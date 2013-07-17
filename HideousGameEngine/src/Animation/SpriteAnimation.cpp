//
//  SpriteAnimation.cpp
//  HideousGameEngine
//
//  Created by Sid on 07/06/13.
//  Copyright (c) 2013 whackylabs. All rights reserved.
//
#include <he/Animation/SpriteAnimation.h>


#include <he/RenderObject/RenderObject.h>
#include <he/Texture/TextureAtlas.h>
#include <he/Texture/TextureAtlasRegion.h>
#include <he/Vertex/TextureVertex.h>
#include <he/Utils/DebugHelper.h>
#include <he/Utils/Utils.h>

namespace he{
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// MARK: SpriteAnimation
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	SpriteAnimation::SpriteAnimation(TextureVertex **vertex_data, const TextureAtlas *atlas, const std::string &name,
									 const int repeat_count, const int final_frame_index, const float fps) :
	vertex_data_(vertex_data),
	final_vertex_data_(nullptr),
	head_(nullptr),
	tail_(nullptr),
	active_frame_(nullptr),
	clock_(0.0f),
	delay_(1.0f/fps),
	repeat_count_(repeat_count)
	{
		for(int frame_count = 0; atlas->IsTextureRegionAvailable(FlashFullName(name, frame_count)); frame_count++){
			const TextureAtlasRegion region = atlas->GetTextureAtlasRegion(FlashFullName(name, frame_count));
			TextureVertex *v_data = new TextureVertex(region, false, region.sprite_size_);
			GLKVector2 offset = region.sprite_offset_;
			if(offset.x || offset.y){	// translate
				Vertex::V2 pos_data = v_data->GetVertexPositionData();
				Vertex::Translate(pos_data, offset);
				TextureVertex *del = v_data;
				v_data = new TextureVertex(pos_data, del->GetVertexTextureData());
				delete del;
			}
			Frame *frame = new Frame(v_data);
			if(!head_ && !tail_){	// first node
				head_ = tail_ = active_frame_ = frame;
				*vertex_data_ = active_frame_->vertex_;
			}else{
				tail_->next_ = frame;
				tail_ = frame;
			}
			if(frame_count == final_frame_index){
				assert(!final_vertex_data_);		//Should not be loaded already. If allowed, might be a memory leak.
				final_vertex_data_ = new TextureVertex(region, false, region.sprite_size_);
			}
			he_Trace("SpriteAnimation: v-data:\n%@",tail_->vertex_->GetVertexPositionData());
			he_Trace("SpriteAnimation: t-data:\n%@",tail_->vertex_->GetVertexTextureData());
		}
		assert(final_vertex_data_);		// No data to load when the animation end, maybe the frame index provided is out of range.
		assert(*vertex_data_);		// Default vertex data not set
	}

	void SpriteAnimation::SetRepeatCount(int c) {
		repeat_count_ = c;
	}
	
	void SpriteAnimation::SetFinalFrameIndex(int ffi) {
		Frame *f;
		for(f = head_; ffi--; f = f->next_){
		}
		assert(f);
		delete final_vertex_data_;
		final_vertex_data_ = new TextureVertex(f->vertex_->GetVertexPositionData(), f->vertex_->GetVertexTextureData());
	}
	
	void SpriteAnimation::SetFPS(float fps) {
		delay_ = 1.0f/fps;
	}

	
	SpriteAnimation::~SpriteAnimation(){
		Frame *del = nullptr;
		for(Frame *f = head_; f; f = f->next_){
			if(del){
				delete del;
				del = nullptr;
			}
			del = f;
		}
		if(del){
			delete del;
			del = nullptr;
		}
	}
	
	void SpriteAnimation::update(float dt){
		clock_ += dt;											// sit idle till next delay is over
		if(clock_ > delay_){
			active_frame_ = active_frame_->next_;				// move to next frame
			if(!active_frame_){									// animation done
				if(--repeat_count_ == 0){						// no repeats left
					state_ = kNaturalDeath;						// make zombie. Will be removed at next update cycle.
					*vertex_data_ = final_vertex_data_;			// set the sprite state to final state (picked at ctor)
				}else{	//restart loop
					active_frame_ = head_;						// set active-frame to head
					*vertex_data_ = active_frame_->vertex_;		// move to next frame
					clock_ = 0.0f;								// reset clock
				}
			}else{
				*vertex_data_ = active_frame_->vertex_;			// move to next frame
				clock_ = 0.0f;									// reset clock
			}
		}
	}

	
	SpriteAnimation::Frame::Frame(TextureVertex *vertex) :
	vertex_(vertex),
	next_(nullptr)
	{}
	
	SpriteAnimation::Frame::~Frame(){
		delete vertex_;
	}
	
} /*namespace he*/
///EOF
