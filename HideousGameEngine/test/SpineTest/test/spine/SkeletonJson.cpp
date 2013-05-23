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

#include "SkeletonJson.h"
#include <math.h>
#include <stdio.h>
#include <math.h>

#include <he/Texture/TextureAtlas.h>
#include <he/Utils/Utils.h>

#include "Json.h"

#include "RegionAttachment.h"
#include "AtlasAttachmentLoader.h"


namespace {
	float ToColor (std::string value, int index) {
		char digits[3];
		char *error;
		int color;
		
		if (value.size() != 8) return -1;
		value += index * 2;
		
		digits[0] = value.at(0);
		digits[1] = value.at(1);
		digits[2] = '\0';
		color = strtoul(digits, &error, 16);
		if (*error != 0) return -1;
		return color / (float)255;
	}
	
	void ReadCurve (spine::CurveTimeline* timeline, int frameIndex, spine::Json* frame) {
		spine::Json* curve = frame->GetItem( "curve");
		if (!curve) return;
		if (curve->GetType() == Json_String && (curve->GetValueString() == "stepped"))
			timeline->SetStepped( frameIndex);
		else if (curve->GetType() == Json_Array) {
			timeline->SetCurve( frameIndex, curve->GetItemAt(0)->GetValueFloat(), curve->GetItemAt( 1)->GetValueFloat(),
							   curve->GetItemAt( 2)->GetValueFloat(), curve->GetItemAt( 3)->GetValueFloat());
		}
	}
}

namespace spine {
	
	SkeletonJson::SkeletonJson (AttachmentLoader* attachmentLoader) :
	attachmentLoader_(attachmentLoader),
	error_(""),
	ownsLoader_(false),
	scale_(1)
	{	}
	
	SkeletonJson::SkeletonJson (he::TextureAtlas* atlas) :
	attachmentLoader_( new AtlasAttachmentLoader(atlas)),
	ownsLoader_(true),
	scale_(1),
	error_("")
	{	}
	
	SkeletonJson::~SkeletonJson () {
		if (ownsLoader_) {
			delete attachmentLoader_;
		}
	}
	
	void SkeletonJson::set_error ( Json* root, std::string value1, std::string value2) {
		std::string message;
		int length;
		message = value1;
		length = value1.size();
		if (!value2.empty()){
			message += value2;
		}
		error_ =  message;
		if (root){
			delete root;
		}
	}
	
	SkeletonData* SkeletonJson::CreateSkeletonData ( std::string path) {
		he::FileBuffer buffer(path);
		
		std::string json = buffer.GetString();
		assert(!json.empty());	//"Unable to read skeleton file: "
		SkeletonData* skeletonData = read_skeleton_data( json);
		return skeletonData;
	}
	
	SkeletonData* SkeletonJson::read_skeleton_data ( std::string json) {
		error_ = "";
		Json *root = new Json(json.c_str());
		
		if (!root) {
			set_error( 0, "Invalid skeleton JSON: ", root->GetError());
			return 0;
		}
		

		Json *bones = root->GetItem( "bones");
		int boneCount = (bones) ? bones->GetSize() : 0;

		Json* slots = root->GetItem("slots");
		int slotCount = (slots) ? slots->GetSize() : 0;

		Json *skinsMap = root->GetItem("skins");
		int skinCount = (skinsMap) ? skinsMap->GetSize() : 0;

		Json *animations = root->GetItem("animations");
		int animationCount = (animations) ? animations->GetSize() : 0;
		
		SkeletonData* skeletonData = new SkeletonData(boneCount, slotCount, skinCount, animationCount);
		
		//load bones
		for (int i = 0; i < boneCount; ++i) {
			Json* boneMap = bones->GetItemAt(i);
			
			std::string boneName = boneMap->GetString("name", "");
			
			BoneData* parent = 0;
			std::string parentName = boneMap->GetString( "parent", "");
			if (!parentName.empty()) {
				parent = skeletonData->FindBone( parentName);
				if (!parent) {
					delete skeletonData;
					set_error( root, "Parent bone not found: ", parentName);
					return 0;
				}
			}
			
			skeletonData->PushBone(new BoneData(boneName,
											  parent,
											  boneMap->GetFloat( "length", 0) * scale_,
											  boneMap->GetFloat("rotation", 0),
											  GLKVector2Make( boneMap->GetFloat("scaleX", 1), boneMap->GetFloat( "scaleY", 1)),
											  GLKVector2Make(boneMap->GetFloat( "x", 0) * scale_, boneMap->GetFloat( "y", 0) * scale_)));
		}
		
		// Slots		
		for (int i = 0; i < slotCount; ++i) {
			Json* slotMap = slots->GetItemAt(i);
			std::string slotName = slotMap->GetString( "name", "");
			std::string boneName = slotMap->GetString( "bone", "");
			BoneData* boneData = skeletonData->FindBone( boneName);
			if (!boneData) {
				delete skeletonData;
				set_error( root, "Slot bone not found: ", boneName);
				return 0;
			}
						
			GLKVector4 color = GLKVector4Make(1,1,1,1);
			std::string color_str = slotMap->GetString( "color", "");
			if (!color_str.empty()) {
				color = GLKVector4Make( ToColor(color_str, 0), ToColor(color_str, 1), ToColor(color_str, 2), ToColor(color_str, 3));
			}
			
			std::string attachment;
			Json *attachmentItem = slotMap->GetItem( "attachment");
			if (attachmentItem) {
				attachment = attachmentItem->GetValueString();
			}
			
			skeletonData->PushSlot(new SlotData(slotName, boneData, attachment, color));
		}
				
		//Skin
		for (int i = 0; i < skinCount; ++i) {
			Json* slotMap = skinsMap->GetItemAt(i);
			std::string skinName = slotMap->GetName();
			Skin *skin = new Skin(skinName);
			skeletonData->PushSkin( skin);
			
			//bind slots
			int slotNameCount = slotMap->GetSize();
			for (int ii = 0; ii < slotNameCount; ++ii) {
				Json* attachmentsMap = slotMap->GetItemAt(ii);
				std::string slotName = attachmentsMap->GetName();
				int slotIndex = skeletonData->FindSlotIndex( slotName);
				
				// bind attachments
				int attachmentCount = attachmentsMap->GetSize();
				for (int iii = 0; iii < attachmentCount; ++iii) {
					Json* attachmentMap = attachmentsMap->GetItemAt(iii);
					std::string skinAttachmentName = attachmentMap->GetName();
					std::string attachmentName = attachmentMap->GetString("name", skinAttachmentName.c_str());
					
					std::string typeString = attachmentMap->GetString("type", "region");
					AttachmentType type;
					if (typeString == "region"){
						type = ATTACHMENT_REGION;
					}else if (typeString == "regionSequence"){
						type = ATTACHMENT_REGION_SEQUENCE;
					}else {
						delete skeletonData;
						set_error( root, "Unknown attachment type: ", typeString);
						return 0;
					}
					
					Attachment* attachment = attachmentLoader_->NewAttachment( skin, type, attachmentName);
					if (!attachment) {
						if (!attachmentLoader_->GetError1().empty()) {
							delete skeletonData;
							set_error( root, attachmentLoader_->GetError1(), attachmentLoader_->GetError2());
							return 0;
						}
						continue;
					}
					
					if (attachment->GetType() == ATTACHMENT_REGION || attachment->GetType() == ATTACHMENT_REGION_SEQUENCE) {
						RegionAttachment* regionAttachment = (RegionAttachment*)attachment;
						regionAttachment->SetXY(GLKVector2Make(attachmentMap->GetFloat("x", 0) * scale_, attachmentMap->GetFloat("y", 0) * scale_));
						regionAttachment->SetScale(GLKVector2Make(attachmentMap->GetFloat("scaleX", 1), attachmentMap->GetFloat("scaleY", 1)));
						regionAttachment->SetRotation( attachmentMap->GetFloat("rotation", 0));
						regionAttachment->SetSize(GLKVector2Make(attachmentMap->GetFloat("width", 32) * scale_, attachmentMap->GetFloat("height", 32) * scale_));
						regionAttachment->UpdateOffset();
					}
					
					skin->AddAttachment( slotIndex, skinAttachmentName, attachment);
				}
			}
		}
		
		
		//animation
		for (int i = 0; i < animationCount; ++i) {
			Json* animationMap = animations->GetItemAt(i);
			read_animation( animationMap, skeletonData);
		}
		
		
		delete root;
		return skeletonData;
	}
	
	
	Animation* SkeletonJson::read_animation ( Json* root, SkeletonData *skeletonData) {
		Animation* animation;
		
		Json* bones = root->GetItem( "bones");
		int boneCount = bones ? bones->GetSize() : 0;
		
		Json* slots = root->GetItem( "slots");
		int slotCount = slots ? slots->GetSize() : 0;
		
		int timelineCount = 0;
		int i, ii, iii;
		for (i = 0; i < boneCount; ++i){
			timelineCount += bones->GetItemAt(i)->GetSize();
		}
		for (i = 0; i < slotCount; ++i){
			timelineCount += slots->GetItemAt(i)->GetSize();
		}
		animation = new Animation(root->GetName(), timelineCount);
		animation->SetTimelineCount(0);
		skeletonData->PushAnimation(animation);
		
		for (i = 0; i < boneCount; ++i) {
			int timelineCount;
			Json* boneMap = bones->GetItemAt( i);
			
			std::string boneName = boneMap->GetName();
			
			int boneIndex = skeletonData->FindBoneIndex( boneName);
			if (boneIndex == -1) {
				delete animation;
				set_error( root, "Bone not found: ", boneName);
				return 0;
			}
			
			timelineCount = boneMap->GetSize();
			for (ii = 0; ii < timelineCount; ++ii) {
				float duration;
				Json* timelineArray = boneMap->GetItemAt( ii);
				int frameCount = timelineArray->GetSize();
				std::string timelineType = timelineArray->GetName();
				
				if (timelineType == "rotate") {
					
					RotateTimeline *timeline = new RotateTimeline(frameCount);
					timeline->SetBoneIndex(boneIndex);
					for (iii = 0; iii < frameCount; ++iii) {
						Json* frame = timelineArray->GetItemAt(iii);
						timeline->SetFrame( iii, frame->GetFloat("time", 0), frame->GetFloat( "angle", 0));
						ReadCurve(timeline, iii, frame);
					}
					int timelineCount = animation->GetTimelineCount();
					animation->SetTimelineAtIndex(timeline, timelineCount);
					animation->SetTimelineCount(timelineCount+1);
					duration = timeline->GetFrameAtIndex(frameCount * 2 - 2);
					if (duration > animation->GetDuration()){
						animation->SetDuration(duration);
					}
					
				} else {
					bool isScale = (timelineType == "scale");
					if (isScale || (timelineType == "translate")) {
						float scale = isScale ? 1 : scale_;
						BoneBaseTimeline *timeline;
						if(isScale){
							timeline = new ScaleTimeline(frameCount);
						}else{
							timeline = new TranslateTimeline(frameCount);
						}
						timeline->SetBoneIndex( boneIndex);
						for (iii = 0; iii < frameCount; ++iii) {
							Json* frame = timelineArray->GetItemAt( iii);
							timeline->SetFrame(iii, frame->GetFloat( "time", 0), frame->GetFloat("x", 0) * scale, frame->GetFloat("y", 0) * scale);
							ReadCurve(timeline, iii, frame);
						}
						int timelineCount = animation->GetTimelineCount();
						animation->SetTimelineAtIndex(timeline, timelineCount);
						animation->SetTimelineCount(timelineCount+1);
						duration = timeline->GetFrameAtIndex(frameCount * 3 - 3);
						if (duration > animation->GetDuration()){
							animation->SetDuration(duration);
						}
					} else {
						delete animation;
						set_error( 0, "Invalid timeline type for a bone: ", timelineType);
						return 0;
					}
				}
			}
		}
		
		for (i = 0; i < slotCount; ++i) {
			int timelineCount;
			Json* slotMap = slots->GetItemAt( i);
			std::string slotName = slotMap->GetName();
			
			int slotIndex = skeletonData->FindSlotIndex( slotName);
			if (slotIndex == -1) {
				delete animation;
				set_error( root, "Slot not found: ", slotName);
				return 0;
			}
			
			timelineCount = slotMap->GetSize();
			for (ii = 0; ii < timelineCount; ++ii) {
				float duration;
				Json* timelineArray = slotMap->GetItemAt( ii);
				int frameCount = timelineArray->GetSize();
				std::string timelineType = timelineArray->GetName();
				
				if (timelineType == "color") {
					ColorTimeline *timeline = new ColorTimeline(frameCount);
					timeline->SetSlotIndex(slotIndex);
					for (iii = 0; iii < frameCount; ++iii) {
						Json* frame = timelineArray->GetItemAt( iii);
						std::string s = frame->GetString( "color", "");
						timeline->SetFrame( iii, frame->GetFloat( "time", 0), ToColor(s, 0), ToColor(s, 1), ToColor(s, 2), ToColor(s, 3));
						ReadCurve(timeline, iii, frame);
					}
					int timelineCount = animation->GetTimelineCount();
					animation->SetTimelineAtIndex(timeline, timelineCount);
					animation->SetTimelineCount(timelineCount + 1);
					duration = timeline->GetFrameAtIndex(frameCount * 5 - 5);
					if (duration > animation->GetDuration()) animation->SetDuration(duration);
					
				} else if (timelineType == "attachment") {
					AttachmentTimeline *timeline = new AttachmentTimeline(frameCount);
					timeline->SetSlotIndex(slotIndex);
					for (iii = 0; iii < frameCount; ++iii) {
						Json* frame = timelineArray->GetItemAt( iii);
						Json* name = frame->GetItem("name");
						timeline->SetFrame( iii, frame->GetFloat("time", 0),
										   name->GetType() == Json_NULL ? 0 : name->GetValueString());
					}
					int timelineCount = animation->GetTimelineCount();
					animation->SetTimelineAtIndex(timeline, timelineCount);
					animation->SetTimelineCount(timelineCount+1);
					duration = timeline->GetFrameAtIndex(frameCount - 1);
					if (duration > animation->GetDuration()){
						animation->SetDuration( duration );
					}
					
				} else {
					delete animation;
					set_error( 0, "Invalid timeline type for a slot: ", timelineType);
					return 0;
				}
			}
		}
		
		return animation;
	}
	
	std::string SkeletonJson::GetError(){
		return error_;
	}
}
