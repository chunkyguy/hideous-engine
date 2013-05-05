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
}
///EOF
