//
//  Utils.cpp
//  HideousGameEngine
//
//  Created by Sid on 13/02/13.
//  Copyright (c) 2013 whackylabs. All rights reserved.
//

#include <he/Utils/Utils.h>

#include <fstream>
#include <sstream>


namespace he{
 
 //Set to next power of 2
 int NextPOT (int a){
  int rval = 1;
  while(rval<a)
   rval <<= 1;
  return rval;
 }
 
 std::string FlashFullName(const std::string &name, const int frame_number){
  std::stringstream stream;
  stream << name << " instance " << 10000 + frame_number; 		// head instance 10000
  return stream.str();
 }
 
 
 FileBuffer::FileBuffer(const std::string &path){
  std::ifstream fin;
  fin.open(path.c_str());
  assert(fin.is_open());
  
  fin.seekg(0, std::ios::end);
  length_ = fin.tellg();
  fin.seekg(0, std::ios::beg);
  buffer_ = new char[length_ + 1];
  fin.read(buffer_, length_);
  buffer_[length_] = 0;
 }
 FileBuffer::~FileBuffer(){
  delete buffer_;
  buffer_ = 0;
 }
 std::string FileBuffer::GetString() const{
  return std::string(buffer_);
 }
 const char *FileBuffer::GetData() const{
  return buffer_;
 }
 int FileBuffer::GetLength() const{
  return length_;
 }
 
 //#define ENABLE_COLLISION_TRACE
 
#define CROSS_Z(a, b) ((a.x*b.y) - (a.y*b.x))
 
 bool LinesIntersect(GLKVector2 p, GLKVector2 p_plus_r, GLKVector2 q, GLKVector2 q_plus_s) {
  //		printf("Processing: {{%f,%f},{%f,%f}},{{%f,%f},{%f,%f}}\n",p.x,p.y,p_plus_r.x,p_plus_r.y,q.x,q.y,q_plus_s.x,q_plus_s.y);
  
  /* Calculate q - p */
  GLKVector2 q_p	= {
   q.x - p.x,
   q.y - p.y
  };
  
  /* Calculate r */
  GLKVector2 r = {
   p_plus_r.x - p.x,
   p_plus_r.y - p.y
  };
  
  /* Calculate s */
  GLKVector2 s = {
   q_plus_s.x - q.x,
   q_plus_s.y - q.y
  };
  
  /* Calculate (q-p) x r */
  float q_pxr = CROSS_Z(q_p, r);
  
  /* Calculate (q-p) x s */
  float q_pxs = CROSS_Z(q_p, s);
  
  /* Calculate (r x s) */
  float rxs = CROSS_Z(r,s);
  
  if (q_pxr == 0.0f) {
   //			printf("Lines are collinear, and so intersect if they have any overlap.\n");
   // Assume edge case as failure
   return false;
   //		return ((q.x - p.x < 0.0f) != (q.x - p_plus_r.x < 0.0f)) ||
   //				((q.y - p.y < 0.0f) != (q.y - p_plus_r.y < 0.0f));
  }
  
  if (rxs == 0.0f) {
   //			printf("Lines are parallel.\n");
   return false;
  }
  
  /* Calculate 1 / (rxs) */
  float one_div_rxs = 1.0f / rxs;
  
  /* Calculate t */
  float t = q_pxs * one_div_rxs;
  
  /* Calculate u */
  float u = q_pxr * one_div_rxs;
  
  return (t >= 0.0f) && (t <= 1.0f) && (u >= 0.0f) && (u <= 1.0f);
 }
 
#define kColor_HexToRGBA(channel) (((hex_color >> ((3 - channel)* 8 )) & 0xff) / 255.0f)
 GLKVector4 Color_HexToRGBA(unsigned long hex_color) {
  GLKVector4 comp_color = {
   kColor_HexToRGBA(0), // Red
   kColor_HexToRGBA(1), // Green
   kColor_HexToRGBA(2), // Blue
   kColor_HexToRGBA(3)  // Alpha
  };
  return comp_color;
 }
 
}
//EOF