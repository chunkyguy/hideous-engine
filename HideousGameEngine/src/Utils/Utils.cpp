//
//  Utils.cpp
//  HideousGameEngine
//
//  Created by Sid on 13/02/13.
//  Copyright (c) 2013 whackylabs. All rights reserved.
//

#include <he/Utils/Utils.h>

#include <fstream>
#include <sstream>


namespace he{
	
	//Set to next power of 2
	int NextPOT (int a){
		int rval = 1;
		while(rval<a)
			rval <<= 1;
		return rval;
	}
	
	std::string FlashFullName(const std::string &name, const int frame_number){
		std::stringstream stream;
		stream << name << " instance " << 10000 + frame_number; 		// head instance 10000
		return stream.str();
	}

	
	FileBuffer::FileBuffer(const std::string &path){
		std::ifstream fin;
		fin.open(path.c_str());
		assert(fin.is_open());
		
		fin.seekg(0, std::ios::end);
		length_ = fin.tellg();
		fin.seekg(0, std::ios::beg);
		buffer_ = new char[length_ + 1];
		fin.read(buffer_, length_);
		buffer_[length_] = 0;
	}
	FileBuffer::~FileBuffer(){
		delete buffer_;
		buffer_ = 0;
	}
	std::string FileBuffer::GetString() const{
		return std::string(buffer_);
	}
	const char *FileBuffer::GetData() const{
		return buffer_;
	}
	int FileBuffer::GetLength() const{
		return length_;
	}

}
//EOF