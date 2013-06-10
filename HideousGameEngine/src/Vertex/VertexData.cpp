//
//  VertexData.cpp
//  HEAssets
//
//  Created by Sid on 22/04/13.
//  Copyright (c) 2013 whackylabs. All rights reserved.
//

#include <he/Vertex/VertexData.h>

namespace he{
	namespace Vertex {
		
		int V2::vertex_count = 2;
		int V3::vertex_count = 3;
		int V4::vertex_count = 4;
		
		GLKVector2 GetVertex(const V2 &v, const Index vi){
			int start = vi * V2::vertex_count;
			return GLKVector2Make(v.data[start], v.data[start+1]);
		}
		GLKVector3 GetVertex(const V3 &v, const Index vi){
			int start = vi * V3::vertex_count;
			return GLKVector3Make(v.data[start], v.data[start+1], v.data[start+2]);
		}
		GLKVector4 GetVertex(const V4 &v, const Index vi){
			int start = vi * V4::vertex_count;
			return GLKVector4Make(v.data[start], v.data[start+1], v.data[start+2], v.data[start+3]);
		}
		
		std::ostream &operator<<(std::ostream &os, const V2 &slf){
			os << "A: " << GetVertex(slf, kA) << "\n";
			os << "B: " << GetVertex(slf, kB) << "\n";
			os << "C: " << GetVertex(slf, kC) << "\n";
			os << "D: " << GetVertex(slf, kD) << "\n";
			return os;
		}
		std::ostream &operator<<(std::ostream &os, const V3 &slf){
			os << "A: " << GetVertex(slf, kA) << "\n";
			os << "B: " << GetVertex(slf, kB) << "\n";
			os << "C: " << GetVertex(slf, kC) << "\n";
			os << "D: " << GetVertex(slf, kD) << "\n";
			return os;
		}
		std::ostream &operator<<(std::ostream &os, const V4 &slf){
			os << "A: " << GetVertex(slf, kA) << "\n";
			os << "B: " << GetVertex(slf, kB) << "\n";
			os << "C: " << GetVertex(slf, kC) << "\n";
			os << "D: " << GetVertex(slf, kD) << "\n";
			return os;
		}
		
		void Set(V2 &slf, const GLKVector2 &a, const GLKVector2 &d){
			GLfloat data[8] = {
				a.x, a.y,	//A
				d.x, a.y,	//B
				a.x, d.y,	//C
				d.x, d.y,	//D
			};
			Set(slf, data);
		}
		
		bool Contains(const V2 &v, const GLKVector2 &point) {
			return ((point.x > v.data[0] && point.x < v.data[6]) && (point.y > v.data[1] && point.y < v.data[7]));
		}
		
		bool Contains(const V2 &slf, const V2 &other) {
			return (Contains(slf, GetVertex(other, kA)) && Contains(slf, GetVertex(other, kB)) && Contains(slf, GetVertex(other, kC)) && Contains(slf, GetVertex(other, kD)));
		}
		
	}
	/*
	 //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	 // MARK:	Vertex2
	 //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	 
	 //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	 // MARK:	Vertex3
	 //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	 
	 //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	 // MARK:	Vertex4
	 //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	 
	 
	 
	 //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	 // MARK:	VertexData2
	 //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	 VertexData2::VertexData2(){
	 GLfloat data[8] = {0};
	 load(data);
	 }
	 VertexData2::VertexData2(const GLfloat *data){
	 load(data);
	 }
	 VertexData2::VertexData2(const GLKVector2 &a, const GLKVector2 &b, const GLKVector2 &c, const GLKVector2 &d){
	 GLfloat data[8] = {
	 a.x, a.y,	//A
	 b.x, b.y,	//B
	 c.x, c.y,	//C
	 d.x, d.y,	//D
	 };
	 load(data);
	 }
	 VertexData2::VertexData2(const GLfloat a_x, const GLfloat a_y, const GLfloat d_x, const GLfloat d_y){
	 GLfloat data[8] = {
	 a_x, a_y,	//A
	 d_x, a_y,	//B
	 a_x, d_y,	//C
	 d_x, d_y,	//D
	 };
	 load(data);
	 }
	 VertexData2::VertexData2(const GLKVector2 &a, const GLKVector2 &d){
	 GLfloat data[8] = {
	 a.x, a.y,	//A
	 d.x, a.y,	//B
	 a.x, d.y,	//C
	 d.x, d.y,	//D
	 };
	 load(data);
	 }
	 VertexData2::VertexData2(const GLKVector4 &a_d){
	 GLfloat data[8] = {
	 a_d.x, a_d.y,	//A
	 a_d.z, a_d.y,	//B
	 a_d.x, a_d.w,	//C
	 a_d.z, a_d.w,	//D
	 };
	 load(data);
	 }
	 
	 void VertexData2::load(const GLfloat *data){
	 for(int i = 0; i < 8; ++i){
	 data_[i] = data[i];
	 }
	 }
	 
	 const GLfloat *VertexData2::GetData() const{
	 return &data_[0];
	 }
	 
	 const GLsizei VertexData2::GetSize() const{
	 return sizeof(data_);
	 }
	 
	 bool VertexData2::Contains(const GLfloat x, const GLfloat y) const{
	 //printf("%f %f %f %f %f %f\n",x,y,data[eAx],data[eAy],data[eDx],data[eDy]);
	 return ((x > data_[Ax] && x < data_[Dx]) && (y > data_[Ay] && y < data_[Dy]));
	 }
	 
	 bool VertexData2::Contains(const GLKVector2 &point) const{
	 return Contains(point.x, point.y);
	 }
	 
	 bool VertexData2::Contains(const he::VertexData2 &other) const{
	 return (Contains(other.GetVertex(kVertexA)) && Contains(other.GetVertex(kVertexB)) && Contains(other.GetVertex(kVertexC)) && Contains(other.GetVertex(kVertexD)));
	 }
	 
	 void VertexData2::Translate(const GLfloat x, const GLfloat y){
	 int j = 0;
	 for(int i = 0; i < 4; ++i){
	 data_[j++] += x;
	 data_[j++] += y;
	 }
	 }
	 void VertexData2::Translate(const GLKVector2 &point){
	 Translate(point.x, point.y);
	 }
	 
	 void VertexData2::Scale(const GLfloat x, const GLfloat y){
	 int j = 0;
	 for(int i = 0; i < 4; ++i){
	 data_[j++] *= x;
	 data_[j++] *= y;
	 }
	 }
	 void VertexData2::Scale(const GLKVector2 &value){
	 Scale(value.x, value.y);
	 }
	 
	 void VertexData2::SetVertex(const VertexIndex index, const GLKVector2 &value){
	 switch(index){
	 case kVertexA:
	 data_[Ax] = value.x; data_[Ay] = value.y;	//A
	 break;
	 case kVertexB:
	 data_[Bx] = value.x; data_[By] = value.y;	//B
	 break;
	 case kVertexC:
	 data_[Cx] = value.x; data_[Cy] = value.y;	//C
	 break;
	 case kVertexD:
	 data_[Dx] = value.x; data_[Dy] = value.y;	//D
	 break;
	 }
	 }
	 const GLKVector2 VertexData2::GetVertex(const VertexIndex index) const{
	 GLKVector2 ret;
	 switch(index){
	 case kVertexA:
	 ret.x = data_[Ax]; ret.y = data_[Ay];	//A
	 break;
	 case kVertexB:
	 ret.x = data_[Bx]; ret.y = data_[By];	//B
	 break;
	 case kVertexC:
	 ret.x = data_[Cx]; ret.y = data_[Cy];	//C
	 break;
	 case kVertexD:
	 ret.x = data_[Dx]; ret.y = data_[Dy];	//D
	 break;
	 }
	 return ret;
	 }
	 
	 std::ostream &operator<<(std::ostream &os, const VertexData2 &data){
	 os << "A: " << data.GetVertex(kVertexA) << "\n";
	 os << "B: " << data.GetVertex(kVertexB) << "\n";
	 os << "C: " << data.GetVertex(kVertexC) << "\n";
	 os << "D: " << data.GetVertex(kVertexD) << "\n";
	 return os;
	 }
	 */
}
///EOF
