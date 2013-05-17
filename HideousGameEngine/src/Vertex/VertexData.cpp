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
		for(int i = 0; i < 8; ++i){
			data_[i] = 0;
		}
	}
	VertexData::VertexData(GLfloat *data){
		for(int i = 0; i < 8; ++i){
			data_[i] = data[i];
		}
	}
	VertexData::VertexData(const VertexData &other){
		for(int i = 0; i < 8; ++i){
			data_[i] = other.data_[i];
		}
	}
	VertexData::VertexData(GLKVector2 a, GLKVector2 b, GLKVector2 c, GLKVector2 d){
		data_[Ax] = a.x; data_[Ay] = a.y;	//A
		data_[Bx] = b.x; data_[By] = b.y;	//B
		data_[Cx] = c.x; data_[Cy] = c.y;	//C
		data_[Dx] = d.x; data_[Dy] = d.y;	//D
	}
	void VertexData::operator=(const VertexData &other){
		for(int i = 0; i < 8; ++i){
			data_[i] = other.data_[i];
		}
	}
	
	VertexData::VertexData(GLfloat a_x, GLfloat a_y, GLfloat d_x, GLfloat d_y){
		data_[Ax] = a_x; data_[Ay] = a_y;	//A
		data_[Bx] = d_x; data_[By] = a_y;	//B
		data_[Cx] = a_x; data_[Cy] = d_y;	//C
		data_[Dx] = d_x; data_[Dy] = d_y;	//D
	}
	
	GLfloat *VertexData::GetData(){
		return &data_[0];
	}
	
	GLsizei VertexData::GetSize(){
		return sizeof(data_);
	}
	
	bool VertexData::Contains(GLfloat x, GLfloat y){
		//printf("%f %f %f %f %f %f\n",x,y,data[eAx],data[eAy],data[eDx],data[eDy]);
		return ((x > data_[Ax] && x < data_[Dx]) && (y > data_[Ay] && y < data_[Dy]));
	}
	
	void VertexData::Scale(GLfloat x, GLfloat y){
		int j = 0;
		for(int i = 0; i < 4; ++i){
			data_[j++] *= x;
			data_[j++] *= y;
		}
	}
	void VertexData::SetVertex(VertexIndex index, GLKVector2 value){
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
	GLKVector2 VertexData::GetVertex(VertexIndex index){
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
}
///EOF
