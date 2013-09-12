//
//  Sprite.cpp
//  HideousGameEngine
//
//  Created by Sid on 20/06/13.
//  Copyright (c) 2013 whackylabs. All rights reserved.
//

#include <he/UI/Sprite.h>
#include <he/Animation/AnimationLoop.h>
#include <he/Animation/SpriteAnimation.h>
#include <he/Animation/AnimationUtils.h>
#include <he/RenderObject/RenderObject.h>
#include <he/Vertex/TextureVertex.h>
#include <he/Utils/Utils.h>
#include <he/Texture/TextureAtlas.h>
#include <he/Shaders/TextureShader.h>
#include <he/Texture/Texture.h>
#include <he/Vertex/TextureVertex.h>
#include <he/Texture/TextureAtlasRegion.h>

namespace he{
	namespace {
		class SpriteEndAnimationFunctor {
		public:
			SpriteEndAnimationFunctor(Animation::ID ID) :
			id_(ID) {}
			
			void operator()(Animation *anim) {
				SpriteAnimation *animation = static_cast<SpriteAnimation*>(anim);
				Animation::ID ID = animation->GetID();
				if(ID == id_){
					animation->RetainCurrVertex();
					animation->Die();
				}
			}
			
		private:
			Animation::ID id_;
		};
		
		
		void SpriteEndAnimationsWithID(Animation::ID ID){
			g_AnimationLoop->TraverseAnimations(SpriteEndAnimationFunctor(ID));
		}
	}
	
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// MARK: Sprite
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	Sprite::Sprite(const SpriteAnimationData *data,
				   const TextureShader *shader, const TextureAtlas *atlas,
				   const int repeat_count, AnimationListenable *listener,
				   const int final_frame, const float fps) :
	vertex_(nullptr),
	render_object_(),
	size_(atlas->GetTextureAtlasRegion(he::FlashFullName(data->GetAnimationName())).sprite_size_)
	{
		animation_ = static_cast<SpriteAnimation*>(g_AnimationLoop->MoveAnimation(new SpriteAnimation(&vertex_, data, repeat_count, final_frame, fps)));
		anim_id_ = animation_->GetID();
		if (listener) {
			animation_->SetListener(listener);
		}
		assert(vertex_);		// There is some default vertex data.
		render_object_ = new RenderObject(vertex_, shader, atlas->GetTexture());
	}

	Sprite::~Sprite(){
		/*
		 Case 1: The Sprite dies after the SpriteAnimation.
		 1. Call the SpriteEndAnimationFunctor, would do no harm, as no anim_id_ exists.
		 2. Before dying the SpriteAnimation must have passed an allocated copy to vertex_.
		 3. Can safely delete the vertex_ now.
		 
		 Case 2: The SpriteAnimation dies after Sprite.
		 1. The SpriteEndAnimationFunctor asks the SpriteAnimation to retain current-vertex.
		 2. Since 'this' is not NULL yet, so can be used to create an allocated copy for SpriteAnimation::Frame's vertex object.
		 3. Can safely delete the vertex_ now.
		 */
		SpriteEndAnimationsWithID(anim_id_);
		delete vertex_;
		vertex_ = nullptr;
		delete render_object_;
	}

	Animation::ID Sprite::GetID() const {
		return anim_id_;
	}
	
	void Sprite::Render(const Transform &transform){
		render_object_->SetVertexData(vertex_);
		render_object_->SetMVP(Transform_GetMVP(&transform));
		render_object_->Render();
	}

	GLKVector2 Sprite::GetSize() const {
		return size_;
	}
	
	void Sprite::GoToFrameNumber(unsigned int frame_num) {
		animation_->GoToFrameNumber(frame_num);
	}
	
	unsigned int Sprite::GetFrameCount() const {
		return animation_->GetFrameCount();
	}

	void Sprite::StartAnimation() {
		animation_->Run();
	}


	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// MARK: Utility
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	namespace sprite {

		SpriteAnimationData *Create(const TextureAtlas *texture_atlas,
									const std::string &region) {
			return new SpriteAnimationData(texture_atlas, region);
		}

		Sprite *Create(const SpriteAnimationData *data,
					   const TextureShader *shader, const TextureAtlas *texture_atlas,
					   const int repeat_count, AnimationListenable *listener, const int final_frame, const float fps) {
			return new Sprite(data, shader, texture_atlas, repeat_count, listener, final_frame, fps);
		}

	}
	
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// MARK: SpriteView
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	SpriteView::SpriteView(const Transform &transform, Sprite *sprite) :
	View(transform),
	sprite_(sprite)
	{}

	void SpriteView::Update(float dt) {
		View::Update(dt);
	}
	
	void SpriteView::Render() {
		sprite_->Render(GetTransform());
	}
	
	GLKVector2 SpriteView::GetSize() const {
		return sprite_->GetSize();
	}
} 
///EOF