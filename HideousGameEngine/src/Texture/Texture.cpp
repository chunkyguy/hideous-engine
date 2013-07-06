//
//  Texture.cpp
//  HideousGameEngine
//
//  Created by Sid on 24/02/13.
//  Copyright (c) 2013 whackylabs. All rights reserved.
//

#include <he/Texture/Texture.h>
#include <he/Texture/TextureData.h>
#include <he/Utils/DebugHelper.h>

namespace he{
	///////////////////////////////////////////////////////////////////////////////////////////////////
	// MARK: Texture
	///////////////////////////////////////////////////////////////////////////////////////////////////
	Texture::Texture(std::string path, GLint align) :
	destructible_(true),
	object_(0),
	path_(path),
	size_(GLKVector2Make(0,0))
	{
		he_Trace("Texture: %@\n",path);
		TextureData texData(path_);
		assert(texData.data_);
		size_ = GLKVector2Make(texData.width_, texData.height_);
		assert(size_.x && size_.y);
	
		load_texture(texData.data_, align);
	}
	
	Texture::Texture(std::string path, GLubyte *data, GLKVector2 size, GLint align) :
	destructible_(true),
	object_(0),
	path_(path),
	size_(size)
	{
		he_Trace("Texture: %@\n",path);
		load_texture(data, align);
	}

	Texture::Texture(Texture *texture) :
	destructible_(false),
	object_(texture->object_),
	path_(texture->path_),
	size_(texture->size_)
	{	}
	
	Texture::~Texture(){
		if(destructible_){
			he_Trace("~Texture: %@\n",path_);
			glDeleteTextures(1, &object_);
			object_ = 0;
		}
	}

	void Texture::load_texture(GLubyte *data, GLint align){
		glGenTextures(1, &object_);
		glBindTexture(GL_TEXTURE_2D, object_);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		switch(align){
			case 1:
				glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
				glTexImage2D(GL_TEXTURE_2D, 0, GL_ALPHA, size_.x, size_.y, 0, GL_ALPHA, GL_UNSIGNED_BYTE, data);
				glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
				break;
				
			default:
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, size_.x, size_.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
				break;
		}
		assert(object_);		// Texture not loaded
	}
	
	GLKVector2 Texture::GetSize(){
		return size_;
	}
	
}
////EOF
