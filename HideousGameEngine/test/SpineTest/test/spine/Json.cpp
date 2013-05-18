/*
 Copyright (c) 2009 Dave Gamble
 
 Permission is hereby granted, dispose of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 */

/* Json */
/* JSON parser in C. */

#include "Json.h"
#include <cmath>
#include <cstdio>
#include <cctype>
#include <cassert>

namespace{
	/* Utility to jump whitespace and cr/lf */
	const char* skip (const char* in) {
		while (in && *in && (unsigned char)*in <= 32)
			in++;
		return in;
	}
	
	int Strcasecmp (const char* s1, const char* s2) {
		if (!s1) return (s1 == s2) ? 0 : 1;
		if (!s2) return 1;
		for (; tolower(*s1) == tolower(*s2); ++s1, ++s2)
			if (*s1 == 0) return 0;
		return tolower(*(const unsigned char*)s1) - tolower(*(const unsigned char*)s2);
	}
}

namespace spine {
	
	/* Parse an object - create a new root, and populate. */
	Json::Json (std::string value) :
	ep_(nullptr),
	next_(nullptr),
	prev_(nullptr),
	child_(nullptr),
	type_(0),
	valuestring_(nullptr),
	valueint_(0),
	valuefloat_(0),
	name_(nullptr)
	{
		const char* end = parse_value(skip(value.c_str()));
		assert(end);	/* parse failure. ep is set. */
	}


	Json::Json () :
	ep_(nullptr),
	next_(nullptr),
	prev_(nullptr),
	child_(nullptr),
	type_(0),
	valuestring_(nullptr),
	valueint_(0),
	valuefloat_(0),
	name_(nullptr)
	{	}

	/* Delete a Json structure. */
	//	void Json_Dispose (Json *curr) {
	//
	//		Json *current = curr;
	//		Json *next;
	//		while (current) {
	//			next = current->next_;
	//			if (current->child_) Json_Dispose(current->child_);
	//			delete current;
	//			current = next;
	//		}
	//	}
	Json::~Json(){
		if(child_) { delete child_;}
		if(next_) {delete next_;}
		if(ep_){ delete ep_;}
		if(prev_) {prev_ = 0;}
		if(valuestring_) {delete valuestring_;}
		if(name_) {delete name_;}
	}
	
	/* Parser core - when encountering text, process appropriately. */
	const char* Json::parse_value (const char* value) {
		if (!value) return 0; /* Fail on null. */
		if (!strncmp(value, "null", 4)) {
			type_ = Json_NULL;
			return value + 4;
		}
		if (!strncmp(value, "false", 5)) {
			type_ = Json_False;
			return value + 5;
		}
		if (!strncmp(value, "true", 4)) {
			type_ = Json_True;
			valueint_ = 1;
			return value + 4;
		}
		if (*value == '\"') {
			return parse_string(value);
		}
		if (*value == '-' || (*value >= '0' && *value <= '9')) {
			return parse_number(value);
		}
		if (*value == '[') {
			return parse_array(value);
		}
		if (*value == '{') {
			return parse_object(value);
		}
		
		ep_ = value;
		return 0; /* failure. */
	}

	/* Parse the input text into an unescaped cstring, and populate item. */
	static const unsigned char firstByteMark[7] = {0x00, 0x00, 0xC0, 0xE0, 0xF0, 0xF8, 0xFC};
	const char *Json::parse_string (const char *str) {
		const char* ptr = str + 1;
		char* ptr2;
		char* out;
		int len = 0;
		unsigned uc, uc2;
		if (*str != '\"') {
			ep_ = str;
			return 0;
		} /* not a string! */
		
		while (*ptr != '\"' && *ptr && ++len)
			if (*ptr++ == '\\') ptr++; /* Skip escaped quotes. */
		
		out = (char*)malloc(len + 1); /* This is how long we need for the string, roughly. */
		if (!out) return 0;
		
		ptr = str + 1;
		ptr2 = out;
		while (*ptr != '\"' && *ptr) {
			if (*ptr != '\\')
				*ptr2++ = *ptr++;
			else {
				ptr++;
				switch (*ptr) {
					case 'b':
						*ptr2++ = '\b';
						break;
					case 'f':
						*ptr2++ = '\f';
						break;
					case 'n':
						*ptr2++ = '\n';
						break;
					case 'r':
						*ptr2++ = '\r';
						break;
					case 't':
						*ptr2++ = '\t';
						break;
					case 'u': /* transcode utf16 to utf8. */
						sscanf(ptr + 1, "%4x", &uc);
						ptr += 4; /* get the unicode char. */
						
						if ((uc >= 0xDC00 && uc <= 0xDFFF) || uc == 0) break; /* check for invalid.	*/
						
						if (uc >= 0xD800 && uc <= 0xDBFF) /* UTF16 surrogate pairs.	*/
						{
							if (ptr[1] != '\\' || ptr[2] != 'u') break; /* missing second-half of surrogate.	*/
							sscanf(ptr + 3, "%4x", &uc2);
							ptr += 6;
							if (uc2 < 0xDC00 || uc2 > 0xDFFF) break; /* invalid second-half of surrogate.	*/
							uc = 0x10000 + (((uc & 0x3FF) << 10) | (uc2 & 0x3FF));
						}
						
						len = 4;
						if (uc < 0x80)
							len = 1;
						else if (uc < 0x800)
							len = 2;
						else if (uc < 0x10000) len = 3;
						ptr2 += len;
						
						switch (len) {
							case 4:
								*--ptr2 = ((uc | 0x80) & 0xBF);
								uc >>= 6;
							case 3:
								*--ptr2 = ((uc | 0x80) & 0xBF);
								uc >>= 6;
							case 2:
								*--ptr2 = ((uc | 0x80) & 0xBF);
								uc >>= 6;
							case 1:
								*--ptr2 = (uc | firstByteMark[len]);
						}
						ptr2 += len;
						break;
					default:
						*ptr2++ = *ptr;
						break;
				}
				ptr++;
			}
		}
		*ptr2 = 0;
		if (*ptr == '\"') ptr++;
		valuestring_ = out;
		type_ = Json_String;
		return ptr;
	}

	/* Parse the input text to generate a number, and populate the result into item. */
	const char* Json::parse_number (const char* num) {
		float n = 0, sign = 1, scale = 0;
		int subscale = 0, signsubscale = 1;
		
		/* Could use sscanf for this? */
		if (*num == '-') sign = -1, num++; /* Has sign? */
		if (*num == '0') num++; /* is zero */
		if (*num >= '1' && *num <= '9') do
			n = (n * 10.0f) + (*num++ - '0');
		while (*num >= '0' && *num <= '9'); /* Number? */
		if (*num == '.' && num[1] >= '0' && num[1] <= '9') {
			num++;
			do
				n = (n * 10.0f) + (*num++ - '0'), scale--;
			while (*num >= '0' && *num <= '9');
		} /* Fractional part? */
		if (*num == 'e' || *num == 'E') /* Exponent? */
		{
			num++;
			if (*num == '+')
				num++;
			else if (*num == '-') signsubscale = -1, num++; /* With sign? */
			while (*num >= '0' && *num <= '9')
				subscale = (subscale * 10) + (*num++ - '0'); /* Number? */
		}
		
		n = sign * n * (float)pow(10.0f, (scale + subscale * signsubscale)); /* number = +/- number.fraction * 10^+/- exponent */
		
		valuefloat_ = n;
		valueint_ = (int)n;
		type_ = Json_Number;
		return num;
	}
		
	/* Build an array from input text. */
	const char *Json::parse_array (const char *value) {
		Json *child;
		if (*value != '[') {
			ep_ = value;
			return 0;
		} /* not an array! */
		
		type_ = Json_Array;
		value = skip(value + 1);
		if (*value == ']') return value + 1; /* empty array. */
		
		child_ = child = new Json;
		if (!child_) return 0; /* memory fail */
		value = skip(child->parse_value(skip(value))); /* skip any spacing, get the value. */
		if (!value) return 0;
		
		while (*value == ',') {
			Json *new_item;
			if (!(new_item = new Json)) return 0; /* memory fail */
			child->next_ = new_item;
			new_item->prev_ = child;
			child = new_item;
			value = skip(child->parse_value(skip(value + 1)));
			if (!value) return 0; /* memory fail */
		}
		
		if (*value == ']') return value + 1; /* end of array */
		ep_ = value;
		return 0; /* malformed. */
	}
	
	/* Build an object from the text. */
	const char *Json::parse_object (const char *value) {
		Json *child;
		if (*value != '{') {
			ep_ = value;
			return 0;
		} /* not an object! */
		
		type_ = Json_Object;
		value = skip(value + 1);
		if (*value == '}') return value + 1; /* empty array. */
		
		child_ = child = new Json;
		if (!child_) return 0;
		value = skip(child->parse_string(skip(value)));
		if (!value) return 0;
		child->name_ = child->valuestring_;
		child->valuestring_ = 0;
		if (*value != ':') {
			ep_ = value;
			return 0;
		} /* fail! */
		value = skip(child->parse_value( skip(value + 1))); /* skip any spacing, get the value. */
		if (!value) return 0;
		
		while (*value == ',') {
			Json *new_item;
			if (!(new_item = new Json)) return 0; /* memory fail */
			child->next_ = new_item;
			new_item->prev_ = child;
			child = new_item;
			value = skip(child->parse_string(skip(value + 1)));
			if (!value) return 0;
			child->name_ = child->valuestring_;
			child->valuestring_ = 0;
			if (*value != ':') {
				ep_ = value;
				return 0;
			} /* fail! */
			value = skip(child->parse_value(skip(value + 1))); /* skip any spacing, get the value. */
			if (!value) return 0;
		}
		
		if (*value == '}') return value + 1; /* end of array */
		ep_ = value;
		return 0; /* malformed. */
	}
	
	std::string Json::GetError (void) {
		return ep_;
	}

	/* Get Array size/item / object item. */
	int Json::GetSize () {
		Json *c = child_;
		int i = 0;
		while (c)
			i++, c = c->next_;
		return i;
	}
	
	Json *Json::GetItemAt ( int item) {
		Json *c = child_;
		while (c && item > 0)
			item--, c = c->next_;
		return c;
	}
	
	Json *Json::GetItem ( std::string string) {
		Json *c = child_;
		while (c && Strcasecmp(c->name_, string.c_str()))
			c = c->next_;
		return c;
	}
	
	std::string Json::GetString ( std::string name, std::string defaultValue) {
		Json *object = GetItem(name);
		if (object) return object->valuestring_;
		return defaultValue;
	}
	
	float Json::GetFloat (std::string name, float defaultValue) {
		Json* value = GetItem(name);
		return value ? value->valuefloat_ : defaultValue;
	}
	
	int Json::GetInt ( std::string name, int defaultValue) {
		Json* value = GetItem (name);
		return value ? (int)value->valuefloat_ : defaultValue;
	}

	std::string Json::GetValueString(){
		return valuestring_;
	}
	int Json::GetValueInt(){
		return valueint_;
	}
	float Json::GetValueFloat(){
		return valuefloat_;
	}
	int Json::GetType(){
		return type_;
	}
	std::string Json::GetName(){
		return name_;
	}
}
