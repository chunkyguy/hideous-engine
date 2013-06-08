//
//  SpineTest.cpp
//  HideousGameEngine
//
//  Created by Sid on 09/05/13.
//  Copyright (c) 2013 whackylabs. All rights reserved.
//

#include "SpineTest.h"

#include <cstdio>
#include <he/Utils/GLKMath_Additions.h>

#include <he/RenderObject/RenderObject.h>
#if defined(DEBUG_DRAW)
	#include <he/Shaders/RectColorSh/RectColorSh.h>
	#include <he/Vertex/VertexCol.h>
#else
	#include <he/Shaders/RectTextureSh/RectTextureSh.h>
	#include <he/Texture/Texture.h>
	#include <he/Vertex/VertexTex.h>
#endif
#include <he/Texture/TextureAtlas.h>
#include <he/Texture/TextureAtlasRegion.h>
#include <he/Vertex/VertexData.h>
#include <he/Utils/DebugLog.h>
#include <he/Utils/ResourcePath.hpp>
#include <he/Utils/Utils.h>

//#define GOBLIN
#define SPINEBOY
#define PRINT_LOG

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// MARK: SpintTest
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
SpineTest::~SpineTest(){
	he::g_EventLoop->RemoveListener(gesture_listener_);
	delete gesture_listener_;

	he::GlobalsDestroy();
}

SpineTest::SpineTest(float width, float height) :
animation_index_(0),
atlas_(nullptr),
drawable_(nullptr),
gesture_listener_(nullptr),
skeletonData_(nullptr)
{
	he::GlobalsInit(width, height);
	
	const std::string loglevel("DEBUG1");
	FILELog::ReportingLevel() = FILELog::FromString(loglevel);
	FILE_LOG(logDEBUG) << "Logging Enabled: SpineTest: " << loglevel << std::endl;

	gesture_listener_ = new he::GestureListener<SpineTest>(this, &SpineTest::HandleGesture);
	he::g_EventLoop->AddListener(gesture_listener_);
	
	// waiting for input...
}

void SpineTest::load(std::string animation_name){
#if defined(SPINEBOY)
	std::string atlas_image_fpath = he::ResourcePath() + "spineboy.png";
	std::string atlas_file_fpath = he::ResourcePath() + "spineboy.plist";
	//	std::string atlas_fpath = he::ResourcePath() + "spineboy.atlas";
	std::string json_fpath = he::ResourcePath() + "spineboy.json";
#endif
	
#if defined(GOBLIN)
	std::string atlas_image_fpath = he::ResourcePath() + "goblin.png";
	std::string atlas_file_fpath = he::ResourcePath() + "goblin.plist";
	//	std::string atlas_fpath = he::ResourcePath() + "goblins.atlas";
	std::string json_fpath = he::ResourcePath() + "goblins.json";
#endif

//	atlas_ = spine::Atlas_readAtlasFile(atlas_fpath.c_str());
//	printf("First region name: %s, x: %d, y: %d\n", atlas_->regions->name, atlas_->regions->x, atlas_->regions->y);
//	printf("First page name: %s, size: %d, %d\n", atlas_->pages->name, atlas_->pages->width, atlas_->pages->height);
	atlas_ = new he::TextureAtlas( atlas_file_fpath, atlas_image_fpath, he::TextureAtlas::Zwoptex);
	
	spine::SkeletonJson* json = new spine::SkeletonJson(atlas_);

	skeletonData_ = json->CreateSkeletonData( json_fpath.c_str());
	if (!skeletonData_) printf("Error: %s\n", json->GetError().c_str());

#if defined(PRINT_LOG)
	printf("Default skin name: %s\n", skeletonData_->GetDefaultSkin()->GetName().c_str());
#endif
	
	spine::Animation* walkAnimation = skeletonData_->FindAnimation( animation_name);

#if defined(PRINT_LOG)
	if (!walkAnimation){
		printf("Error: %s\n", json->GetError().c_str());
	}
	printf("Animation timelineCount: %d\n", walkAnimation->GetTimelineCount());
#endif

	delete json;

	drawable_ = new SkeletonDrawable(skeletonData_);
	drawable_->timeScale_ = 1;

	spine::Skeleton* skeleton = drawable_->skeleton_;
#if defined(GOBLIN)
	Skeleton_setSkinByName(skeleton, "goblin");
	Skeleton_setSlotsToSetupPose(skeleton);
#endif
	
#if defined(SPINEBOY)
	skeleton->SetToSetupPose();
#endif

	skeleton->GetRoot()->SetXY(GLKVector2Make(0,0));
	skeleton->UpdateWorldTransform();
	
	drawable_->state_->SetAnimation( walkAnimation, true);
}

void SpineTest::unload(){
	delete skeletonData_; skeletonData_ = nullptr;
	delete atlas_; atlas_ = nullptr;
	delete drawable_; drawable_ = nullptr;
}

void SpineTest::HandleGesture(const he::Gesture &gesture){
	if(gesture.action_ != he::Gesture::kTap){
		return;
	}
	std::string animations[] = {"walk", "jump"};
	if(++animation_index_ > 1){
		animation_index_ = 0;
	}
	if(drawable_){
		unload();
	}
	load(animations[animation_index_]);
}

void SpineTest::Update(float dt){
	if(drawable_){
		drawable_->Update(dt);
	}
}

void SpineTest::Render(){
	if(drawable_){
		drawable_->Render();
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// MARK: SkeletonDrawable
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

SkeletonDrawable::SkeletonDrawable (spine::SkeletonData* skeletonData, spine::AnimationStateData* stateData) :
timeScale_(1)
{
#if defined(DEBUG_DRAW)
	shader_ = new he::RectColorSh;
#else
	shader_ = new he::RectTextureSh;
#endif
	skeleton_ = new spine::Skeleton(skeletonData);
	state_ = new spine::AnimationState(stateData);
}

SkeletonDrawable::~SkeletonDrawable () {
	delete shader_;
	delete state_;
	delete skeleton_;
}

void SkeletonDrawable::Update (float deltaTime) {
	skeleton_->Update( deltaTime);
	state_->Update(deltaTime * timeScale_);
	state_->Apply( skeleton_);
	skeleton_->UpdateWorldTransform();
}

void SkeletonDrawable::Render() {
	glClearColor(0.5, 0.5, 0.5, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);

	he::VertexData vertexPositions;
	for (int i = 0; i < skeleton_->GetSlotCount(); ++i) {

#if defined(PRINT_LOG)
		printf("Slot #: %d\n",i);
#endif

		spine::Slot* slot = skeleton_->GetSlotAtIndex(i);
		spine::Attachment* attachment = slot->GetAttachment();
		if (!attachment) {

#if defined(PRINT_LOG)
			printf("No attachment!\n");
#endif
			
			continue;
		}
		
		if (attachment->GetType() != spine::ATTACHMENT_REGION){

#if defined(PRINT_LOG)
printf("Attachment is not region!\n");
#endif
			
			continue;
		}
		spine::RegionAttachment* regionAttachment = (spine::RegionAttachment*)attachment;
		vertexPositions = regionAttachment->ComputeVertices( slot);
		
#if defined(DEBUG_DRAW)
		he::VertexCol *vertex_data = new he::VertexCol(0,0);
		vertex_data->position_data_ = he::VertexData(pos_data);
		he::Texture *texture = 0;
#else
		he::TextureAtlas *atlas = regionAttachment->GetRendererObject();;
		const he::TextureAtlasRegion *region = atlas->GetTextureAtlasRegion(regionAttachment->GetName());

#if defined(PRINT_LOG)
		printf("name:\t\t\t\t\t\t\t%s\n"
			   "{{x, y}, {width, height}}:\t\t{{%.2f, %.2f}, {%.2f, %.2f}}\n"
			   "{{u,v},{u2,v2}}:\t\t\t\t{{%.2f, %.2f}, {%.2f, %.2f}}\n"
			   "{offsetX, offsetY}:\t\t\t\t{%.2f, %.2f}\n"
			   "{originalWidth, originalHeight}:\t{%.2f, %.2f}\n"
			   "rotate:\t\t\t\t\t\t\t%s\n"
			   "trimmed:\t\t\t\t\t\t\t%s\n"
			   ,
			   region->name_.c_str(),
			   region->sprite_color_rect_.x, region->sprite_color_rect_.y, region->sprite_color_rect_.z, region->sprite_color_rect_.w,
			   region->tex_coords_.x, region->tex_coords_.y, region->tex_coords_.z, region->tex_coords_.w,
			   region->sprite_offset_.x, region->sprite_offset_.y,
			   region->sprite_source_size_.x, region->sprite_source_size_.y,
			   region->texture_rotated_?"y":"n",
			   region->sprite_trimmed_?"y":"n"
			   );
#endif
		
		he::Texture *texture = atlas->GetTexture();
		
#if defined(PRINT_LOG)
		GLKVector2 tex_size = texture->GetSize();
		printf("size:\t\t\t\t\t\t\t{%.2f, %.2f}\n",tex_size.x,tex_size.y);

		// calc position data
		printf("GLfloat pos_data[] = {\n");
		const GLfloat *pos_data = vertexPositions.GetData();
		for(int vd_indx = 0; vd_indx < 8; vd_indx += 2){
			printf("%.2f, %.2f,\n", pos_data[vd_indx], pos_data[vd_indx+1]);
		}
		printf("};\n");
#endif
		
		GLKVector4 eff_frame = region->sprite_color_rect_;
		//rotate if image is roated
		if(region->texture_rotated_){
			float tmp;
			tmp = eff_frame.z; eff_frame.z = eff_frame.w; eff_frame.w = tmp;

#if defined(PRINT_LOG)
			printf("{{x', y'}, {width', height'}}:\t\t{{%.2f, %.2f}, {%.2f, %.2f}}\n",eff_frame.x, eff_frame.y, eff_frame.z, eff_frame.w);
#endif

		}

		GLKVector4 tex_coords = region->tex_coords_;

#if defined(PRINT_LOG)
		printf("tex_coords:\t\t\t\t\t{{%.2f, %.2f}, {%.2f, %.2f}}\n", tex_coords.x, tex_coords.y, tex_coords.z, tex_coords.w);
#endif

		he::VertexTex vertex_data_tex(eff_frame.z, eff_frame.w, false, tex_coords);
		he::VertexTex *vertex_data = new he::VertexTex(vertexPositions, vertex_data_tex.GetVertexTextureData());
		
#if defined(PRINT_LOG)
		printf("GLfloat tex_data[] = {\n");
		const GLfloat *vtex_data = vertex_data->GetTextureData();
		for(int vd_indx = 0; vd_indx < 8; vd_indx += 2){
			printf("%.2f, %.2f,\n", vtex_data[vd_indx], vtex_data[vd_indx+1]);
		}
		printf("};\n");
#endif

#endif
		GLKVector2 pos = GLKVector2Make(0.0, -150);
		GLKMatrix4 tMat = GLKMatrix4MakeTranslation(pos.x, pos.y, -0.1);
		GLKMatrix4 mvpMat = GLKMatrix4Multiply(he::g_Screen->projection_, tMat);


		GLKVector4 color = GLKVector4Multiply(skeleton_->GetColor(), slot->GetColor());

		he::RenderObject *render_object = new he::RenderObject(vertex_data, shader_, texture, mvpMat, color);
		render_object->Render();
		delete render_object;
		delete vertex_data;
	}
}

// Use this to make use of .atlas files
//GLKVector4 SkeletonDrawable::convert_to_tex_coords(GLKVector4 frame, GLKVector2 fullFrameSize){
//	float u = frame.x;
//	float v = frame.y;
//	v += frame.w;
//	v = fullFrameSize.y - v;
//	float s = u + frame.z;
//	float t = v + frame.w;
//	
//	return GLKVector4Make(u/fullFrameSize.x, v/fullFrameSize.y, s/fullFrameSize.x, t/fullFrameSize.y);
//}

