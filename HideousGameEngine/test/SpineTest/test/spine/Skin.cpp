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

#include "Skin.h"
#include "Skeleton.h"

namespace spine {
	
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// MARK: Skin::Internal::Entry
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	Skin::Internal::Entry::Entry (int slotIndex, std::string name, Attachment* attachment) :
	attachment_(attachment),
	name_(name),
	next_(nullptr),
	slotIndex_(slotIndex)
	{	}
	
	Skin::Internal::Entry::~Entry() {
		delete attachment_;
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// MARK: Skin::Internal
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	Skin::Internal::Internal() :
	entries_(nullptr)
	{}
	
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// MARK: Skin
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	Skin::Skin (std::string name) :
	internal_(new Internal),
	name_(name)
	{	}
	
	Skin::~Skin () {
		Internal::Entry* entry = internal_->entries_;
		while (entry) {
			Internal::Entry* nextEntry = entry->next_;
			delete entry;
			entry = nextEntry;
		}
		 delete internal_;
	}
	
#include <stdio.h>
	void Skin::AddAttachment ( int slotIndex, std::string name, Attachment* attachment) {
		Internal::Entry* newEntry = new Internal::Entry(slotIndex, name, attachment);
		newEntry->next_ = internal_->entries_;
		internal_->entries_ = newEntry;
	}
	Attachment* Skin::GetAttachment ( int slotIndex, std::string name) const{
		const Internal::Entry* entry = internal_->entries_;
		while (entry) {
			if (entry->slotIndex_ == slotIndex && (entry->name_ == name)){
				return entry->attachment_;
			}
			entry = entry->next_;
		}
		return 0;
	}
	
	void Skin::AttachAll ( Skeleton* skeleton, const Skin* oldSkin) const{
		const Internal::Entry *entry = oldSkin->internal_->entries_;
		while (entry) {
			Slot *slot = skeleton->GetSlotAtIndex(entry->slotIndex_);
			if (slot->GetAttachment() == entry->attachment_) {
				Attachment *attachment = GetAttachment( entry->slotIndex_, entry->name_);
				if (attachment) slot->SetAttachment( attachment);
			}
			entry = entry->next_;
		}
	}

	std::string Skin::GetName(){
		return name_;
	}

}
