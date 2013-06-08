//
//  VertexData.cpp
//  HEAssets
//
//  Created by Sid on 22/04/13.
//  Copyright (c) 2013 whackylabs. All rights reserved.
//

#include <he/Vertex/VertexData.h>

namespace he{
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// MARK:	VertexData
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	VertexData::VertexData(){
		GLfloat data[8] = {0};
		load(data);
	}
	VertexData::VertexData(const GLfloat *data){
		load(data);
	}
	VertexData::VertexData(const GLKVector2 &a, const GLKVector2 &b, const GLKVector2 &c, const GLKVector2 &d){
		GLfloat data[8] = {
			a.x, a.y,	//A
			b.x, b.y,	//B
			c.x, c.y,	//C
			d.x, d.y,	//D
		};
		load(data);
	}
	VertexData::VertexData(const GLfloat a_x, const GLfloat a_y, const GLfloat d_x, const GLfloat d_y){
		GLfloat data[8] = {
			a_x, a_y,	//A
			d_x, a_y,	//B
			a_x, d_y,	//C
			d_x, d_y,	//D
		};
		load(data);
	}
	VertexData::VertexData(const GLKVector2 &a, const GLKVector2 &d){
		GLfloat data[8] = {
			a.x, a.y,	//A
			d.x, a.y,	//B
			a.x, d.y,	//C
			d.x, d.y,	//D
		};
		load(data);
	}
	VertexData::VertexData(const GLKVector4 &a_d){
		GLfloat data[8] = {
			a_d.x, a_d.y,	//A
			a_d.z, a_d.y,	//B
			a_d.x, a_d.w,	//C
			a_d.z, a_d.w,	//D
		};
		load(data);
	}

	void VertexData::load(const GLfloat *data){
		for(int i = 0; i < 8; ++i){
			data_[i] = data[i];
		}
	}
	
	const GLfloat *VertexData::GetData() const{
		return &data_[0];
	}
	
	const GLsizei VertexData::GetSize() const{
		return sizeof(data_);
	}
	
	bool VertexData::Contains(const GLfloat x, const GLfloat y) const{
		//printf("%f %f %f %f %f %f\n",x,y,data[eAx],data[eAy],data[eDx],data[eDy]);
		return ((x > data_[Ax] && x < data_[Dx]) && (y > data_[Ay] && y < data_[Dy]));
	}
	
	bool VertexData::Contains(const GLKVector2 &point) const{
		return Contains(point.x, point.y);
	}

	bool VertexData::Contains(const he::VertexData &other) const{
		return (Contains(other.GetVertex(kA)) && Contains(other.GetVertex(kB)) && Contains(other.GetVertex(kC)) && Contains(other.GetVertex(kD)));
	}
	
	void VertexData::Translate(const GLfloat x, const GLfloat y){
		int j = 0;
		for(int i = 0; i < 4; ++i){
			data_[j++] += x;
			data_[j++] += y;
		}
	}
	void VertexData::Translate(const GLKVector2 &point){
		Translate(point.x, point.y);
	}
	
	void VertexData::Scale(const GLfloat x, const GLfloat y){
		int j = 0;
		for(int i = 0; i < 4; ++i){
			data_[j++] *= x;
			data_[j++] *= y;
		}
	}
	void VertexData::Scale(const GLKVector2 &value){
		Scale(value.x, value.y);
	}

	void VertexData::SetVertex(const VertexIndex index, const GLKVector2 &value){
		switch(index){
			case kA:
				data_[Ax] = value.x; data_[Ay] = value.y;	//A
				break;
			case kB:
				data_[Bx] = value.x; data_[By] = value.y;	//B
				break;
			case kC:
				data_[Cx] = value.x; data_[Cy] = value.y;	//C
				break;
			case kD:
				data_[Dx] = value.x; data_[Dy] = value.y;	//D
				break;
		}
	}
	const GLKVector2 VertexData::GetVertex(const VertexIndex index) const{
		GLKVector2 ret;
		switch(index){
			case kA:
				ret.x = data_[Ax]; ret.y = data_[Ay];	//A
				break;
			case kB:
				ret.x = data_[Bx]; ret.y = data_[By];	//B
				break;
			case kC:
				ret.x = data_[Cx]; ret.y = data_[Cy];	//C
				break;
			case kD:
				ret.x = data_[Dx]; ret.y = data_[Dy];	//D
				break;
		}
		return ret;
	}
	
	std::ostream &operator<<(std::ostream &os, const VertexData &data){
		os << "A: " << data.GetVertex(VertexData::kA) << "\n";
		os << "B: " << data.GetVertex(VertexData::kB) << "\n";
		os << "C: " << data.GetVertex(VertexData::kC) << "\n";
		os << "D: " << data.GetVertex(VertexData::kD) << "\n";
		return os;
	}

}
///EOF
