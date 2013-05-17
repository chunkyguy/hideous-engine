//
//  Utils.cpp
//  HideousGameEngine
//
//  Created by Sid on 13/02/13.
//  Copyright (c) 2013 whackylabs. All rights reserved.
//

#include <he/Utils/Utils.h>
#include <fstream>

namespace he{
	
	//Set to next power of 2
	int NextPOT (int a){
		int rval = 1;
		while(rval<a)
			rval <<= 1;
		return rval;
	}
	
	FileBuffer::FileBuffer(std::string path){
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
	std::string FileBuffer::GetString(){
		return std::string(buffer_);
	}
	int FileBuffer::GetLength(){
		return length_;
	}

}
//EOF