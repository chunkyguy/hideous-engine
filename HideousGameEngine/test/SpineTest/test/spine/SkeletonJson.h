/*******************************************************************************
 * Copyright (c) 2013, Esoteric Software
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 ******************************************************************************/

#ifndef SPINE_SKELETONJSON_H_
#define SPINE_SKELETONJSON_H_

#include "Attachment.h"
#include "AttachmentLoader.h"
#include "SkeletonData.h"
#include "Atlas.h"
#include "Animation.h"
#include "Json.h"

namespace he{
	class TextureAtlas;
}

namespace spine {
	
	class SkeletonJson{
	public:
		// Doesn't owns the attachment loader
		explicit SkeletonJson (AttachmentLoader* attachmentLoader);
		
		// Owns the attachment loader
		explicit SkeletonJson (he::TextureAtlas* atlas);
		
		~SkeletonJson ();

		// Load file into memory
		SkeletonData* ReadSkeletonDataFile ( std::string path);
		
		std::string GetError();
		
	private:
		void set_error ( Json* root, std::string value1, std::string value2);
		
		// read json data and create skeleton data
		SkeletonData* read_skeleton_data ( std::string json);
		Animation* read_animation ( Json* root, SkeletonData *skeletonData);
			
		struct Internal {
			bool ownsLoader;
		} ;
		Internal *internal_;
		float scale_;
		AttachmentLoader* attachmentLoader_;
		std::string error_;
	} ;
	
	
}

#endif /* SPINE_SKELETONJSON_H_ */
