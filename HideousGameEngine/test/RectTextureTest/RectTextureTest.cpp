//
//  RectTextureTest.cpp
//  HideousGameEngine
//
//  Created by Sid on 11/02/13.
//  Copyright (c) 2013 whackylabs. All rights reserved.
//

#include "RectTextureTest.h"

#include <he/RenderObject/RenderObject.h>
#include <he/Shaders/TextureShader.h>
#include <he/Texture/Texture.h>
#include <he/Texture/TextureAtlas.h>
#include <he/Utils/DebugLog.h>
#include <he/Utils/ResourcePath.hpp>
#include <he/Utils/Utils.h>
#include <he/Vertex/TextureVertex.h>

RectTextureTest::~RectTextureTest(){
 unload_textures();
 he::g_EventLoop->RemoveListener(gesture_listener_);
 delete gesture_listener_;
}

RectTextureTest::RectTextureTest():
atlas_()
{
 for (int i = 0; i < 2; ++i) {
  atlas_[i] = 0;
 }
}

void RectTextureTest::init(){
 //debugger
 const std::string loglevel("DEBUG1");
 FILELog::ReportingLevel() = FILELog::FromString(loglevel);
 FILE_LOG(logDEBUG) << "Logging Enabled: " << loglevel << std::endl;
 
 //random
 srand(time(NULL));
 
 gesture_listener_ = new he::GestureListener<RectTextureTest>(this, &RectTextureTest::HandleGesture);
 he::g_EventLoop->AddListener(gesture_listener_);
 // waiting for input
}

void RectTextureTest::update(float dt){
}

void RectTextureTest::render(){
 for(std::list<he::RenderObject *>::iterator it = render_objects_.begin(); it != render_objects_.end(); ++it){
  (*it)->Render();
 }
}

void RectTextureTest::load_textures(){
 if(!textures_.empty()){
  unload_textures();
 }
 
 GLKVector2 pos;
 GLKMatrix4 tMat;
 GLKMatrix4 mvpMat;
 he::TextureVertex *v;
 shader_ = new he::TextureShader;
 
#if defined(SPINE_TEXTURE_OBJECT)
 //Draw a texture in proportion
 load_goblin();
 //load_spineboy();
 return;
#endif
 
 he::Texture *r1t = new he::Texture(he::ResourcePath() + "texture.png");
 GLKVector2 size = GLKVector2Make(200, 200);
 v = new he::TextureVertex(size);
 
 pos = GLKVector2Make(-150.0, 0.0);
 tMat = GLKMatrix4MakeTranslation(pos.x, pos.y, -0.1);
 mvpMat = GLKMatrix4Multiply(he::g_Screen->projection_, tMat);
 he::RenderObject *r = new he::RenderObject(v, shader_, r1t, mvpMat);
 render_objects_.push_back(r);
 textures_.push_back(r1t);
 vertex_datas_.push_back(v);
 
 //Draw a texture out of proportion
 he::Texture *r2t = new he::Texture(he::ResourcePath() + "texture_alpha.png");
 size = GLKVector2Make(50, 25);
 v = new he::TextureVertex(size);
 pos = GLKVector2Make(-50.0, 0.0);
 tMat = GLKMatrix4MakeTranslation(pos.x, pos.y, -0.1);
 mvpMat = GLKMatrix4Multiply(he::g_Screen->projection_, tMat);
 he::RenderObject *r2 = new he::RenderObject(v, shader_, r2t, mvpMat);
 render_objects_.push_back(r2);
 textures_.push_back(r2t);
 vertex_datas_.push_back(v);
 
 //Draw a texture from atlas
 atlas_[0] = new he::TextureAtlas( he::ResourcePath() + "tex_atlas.plist", he::ResourcePath() + "tex_atlas.png", he::TextureAtlas::kZwoptex);
 atlas_[1] = new he::TextureAtlas(he::ResourcePath()+"playscreen_ss.xml", he::ResourcePath()+"playscreen_ss.png", he::TextureAtlas::kStarling);
 //fish
 for(int i = 0; i < 2; ++i){
  GLKVector2 size = GLKVector2Make(100, 100);
  v = CreateTextureData(atlas_[0], "fish.png",  i%2, size);
  GLKVector2 pos = GLKVector2Make(50.0, -100.0 + i*100.0);
  GLKMatrix4 tMat = GLKMatrix4MakeTranslation(pos.x, pos.y, -0.1);
  GLKMatrix4 mvpMat = GLKMatrix4Multiply(he::g_Screen->projection_, tMat);
  he::RenderObject *r3 = new he::RenderObject(v, shader_, atlas_[0]->GetTexture(), mvpMat);
  render_objects_.push_back(r3);
  vertex_datas_.push_back(v);
 }
 
 //rope
 v = CreateTextureData(atlas_[0], "rope.png");
 pos = GLKVector2Make(150.0, 0.0);
 tMat = GLKMatrix4MakeTranslation(pos.x, pos.y, -0.1);
 mvpMat = GLKMatrix4Multiply(he::g_Screen->projection_, tMat);
 he::RenderObject *r4 = new he::RenderObject(v, shader_, atlas_[0]->GetTexture(), mvpMat);
 render_objects_.push_back(r4);
 vertex_datas_.push_back(v);
 
 //seaweed
 v = CreateTextureData(atlas_[0], "seaweed.png", 100.0);
 pos = GLKVector2Make(0.0, -100.0);
 tMat = GLKMatrix4MakeTranslation(pos.x, pos.y, -0.1);
 mvpMat = GLKMatrix4Multiply(he::g_Screen->projection_, tMat);
 he::RenderObject *r5 = new he::RenderObject(v, shader_, atlas_[0]->GetTexture(), mvpMat);
 render_objects_.push_back(r5);
 vertex_datas_.push_back(v);

 //image with artiface
 v = CreateTextureData(atlas_[1], "mc_deadfish instance 10014");
 assert(v);
 pos = GLKVector2Make(100.0, 0.0);
 tMat = GLKMatrix4MakeTranslation(pos.x, pos.y, -0.1);
 mvpMat = GLKMatrix4Multiply(he::g_Screen->projection_, tMat);
 he::RenderObject *r6 = new he::RenderObject(v, shader_, atlas_[1]->GetTexture(), mvpMat);
 render_objects_.push_back(r6);
 vertex_datas_.push_back(v);

}

void RectTextureTest::unload_textures(){
 for(std::list<he::RenderObject *>::iterator it = render_objects_.begin(); it != render_objects_.end(); ++it){
  delete *it;
 }
 render_objects_.clear();
 for(std::list<he::Texture *>::iterator it = textures_.begin(); it != textures_.end(); ++it){
  delete *it;
 }
 textures_.clear();
 for(std::list<he::TextureVertex *>::iterator it = vertex_datas_.begin(); it != vertex_datas_.end(); ++it){
  delete *it;
 }
 vertex_datas_.clear();
 for (int i = 0; i < 2; ++i) {
  if(atlas_[i]) delete atlas_[i];
 }
 if(shader_) delete shader_;
}

void RectTextureTest::HandleGesture(const he::Gesture &gesture){
 if(gesture.action_ == he::Gesture::kTap){
  load_textures();
 }
}

#if defined(SPINE_TEXTURE_OBJECT)
void RectTextureTest::load_goblin(){
 std::string atlas_fpath = he::ResourcePath() + "goblins.atlas";
 spine_atlas_ = spine::Atlas_readAtlasFile(atlas_fpath.c_str());
 GLKVector2 pos;
 GLKMatrix4 tMat;
 GLKMatrix4 mvpMat;
 he::TextureVertex *vertex_data;
 
 he::Texture *goblin_tex = new he::Texture(he::ResourcePath() + "goblins.png");
 
 GLKVector2 tex_size = goblin_tex->GetSize();
 printf("size:\t\t\t\t\t\t\t{%.2f, %.2f}\n",tex_size.x,tex_size.y);
 
 static int sprite_index = 0;
 const char *sprites[] = {
  "spear", "goblingirl/head", "goblin/head", "goblin/torso", "goblin/right-upper-leg", "goblin/left-lower-leg",
  "goblingirl/left-lower-leg", "goblin/undie-straps", "dagger", "goblingirl/torso", "goblin/right-lower-leg",
  "goblingirl/right-lower-leg", "goblin/left-upper-leg", "goblin/pelvis", "goblin/left-hand", "goblingirl/left-upper-leg",
  "goblin/left-foot", "goblingirl/left-foot", "goblin/right-foot", "goblingirl/right-foot", "goblingirl/pelvis",
  "goblingirl/right-upper-leg", "goblin/right-shoulder", "goblingirl/undie-straps", "goblingirl/right-shoulder",
  "goblin/left-arm", "goblin/neck", "goblingirl/left-hand", "goblingirl/right-arm", "goblingirl/neck",
  "goblin/left-shoulder", "goblingirl/left-shoulder", "goblingirl/left-arm", "goblin/right-arm", "goblin/right-hand",
  "goblingirl/right-hand","goblin/undies","goblingirl/undies","goblingirl/eyes-closed","goblin/eyes-closed"
 };
 if(sprite_index >= sizeof(sprites)/sizeof(sprites[0])){
  sprite_index = 0;
 }
 
 spine::AtlasRegion *region = Atlas_findRegion(spine_atlas_, sprites[sprite_index++]);
 printf("name:\t\t\t\t\t\t\t%s\n"
        "{{x, y}, {width, height}}:\t\t{{%d, %d}, {%d, %d}}\n"
        "{{u,v},{u2,v2}}:\t\t\t\t{{%.2f, %.2f}, {%.2f, %.2f}}\n"
        "{offsetX, offsetY}:\t\t\t\t{%d, %d}\n"
        "{originalWidth, originalHeight}:\t{%d, %d}\n"
        "rotate:\t\t\t\t\t\t\t%d\n"
        "flip:\t\t\t\t\t\t\t%d\n"
        ,
        region->name,
        region->x, region->y,region->width, region->height,
        region->u, region->v, region->u2, region->v2,
        region->offsetX, region->offsetY,
        region->originalWidth, region->originalHeight,
        region->rotate,
        region->flip
        );
 
 GLKVector4 eff_frame = GLKVector4Make(region->x, region->y, region->width,region->height);
 //rotate if image is roated
 if(region->rotate){
  float tmp = eff_frame.z;
  eff_frame.z = eff_frame.w;
  eff_frame.w = tmp;
  printf("{{x', y'}, {width', height'}}:\t\t{{%.2f, %.2f}, {%.2f, %.2f}}\n",eff_frame.x, eff_frame.y, eff_frame.z, eff_frame.w);
 }
 GLKVector4 tex_coords = convert_to_tex_coords(eff_frame, tex_size);
 //	tex_coords = GLKVector4Make(region->u, region->v, region->u2, region->v2);
 printf("tex_coords:\t\t\t\t\t{{%.2f, %.2f}, {%.2f, %.2f}}\n", tex_coords.x, tex_coords.y, tex_coords.z, tex_coords.w);
 
 vertex_data = new he::TextureVertex(eff_frame.z, eff_frame.w, false, tex_coords);
 printf("GLfloat pos_data[] = {\n");
 GLfloat *vpos_data = vertex_data->position_data_.GetData();
 for(int vd_indx = 0; vd_indx < 8; vd_indx += 2){
  printf("%.2f, %.2f,\n", vpos_data[vd_indx], vpos_data[vd_indx+1]);
 }
 printf("};\n");
 GLfloat *vtex_data = vertex_data->texture_data_.GetData();
 printf("GLfloat tex_data[] = {\n");
 for(int vd_indx = 0; vd_indx < 8; vd_indx += 2){
  printf("%.2f, %.2f,\n", vtex_data[vd_indx], vtex_data[vd_indx+1]);
 }
 printf("};\n");
 
 pos = GLKVector2Make(0.0, 0.0);
 tMat = GLKMatrix4MakeTranslation(pos.x, pos.y, -0.1);
 mvpMat = GLKMatrix4Multiply(he::g_Screen.projection_, tMat);
 he::RenderObject *goblin = new he::RenderObject(vertex_data, shader_, goblin_tex, mvpMat);
 render_objects_.push_back(goblin);
 vertex_datas_.push_back(vertex_data);
 textures_.push_back(goblin_tex);
}

void RectTextureTest::load_spineboy(){
 std::string atlas_fpath = he::ResourcePath() + "spineboy.atlas";
 spine_atlas_ = spine::Atlas_readAtlasFile(atlas_fpath.c_str());
 GLKVector2 pos;
 GLKMatrix4 tMat;
 GLKMatrix4 mvpMat;
 he::TextureVertex *v;
 he::Texture *goblin_tex = new he::Texture(he::ResourcePath() + "spineboy.png");
 spine::AtlasRegion *region = Atlas_findRegion(spine_atlas_, "head");
 //	GLKVector4 draw_frame = GLKVector4Make(1, 122, 121, 132);
 GLKVector4 draw_frame = GLKVector4Make(region->x, region->y, region->width,region->height);
 v = new he::TextureVertex(121, 132, false, convert_to_tex_coords(draw_frame, goblin_tex->GetSize()));
 pos = GLKVector2Make(0.0, 0.0);
 tMat = GLKMatrix4MakeTranslation(pos.x, pos.y, -0.1);
 mvpMat = GLKMatrix4Multiply(he::g_Screen.projection_, tMat);
 he::RenderObject *goblin = new he::RenderObject(v, shader_, goblin_tex, mvpMat);
 render_objects_.push_back(goblin);
 textures_.push_back(goblin_tex);
 vertex_datas_.push_back(v);
}

GLKVector4 RectTextureTest::convert_to_tex_coords(GLKVector4 frame, GLKVector2 fullFrameSize){
 
 float u = frame.x;
 float v = frame.y;
 v += frame.w;
 v = fullFrameSize.y - v;
 float s = u + frame.z;
 float t = v + frame.w;
 
 return GLKVector4Make(u/fullFrameSize.x, v/fullFrameSize.y, s/fullFrameSize.x, t/fullFrameSize.y);
}
#endif
//EOF