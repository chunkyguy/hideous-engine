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

#include "AttachmentLoader.h"
#include <stdio.h>
 

namespace spine {

	AttachmentLoader::AttachmentLoader() :
	error1_(""),
	error2_("")
	{}
	
	Attachment* AttachmentLoader::NewAttachment ( Skin* skin, AttachmentType type, std::string name) {
		return nullptr;
	}
	
	void AttachmentLoader::set_error (std::string error1, std::string error2) {
		error1_ = error1;
		error2_ = error2;
	}
	
	void AttachmentLoader::set_unknown_type_error ( AttachmentType type) {
		char buffer[16];
		sprintf(buffer, "%d", type);
		set_error("Unknown attachment type: ", buffer);
	}
	
	void AttachmentLoader::SetUnknownTypeError ( AttachmentType type){
		set_unknown_type_error(type);
	}

	std::string AttachmentLoader::GetError1(){
		return error1_;
	}
	std::string AttachmentLoader::GetError2(){
		return error2_;
	}

}
