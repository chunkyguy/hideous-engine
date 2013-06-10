//
//  ParticleVertex.cpp
//  HEAssets
//
//  Created by Sid on 29/04/13.
//  Copyright (c) 2013 whackylabs. All rights reserved.
//

#include <he/Vertex/ParticleVertex.h>
#include <he/Utils/DebugHelper.h>

namespace he{
	////////////////////////////////////////////////////////////////////////////////////////////////////////
	// MARK: ParticleVertex
	////////////////////////////////////////////////////////////////////////////////////////////////////////
	ParticleVertex::ParticleVertex(int count, float point_size) :
	IVertex(count),
	size_(sizeof(GLfloat) * 2 * count),
	data_ (new GLfloat[count * 2]),
	point_size_(point_size)
	{
		bzero(data_, size_);
	}

	ParticleVertex::~ParticleVertex(){
		delete [] data_;
	}
	
	void ParticleVertex::SetData(int index, const GLKVector2 &data){
		int eff_indx = index * 2;
		assert(eff_indx+1 < GetCount()*2);
		data_[eff_indx] = data.x;
		data_[eff_indx+1] = data.y;
	}
	
	const GLfloat *ParticleVertex::GetRawData(const DataType dt) const{
		switch(dt){
			case IVertex::kPosition:
				return data_; break;
				
			case IVertex::kColor:
				return nullptr;
			case IVertex::kTexture:
				return nullptr;
		}
		return nullptr;
	}
	
	GLfloat ParticleVertex::GetPointSize() const{
		return point_size_;
	}

	GLsizei ParticleVertex::GetSize() const{
		return size_;
	}
	
}