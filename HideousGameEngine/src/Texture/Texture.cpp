//
//  Texture.cpp
//  HideousGameEngine
//
//  Created by Sid on 24/02/13.
//  Copyright (c) 2013 whackylabs. All rights reserved.
//

#include <he/Texture/Texture.h>
#include <he/Texture/TextureData.h>
#include <he/Utils/DebugLog.h>

namespace he{
	///////////////////////////////////////////////////////////////////////////////////////////////////
	// MARK: Texture
	///////////////////////////////////////////////////////////////////////////////////////////////////
	Texture::Texture(std::string name, std::string extension, GLint align) :
	name_(name),
	extension_(extension),
	object_(0),
	destructible_(true)
	{
		//FILE_LOG(logDEBUG) << "Creating texture: " << name << "." << extn;
		TextureData texData(name,extension);
		assert(texData.data_);
		GLKVector2 size = GLKVector2Make(texData.width_, texData.height_);
		assert(size.x && size.y);
	
		load_texture(texData.data_, size, align);
	}
	
	Texture::Texture(std::string name, std::string extension, GLubyte *data, GLKVector2 size, GLint align) :
	name_(name),
	extension_(extension),
	object_(0),
	destructible_(true)
	{
		//FILE_LOG(logDEBUG) << "Creating texture: " << name << "." << extn;
		load_texture(data, size, align);
	}

	Texture::Texture(Texture *texture) :
	name_(texture->name_),
	extension_(texture->extension_),
	object_(texture->object_),
	destructible_(false)
	{	}
	
	Texture::~Texture(){
		if(destructible_){
			FILE_LOG(logDEBUG) << "Destroying texture: " << name_ << "." << extension_;
			glDeleteTextures(1, &object_);
			object_ = 0;
		}
	}

	void Texture::load_texture(GLubyte *data, GLKVector2 size, GLint align){
		glGenTextures(1, &object_);
		glBindTexture(GL_TEXTURE_2D, object_);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		switch(align){
			case 1:
				glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
				glTexImage2D(GL_TEXTURE_2D, 0, GL_ALPHA, size.x, size.y, 0, GL_ALPHA, GL_UNSIGNED_BYTE, data);
				glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
				break;
				
			default:
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, size.x, size.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
				break;
		}
	}
}
////EOF
