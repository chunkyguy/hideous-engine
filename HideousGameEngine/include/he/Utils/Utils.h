//
//  Utils.h
//  HideousGameEngine
//
//  Created by Sid on 13/02/13.
//  Copyright (c) 2013 whackylabs. All rights reserved.
//
//	General Utilities inline functions

#ifndef __HideousGameEngine__Utils__
#define __HideousGameEngine__Utils__

#include <OpenGLES/ES2/gl.h>
#include <cstdlib>
#include <string>
#include <he/Utils/GLKMath_Additions.h>

#include <he/Utils/Screen.h>

// A macro to disallow the copy constructor and operator= functions
// This should be used in the private: declarations for a class
#define DISALLOW_COPY_AND_ASSIGN(TypeName) \
TypeName(const TypeName&);               \
void operator=(const TypeName&)

namespace he{

 /**
  *	Convert a hex color to RGBA
  *
  *	@param	hex_color	Some 4 channel hex color, eg: 0xd6008bff
  *
  *	@return	Color components.
  */
 GLKVector4 Color_HexToRGBA(unsigned long hex_color);
 
 /**
  *	Determines if the lines intersect.
  *	Given two line segments:
  *	[p, p+r], [q, q+s]
  *	t = ((q-p) x s) / (r x s)
  *	u = ((q-p) x r) / (r x s)
  *
  *	Each cross product is evaluated as the z-component in a 3D cross
  *	Like, p x q = (p.x * q.y) - (p.y * q.x)
  *
  *	@param	p
  *	@param	p_plus_r
  *	@param	q
  *	@param	q_plus_s
  *
  *	@return	0 if not intersect, else intersect (bool)
  */
 bool LinesIntersect(GLKVector2 p, GLKVector2 p_plus_r, GLKVector2 q, GLKVector2 q_plus_s);
 
 // buffer offset calc for VBO data stride
 inline const GLvoid *BufferOffset(int off){
  return static_cast<char *>(0) + off;
 }
 
 // next power of 2
 int NextPOT(int a);
 
 // Returns a value between [start, end]
 // random has to be between [start, end]. Hint: use Randf() to create random
 template<typename T>
 inline T Rand(const T &start, const T &end, const T &random){
  return start + random * (end - start);
 }
 
 //Returns a value between [start, end]; Default: [0.0, 1.0]
 inline float Randf(float start = 0.0, float end = 1.0){
  return start + static_cast<float>(rand())/static_cast<float>(RAND_MAX) * (end - start);
 }
 
 //	Convert point from CoreGraphics coordinates space to OpenGL coordinate space
 inline GLKVector2 CGtoGL(GLKVector2 cg_point){
  return GLKVector2Make(cg_point.x - g_Screen->width_/2, g_Screen->height_/2 - cg_point.y);
 }
 
 /** Converts to names generated by flash generated xmls
  @note For eg: converts 'head' to 'head instance 10000'
  @param name The symbol name.
  @param frame_number The frame-number added at the end.
  */
 std::string FlashFullName(const std::string &name, const int frame_number = 0);
 
 class FileBuffer{
 public:
  FileBuffer(const std::string &path);
  ~FileBuffer();
  std::string GetString() const;
  const char *GetData() const;
  int GetLength() const;
  
 private:
  char *buffer_;
  int length_;
 };
}
#endif /* defined(__HideousGameEngine__Utils__) */
