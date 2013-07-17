//
//  GradientView.cpp
//  HideousGameEngine
//
//  Created by Sid on 26/06/13.
//  Copyright (c) 2013 whackylabs. All rights reserved.
//

#include <he/UI/GradientView.h>

#include <he/RenderObject/RenderObject.h>
#include <he/Shaders/ColorShader.h>

namespace he{
	
	///////////////////////////////////////////////////////////////////////////////////////////////////
	// MARK: Gradient
	///////////////////////////////////////////////////////////////////////////////////////////////////
	Gradient::Gradient(const ColorVertex *vertex_m, const ColorShader *shader, const GLKVector2 size) :
	vertex_(vertex_m),
	render_object_(new RenderObject(vertex_m, shader, nullptr)),
	size_(size)
	{	}
	
	Gradient::~Gradient(){
		delete render_object_;
		delete vertex_;
	}
	
	void Gradient::Render(const Transform &transform){
		render_object_->SetMVP(Transform_GetMVP(&transform));
		render_object_->Render();
	}

	GLKVector2 Gradient::GetSize() const {
		return size_;
	}
	
	///////////////////////////////////////////////////////////////////////////////////////////////////
	// MARK: GradientView
	///////////////////////////////////////////////////////////////////////////////////////////////////
	GradientView::GradientView(const Transform &transform, Gradient *gradient) :
	View(transform),
	gradient_(gradient)
	{}
	
	void GradientView::Update(float dt) {
		View::Update(dt);
	}
	
	void GradientView::Render() {
		gradient_->Render(GetTransform());
		View::Render();
	}

	GLKVector2 GradientView::GetSize() const {
		return gradient_->GetSize();
	}

	///////////////////////////////////////////////////////////////////////////////////////////////////
	// MARK: Utility
	///////////////////////////////////////////////////////////////////////////////////////////////////
	namespace gradient {
		Gradient* Create(const GLKVector2 &size, ColorShader *shader, GLKVector4 colorA) {
			return Create(size, shader, colorA, colorA);
		}
		Gradient *Create(const GLKVector2 &size, ColorShader *shader, GLKVector4 colorA, GLKVector4 colorD) {
			Frame frame(Transform_Create(GLKVector3Make(0.0f, 0.0f, 0.0f)), size);
			return new Gradient(new ColorVertex({Vertex::GetVertex(frame.GetRect(), Vertex::kA), colorA},
												{Vertex::GetVertex(frame.GetRect(), Vertex::kD), colorD}), shader, size);
		}
		Gradient *Create(const GLKVector2 &size, ColorShader *shader, GLKVector4 colorA, GLKVector4 colorB, GLKVector4 colorC, GLKVector4 colorD) {
			Frame frame(Transform_Create(GLKVector3Make(0.0f, 0.0f, 0.0f)), size);
			return new Gradient(new ColorVertex({Vertex::GetVertex(frame.GetRect(), Vertex::kA), colorA},
												{Vertex::GetVertex(frame.GetRect(), Vertex::kB), colorB},
												{Vertex::GetVertex(frame.GetRect(), Vertex::kC), colorC},
												{Vertex::GetVertex(frame.GetRect(), Vertex::kD), colorD}), shader, size);
		}
	}
}
///EOF
