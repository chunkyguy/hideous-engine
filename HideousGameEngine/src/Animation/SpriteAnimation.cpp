//
//  SpriteAnimation.cpp
//  HideousGameEngine
//
//  Created by Sid on 07/06/13.
//  Copyright (c) 2013 whackylabs. All rights reserved.
//
#include <he/Animation/SpriteAnimation.h>

#include <sstream>

#include <he/RenderObject/RenderObject.h>
#include <he/Texture/TextureAtlas.h>
#include <he/Texture/TextureAtlasRegion.h>
#include <he/Vertex/VertexTex.h>
#include <he/Utils/DebugHelper.h>

namespace he{
	class FrameLoop{
	public:
		FrameLoop(const std::string &name, const TextureAtlas *atlas) :
		frames_(0),
		atlas_(atlas),
		name_(name),
		done_(false),
		region_(nullptr)
		{
			load_region();
		}
		
		bool Done() const{
			return done_;
		}
		
		const TextureAtlasRegion *Get(){
			return region_;
		}
		
		void operator++(){
			++frames_;
			load_region();
		}
		
	private:
		void load_region(){
			std::stringstream stream;
			stream << name_ << " instance " << 10000+frames_; 		// head instance 10000
			std::string full_name = stream.str();
			region_ = atlas_->GetTextureAtlasRegion(full_name);
			if(!region_){
				done_ = true;
			}
		}
		
		int frames_;
		const TextureAtlas *atlas_;
		std::string name_;
		bool done_;
		const TextureAtlasRegion *region_;
	};
	
	SpriteAnimation::SpriteAnimation(VertexTex **vertex_data, const TextureAtlas *atlas, const std::string &name, const int final_frame_index, const float fps) :
	active_frame_(nullptr),
	head_(nullptr),
	tail_(nullptr),
	clock_(0.0f),
	delay_(1.0f/fps),
	vertex_data_(vertex_data),
	final_vertex_data_(nullptr)
	{
		int frame_count = 0;
		for(FrameLoop loop_var(name, atlas); !loop_var.Done(); ++loop_var, ++frame_count){
			const TextureAtlasRegion *region = loop_var.Get();
			VertexTex *v_data = new VertexTex(region, region->sprite_size_.x, region->sprite_size_.y, false);
			GLKVector2 offset = region->sprite_offset_;
			if(offset.x || offset.y){	// translate
				VertexData pos_data = v_data->GetVertexPositionData();
				pos_data.Translate(offset);
				VertexTex *del = v_data;
				v_data = new VertexTex(pos_data, del->GetVertexTextureData());
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
			if(frame_count == final_frame_index && !final_vertex_data_){
				final_vertex_data_ = new VertexTex(region, region->sprite_size_.x, region->sprite_size_.y, false);
			}
			assert(final_vertex_data_);		// No data to load when the animation end, maybe the frame index provided is out of range.
			he_Trace("SpriteAnimation: v-data:\n%@",tail_->vertex_->GetVertexPositionData());
			he_Trace("SpriteAnimation: t-data:\n%@",tail_->vertex_->GetVertexTextureData());
		}
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
		clock_ += dt;
		if(clock_ > delay_){
			active_frame_ = active_frame_->next_;
			if(!active_frame_){
				state_ = kNaturalDeath;
				*vertex_data_ = final_vertex_data_;
			}else{
				*vertex_data_ = active_frame_->vertex_;
				clock_ = 0.0f;
			}
		}
	}

	
	SpriteAnimation::Frame::Frame(VertexTex *vertex) :
	vertex_(vertex),
	next_(nullptr)
	{}
	
	SpriteAnimation::Frame::~Frame(){
		delete vertex_;
	}
	
} /*namespace he*/
///EOF
