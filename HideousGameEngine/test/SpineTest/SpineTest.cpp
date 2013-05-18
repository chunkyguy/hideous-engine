//
//  SpineTest.cpp
//  HideousGameEngine
//
//  Created by Sid on 09/05/13.
//  Copyright (c) 2013 whackylabs. All rights reserved.
//

#include "SpineTest.h"

#include <cstdio>
#include <GLKit/GLKMath.h>

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
#include <he/Texture/TextureAtlasParser.h>
#include <he/Vertex/VertexData.h>
#include <he/Utils/DebugLog.h>
#include <he/Utils/ResourcePath.hpp>
#include <he/Utils/Screen.h>

//#define GOBLIN
#define SPINEBOY

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// MARK: SpintTest
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
SpineTest::~SpineTest(){
	delete skeletonData_;
	//Atlas_dispose(atlas_);
	delete atlas_;
	delete drawable_;
}

SpineTest::SpineTest(double width, double height){
	const std::string loglevel("DEBUG1");
	FILELog::ReportingLevel() = FILELog::FromString(loglevel);
	FILE_LOG(logDEBUG) << "Logging Enabled: SpineTest: " << loglevel << std::endl;

	he::g_Screen = he::Screen(width, height);
	
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
	atlas_ = new he::TextureAtlas(atlas_image_fpath, atlas_file_fpath);
	spine::SkeletonJson* json = new spine::SkeletonJson(atlas_);

	skeletonData_ = json->ReadSkeletonDataFile( json_fpath.c_str());
	if (!skeletonData_) printf("Error: %s\n", json->GetError().c_str());
	printf("Default skin name: %s\n", skeletonData_->GetDefaultSkin()->GetName().c_str());
	
	spine::Animation* walkAnimation = skeletonData_->FindAnimation( "jump");
	if (!walkAnimation) printf("Error: %s\n", json->GetError().c_str());
	printf("Animation timelineCount: %d\n", walkAnimation->GetTimelineCount());
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

void SpineTest::Update(double dt){
	drawable_->Update(dt);
}

void SpineTest::Render(){
	drawable_->Render();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// MARK: SkeletonDrawable
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

SkeletonDrawable::SkeletonDrawable (spine::SkeletonData* skeletonData, spine::AnimationStateData* stateData) :
timeScale_(1)
//vertexArray(new VertexArray(Quads, skeletonData->boneCount * 4))
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
		printf("Slot #: %d\n",i);

		spine::Slot* slot = skeleton_->GetSlotAtIndex(i);
		spine::Attachment* attachment = slot->GetAttachment();
		if (!attachment) {
			printf("No attachment!\n");
			continue;
		}
		if (attachment->GetType() != spine::ATTACHMENT_REGION){
			printf("Attachment is not region!\n");
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
		he::TextureAtlasRegion region = atlas->GetTextureAtlasRegion(regionAttachment->GetName());
		printf("name:\t\t\t\t\t\t\t%s\n"
			   "{{x, y}, {width, height}}:\t\t{{%.2f, %.2f}, {%.2f, %.2f}}\n"
			   "{{u,v},{u2,v2}}:\t\t\t\t{{%.2f, %.2f}, {%.2f, %.2f}}\n"
			   "{offsetX, offsetY}:\t\t\t\t{%.2f, %.2f}\n"
			   "{originalWidth, originalHeight}:\t{%.2f, %.2f}\n"
			   "rotate:\t\t\t\t\t\t\t%s\n"
			   "trimmed:\t\t\t\t\t\t\t%s\n"
			   ,
			   region.name.c_str(),
			   region.sprite_color_rect.x, region.sprite_color_rect.y, region.sprite_color_rect.z, region.sprite_color_rect.w,
			   region.tex_coords.x, region.tex_coords.y, region.tex_coords.z, region.tex_coords.w,
			   region.sprite_offset.x, region.sprite_offset.y,
			   region.sprite_source_size.x, region.sprite_source_size.y,
			   region.texture_rotated?"y":"n",
			   region.sprite_trimmed?"y":"n"
			   );

		he::Texture *texture = atlas->texture_;
		GLKVector2 tex_size = texture->GetSize();
		printf("size:\t\t\t\t\t\t\t{%.2f, %.2f}\n",tex_size.x,tex_size.y);

		// calc position data
		printf("GLfloat pos_data[] = {\n");
		GLfloat *pos_data = vertexPositions.GetData();
		for(int vd_indx = 0; vd_indx < 8; vd_indx += 2){
			printf("%.2f, %.2f,\n", pos_data[vd_indx], pos_data[vd_indx+1]);
		}
		printf("};\n");

		GLKVector4 eff_frame = region.sprite_color_rect;
		//rotate if image is roated
		if(region.texture_rotated){
			float tmp;
			tmp = eff_frame.z; eff_frame.z = eff_frame.w; eff_frame.w = tmp;
			printf("{{x', y'}, {width', height'}}:\t\t{{%.2f, %.2f}, {%.2f, %.2f}}\n",eff_frame.x, eff_frame.y, eff_frame.z, eff_frame.w);

//			pos_data[0] = vertexPositions[spine::VERTEX_Y1];		pos_data[1] = vertexPositions[spine::VERTEX_X1];
//			pos_data[2] = vertexPositions[spine::VERTEX_Y4];		pos_data[3] = vertexPositions[spine::VERTEX_X4];
//			pos_data[4] = vertexPositions[spine::VERTEX_Y2];		pos_data[5] = vertexPositions[spine::VERTEX_X2];
//			pos_data[6] = vertexPositions[spine::VERTEX_Y3];		pos_data[7] = vertexPositions[spine::VERTEX_X3];
//			
//			printf("GLfloat pos_data'[] = {\n");
//			for(int vd_indx = 0; vd_indx < 8; vd_indx += 2){
//				printf("%.2f, %.2f,\n", pos_data[vd_indx], pos_data[vd_indx+1]);
//			}
//			printf("};\n");
		}

		GLKVector4 tex_coords = region.tex_coords;
		printf("tex_coords:\t\t\t\t\t{{%.2f, %.2f}, {%.2f, %.2f}}\n", tex_coords.x, tex_coords.y, tex_coords.z, tex_coords.w);
		
		he::VertexTex *vertex_data = new he::VertexTex(eff_frame.z, eff_frame.w, false, tex_coords);
		
		vertex_data->position_data_ = vertexPositions;
		
		printf("GLfloat tex_data[] = {\n");
		GLfloat *vtex_data = vertex_data->texture_data_.GetData();
		for(int vd_indx = 0; vd_indx < 8; vd_indx += 2){
			printf("%.2f, %.2f,\n", vtex_data[vd_indx], vtex_data[vd_indx+1]);
		}
		printf("};\n");

#endif
		GLKVector2 pos = GLKVector2Make(0.0, -150);
		GLKMatrix4 tMat = GLKMatrix4MakeTranslation(pos.x, pos.y, -0.1);
		GLKMatrix4 mvpMat = GLKMatrix4Multiply(he::g_Screen.projection_, tMat);


		GLKVector4 color = GLKVector4Multiply(skeleton_->GetColor(), slot->GetColor());

		he::RenderObject *render_object = new he::RenderObject(vertex_data, shader_, texture, mvpMat, color);
		render_object->Render();
		delete render_object;
		delete vertex_data;
	}
}

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

