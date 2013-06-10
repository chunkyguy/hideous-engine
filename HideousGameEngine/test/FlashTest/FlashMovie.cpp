//
//  FlashMovie.cpp
//  HideousGameEngine
//
//  Created by Sid on 07/06/13.
//  Copyright (c) 2013 whackylabs. All rights reserved.
//

#include "FlashMovie.h"

#include <he/Animation/AnimationLoop.h>
#include <he/Animation/SpriteAnimation.h>
#include <he/Animation/RawAnimation.h>
#include <he/Animation/Tweener.h>
#include <he/RenderObject/RenderObject.h>
#include <he/Shaders/TextureShader.h>
#include <he/Texture/Texture.h>
#include <he/Texture/TextureAtlas.h>
#include <he/Utils/DebugHelper.h>
#include <he/Utils/Screen.h>
#include <he/Vertex/TextureVertex.h>

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// MARK: FlashMovie
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
FlashMovie::FlashMovie(const std::string &name,
					   const FlashMovieAssets *assets,
					   const GLKVector2 &position,
					   const int final_frame,
					   const float fps) :
angle_(GLKVector3Make(0, 0, 0)),
position_(position),
render_object_(nullptr),
vertex_data_(nullptr)
{

	he::TextureShader *sh = const_cast<he::TextureShader *>(assets->GetShader());
	assert(sh);
	
	he::Texture *tx = assets->GetAtlas()->GetTexture();
	assert(tx);
	
	render_object_ = new he::RenderObject(vertex_data_, sh, tx);
	assert(render_object_);
	
	he::SpriteAnimation *animation = new he::SpriteAnimation(&vertex_data_, assets->GetAtlas(), name, -1, final_frame, fps);
	assert(animation);
	
	he::g_AnimationLoop->AddAnimation(animation);
}

FlashMovie::~FlashMovie(){
	assert(vertex_data_);	delete vertex_data_;
	assert(render_object_);	delete render_object_;
}

void FlashMovie::Update(double dt){
	// translation
	GLKMatrix4 mvMat = GLKMatrix4MakeTranslation(position_.x, position_.y, -he::g_Screen->z_);
	// rotation
	//	mvMat = GLKMatrix4RotateY(mvMat, GLKMathDegreesToRadians(angle_.x));		// determines facing front-back
	
	mvMat = GLKMatrix4RotateX(mvMat, angle_.x);
	mvMat = GLKMatrix4RotateY(mvMat, angle_.y);
	mvMat = GLKMatrix4RotateZ(mvMat, angle_.z);
	GLKMatrix4 mvpMat = he::g_Screen->projection_ * mvMat;
	render_object_->SetMVP(mvpMat);

	// Update vertex-data
	render_object_->SetVertexData(vertex_data_);
}

void FlashMovie::Render(){
	he::TextureVertex *v = dynamic_cast<he::TextureVertex *>(render_object_->GetVertexData());
	assert(v);
	render_object_->Render();
}

void FlashMovie::TouchPoint(const GLKVector2 &point){
	GLKVector2 diff = point - position_;
	angle_ = GLKVector3Make(0, 0, atan2f(diff.y, diff.x));
	//	he_Trace("FlashMovie: next_angle-Z: %@\n",next_angle * GLKMathRadiansToDegrees(1));
	float ninty_rads = GLKMathDegreesToRadians(90.0f);
	if(fabs(angle_.z) > ninty_rads){
		angle_.y = ninty_rads*2;
		if(angle_.z > 90.0f){
			angle_.z -= 2*ninty_rads;
		}else{
			angle_.z = 2+ninty_rads - angle_.z;
		}
	}
	//	he_Trace("FlashMovie: next_angle: %@\n",next_angle * GLKMathRadiansToDegrees(1));

	//	he::RawAnimation<GLKVector3> *rot_anim = new he::RawAnimation<GLKVector3>(&angle_, he::Tweener<GLKVector3>(he::CubicEaseInOut, angle_, next_angle), 30);
	he::RawAnimation<GLKVector2> *trans_anim = new he::RawAnimation<GLKVector2>(&position_, he::Tweener<GLKVector2>(he::CubicEaseInOut, position_, point), 30);
	//	rot_anim->AddChild(trans_anim);

	he::g_AnimationLoop->AddAnimation(trans_anim);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// MARK: FlashMovieAssets
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
FlashMovieAssets::FlashMovieAssets(he::TextureAtlas *atlas, he::TextureShader *shader) :
atlas_(atlas),
shader_(shader)
{}

FlashMovieAssets::~FlashMovieAssets(){
	delete atlas_;
	delete shader_;
}


const he::TextureAtlas *FlashMovieAssets::GetAtlas() const{
	return atlas_;
}

const he::TextureShader *FlashMovieAssets::GetShader() const{
	return shader_;
}
/// EOF
