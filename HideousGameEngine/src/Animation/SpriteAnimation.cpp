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
	// MARK: SpriteAnimationData::Frame
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	SpriteAnimationData::Frame::Frame(TextureVertex *vertex) :
	vertex_(vertex),
	next_(nullptr)
	{}
	
	SpriteAnimationData::Frame::~Frame(){
		delete vertex_;
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// MARK: SpriteAnimationData
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	SpriteAnimationData::SpriteAnimationData(const TextureAtlas *atlas, const std::string &name) :
	head_(nullptr),
	tail_(nullptr),
	t_frame_count_(0),
	name_(name)
	{
		for(; atlas->IsTextureRegionAvailable(FlashFullName(name, t_frame_count_)); t_frame_count_++){
			const TextureAtlasRegion region = atlas->GetTextureAtlasRegion(FlashFullName(name, t_frame_count_));
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
				head_ = tail_ = frame;
			}else{
				tail_->next_ = frame;
				tail_ = frame;
			}
			he_Trace("SpriteAnimation: v-data:\n%@",tail_->vertex_->GetVertexPositionData());
			he_Trace("SpriteAnimation: t-data:\n%@",tail_->vertex_->GetVertexTextureData());
		}
	}

	SpriteAnimationData::~SpriteAnimationData() {
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
	
	unsigned int SpriteAnimationData::GetFrameCount() const {
		return t_frame_count_;
	}

	SpriteAnimationData::Frame* SpriteAnimationData::GetFrameAtIndex(unsigned int frame_num) const {
		Frame *f = nullptr;
		for(f = head_; frame_num-- && f; f = f->next_){
		}
		return f;
	}

//	bool SpriteAnimationData::RetainData(const TextureVertex *data) {
//		for(Frame *f = head_; f; f = f->next_){
//			if (f->vertex_ == data) {
//				f->vertex_ = new TextureVertex((data)->GetVertexPositionData(), (data)->GetVertexTextureData());
//				return true;
//			}
//		}
//		return false;
//	}

	std::string SpriteAnimationData::GetAnimationName() const {
		return name_;
	}

	
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// MARK: SpriteAnimation
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	SpriteAnimation::SpriteAnimation(TextureVertex **vertex_data,
									 const SpriteAnimationData *data,
									 const int repeat_count,
									 const unsigned int final_frame_index,
									 const float fps) :
	vertex_data_(vertex_data),
	data_(data),
	final_vertex_data_(nullptr),
	active_frame_(nullptr),
	clock_(0.0f),
	delay_(1.0f/fps),
	repeat_count_(repeat_count)
	{
		active_frame_ = data->GetFrameAtIndex(0);
		*vertex_data_ = active_frame_->vertex_;
		final_vertex_data_ = data->GetFrameAtIndex(final_frame_index)->vertex_;// new TextureVertex(region, false, region.sprite_size_);
		assert(final_vertex_data_);		// No data to load when the animation end, maybe the frame index provided is out of range.
		assert(*vertex_data_);		// Default vertex data not set
	}

	unsigned int SpriteAnimation::GetFrameCount() const {
		return data_->GetFrameCount();
	}

	void SpriteAnimation::SetRepeatCount(int c) {
		repeat_count_ = c;
	}

	void SpriteAnimation::Restart() {
		active_frame_ = data_->GetFrameAtIndex(0);						// set active-frame to head
		*vertex_data_ = active_frame_->vertex_;		// move to next frame
		clock_ = 0.0f;								// reset clock		
	}

	void SpriteAnimation::GoToFrameNumber(unsigned int frame_num) {
		active_frame_ = data_->GetFrameAtIndex(frame_num);						// set active-frame to head
		*vertex_data_ = active_frame_->vertex_;		// move to next frame
		clock_ = 0.0f;								// reset clock
	}

	void SpriteAnimation::SetFinalFrameIndex(unsigned int ffi) {
		//		delete final_vertex_data_;
		final_vertex_data_ = data_->GetFrameAtIndex(ffi)->vertex_;// new TextureVertex(f->vertex_->GetVertexPositionData(), f->vertex_->GetVertexTextureData());
	}
	
	void SpriteAnimation::SetFPS(float fps) {
		delay_ = 1.0f/fps;
	}

//	void SpriteAnimation::RetainCurrVertex() {
//		he::SpriteAnimationData *data = const_cast<he::SpriteAnimationData*>(data_);
//		if (data->RetainData(*vertex_data_)) {
//		}
//	}

	
	SpriteAnimation::~SpriteAnimation(){		
	}
	
	void SpriteAnimation::update(float dt){
		clock_ += dt;											// sit idle till next delay is over
		if(clock_ > delay_){
			active_frame_ = active_frame_->next_;				// move to next frame
			if(!active_frame_){									// animation done
				if(--repeat_count_ == 0){						// no repeats left
					state_ = kNaturalDeath;						// make zombie. Will be removed at next update cycle.
																// X set the sprite state to final state (released at ~Sprite()).
																//*vertex_data_ = new TextureVertex(final_vertex_data_->GetVertexPositionData(), final_vertex_data_->GetVertexTextureData());
				}else{	//restart loop
					active_frame_ = data_->GetFrameAtIndex(0);						// set active-frame to head
					*vertex_data_ = active_frame_->vertex_;		// move to next frame
					clock_ = 0.0f;								// reset clock
				}
			}else{
				*vertex_data_ = active_frame_->vertex_;			// move to next frame
				clock_ = 0.0f;									// reset clock
			}
		}
	}
} /*namespace he*/
///EOF
