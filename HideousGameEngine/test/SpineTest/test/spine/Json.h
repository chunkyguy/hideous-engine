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

/* Esoteric Software: Removed everything except parsing, shorter method names, more get methods, float to float, formatted. */

#ifndef SPINE_JSON_H_
#define SPINE_JSON_H_
#include <string>

namespace spine {
	/* Json Types: */
#define Json_False 0
#define Json_True 1
#define Json_NULL 2
#define Json_Number 3
#define Json_String 4
#define Json_Array 5
#define Json_Object 6
	
	/* The Json structure: */
	class Json {
	public:
		/* Supply a block of JSON, and this returns a Json object you can interrogate. Call Json_dispose when finished. */
		/* Parse an object - create a new root, and populate. */
		explicit Json (std::string value);
		
		Json();
		
		/* Delete a Json entity and all subentities. */
		~Json();
		
		/* Returns the number of items in an array (or object). */
		int GetSize ();
		
		/* Retrieve item number "item" from array "array". Returns NULL if unsuccessful. */
		Json* GetItemAt (int item);
		
		/* Get item "string" from object. Case insensitive. */
		Json* GetItem ( std::string string);
		std::string GetString ( std::string name, std::string defaultValue);
		float GetFloat ( std::string name, float defaultValue);
		int GetInt ( std::string name, int defaultValue);
		
		/* For analysing failed parses. This returns a pointer to the parse error. You'll probably need to look a few chars back to make sense of it. Defined when Json_create() returns 0. 0 when Json_create() succeeds. */
		std::string GetError (void);
		
		std::string GetValueString();
		int GetValueInt();
		float GetValueFloat();
		int GetType();
		std::string GetName();
		
	private:
		/* Parse the input text to generate a number, and populate the result into item. */
		const char *parse_number (const char *num);
		/* Parse the input text into an unescaped cstring, and populate item. */
		const char *parse_string (const char *str);
		/* Parser core - when encountering text, process appropriately. */
		const char *parse_value (const char *value);
		/* Build an array from input text. */
		const char *parse_array (const char *value);
		/* Build an object from the text. */
		const char *parse_object (const char *value);

		const char *ep_;
		
		/* next/prev allow you to walk array/object chains. Alternatively, use getSize/getItemAt/getItem */
		Json* next_;
		Json* prev_;

		/* An array or object item will have a child pointer pointing to a chain of the items in the array/object. */
		Json* child_;
		
		/* The type of the item, as above. */
		int type_;
		
		/* The item's string, if type==Json_String */
		char *valuestring_;
		
		 /* The item's number, if type==Json_Number */
		int valueint_;
		
		/* The item's number, if type==Json_Number */
		float valuefloat_;
		
		/* The item's name string, if this item is the child of, or is in the list of subitems of an object. */
		char *name_;
	};
	
}

#endif /* SPINE_JSON_H_ */
