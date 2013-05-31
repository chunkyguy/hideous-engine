//
//  VertexPar.cpp
//  HEAssets
//
//  Created by Sid on 29/04/13.
//  Copyright (c) 2013 whackylabs. All rights reserved.
//
#include <cassert>

#include <he/Vertex/VertexPar.h>

namespace he{
	////////////////////////////////////////////////////////////////////////////////////////////////////////
	// MARK: VertexPar
	////////////////////////////////////////////////////////////////////////////////////////////////////////
	VertexPar::VertexPar(int count, double point_size) :
	IVertex(count),
	size_(sizeof(GLfloat) * 2 * count),
	data_ (new GLfloat[count * 2]),
	point_size_(point_size)
	{
		bzero(data_, size_);
	}

	VertexPar::~VertexPar(){
		delete [] data_;
	}
	
	void VertexPar::SetData(int index, const GLKVector2 &data){
		int eff_indx = index * 2;
		assert(eff_indx+1 < GetCount()*2);
		data_[eff_indx] = data.x;
		data_[eff_indx+1] = data.y;
	}
	
	const GLfloat *VertexPar::GetPositionData() const{
		return data_;
	}
	
	GLfloat VertexPar::GetPointSize() const{
		return point_size_;
	}

	GLsizei VertexPar::GetSize() const{
		return size_;
	}
	
}