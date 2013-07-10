//
//  GradientView.cpp
//  HideousGameEngine
//
//  Created by Sid on 26/06/13.
//  Copyright (c) 2013 whackylabs. All rights reserved.
//

#include <he/UI/GradientView.h>

#include <he/RenderObject/RenderObject.h>
#include <he/Vertex/ColorVertex.h>
#include <he/Shaders/ColorShader.h>

namespace he{
	
	///////////////////////////////////////////////////////////////////////////////////////////////////
	// MARK: GradientView
	///////////////////////////////////////////////////////////////////////////////////////////////////
	GradientView::GradientView(const Frame frame, const ColorVertex *vertex_m, const ColorShader *shader) :
	View(frame),
	vertex_(vertex_m),
	render_object_(new RenderObject(vertex_m, shader, nullptr, Transform_GetMVP(&(frame.GetTransform()))))
	{	}
	
	GradientView::~GradientView(){
		delete render_object_;
		delete vertex_;
	}
	
	void GradientView::update(float dt){
	}
	
	void GradientView::render(){
		render_object_->SetMVP(Transform_GetMVP(&(GetFrame().GetTransform())));
		render_object_->Render();
	}
	
	
	///////////////////////////////////////////////////////////////////////////////////////////////////
	// MARK: GradientView::Factory
	///////////////////////////////////////////////////////////////////////////////////////////////////
	GradientViewFactory::GradientViewFactory(ColorShader *shadr){
		shader.Set(shadr, true);
	}
	GradientView *GradientViewFactory::CreateGradientView(Frame frame, GLKVector4 colorA){
		return CreateGradientView(frame, colorA, colorA);
	}
	GradientView *GradientViewFactory::CreateGradientView(Frame frame, GLKVector4 colorA, GLKVector4 colorD){
		return new GradientView(frame,
								new he::ColorVertex({Vertex::GetVertex(frame.GetRect(), Vertex::kA), colorA},
													{Vertex::GetVertex(frame.GetRect(), Vertex::kD), colorD}),
								shader.Get()	);
	}
	GradientView *GradientViewFactory::CreateGradientView(Frame frame, GLKVector4 colorA, GLKVector4 colorB, GLKVector4 colorC, GLKVector4 colorD){
		return new GradientView(frame,
								new he::ColorVertex({Vertex::GetVertex(frame.GetRect(), Vertex::kA), colorA},
													{Vertex::GetVertex(frame.GetRect(), Vertex::kB), colorB},
													{Vertex::GetVertex(frame.GetRect(), Vertex::kC), colorC},
													{Vertex::GetVertex(frame.GetRect(), Vertex::kD), colorD}),
								shader.Get()	);
	}

}
///EOF
