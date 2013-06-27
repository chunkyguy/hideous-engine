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
	GradientView::GradientView(const Frame frame, const Factory *gv_factory) :
	View(frame)
	{
		render_object_ = new RenderObject(gv_factory->vertex.Get(), gv_factory->shader.Get(), nullptr, Transform_GetMVP(&(frame.GetTransform())));
	}
	
	GradientView::~GradientView(){
		delete render_object_;
	}
	
	void GradientView::update(float dt){
		render_object_->SetMVP(Transform_GetMVP(&(GetFrame().GetTransform())));
	}
	
	void GradientView::render(){
		render_object_->Render();
	}
	
	
	///////////////////////////////////////////////////////////////////////////////////////////////////
	// MARK: GradientView::Factory
	///////////////////////////////////////////////////////////////////////////////////////////////////
	GradientView::Factory::Factory(ColorShader *sh, ColorVertex *v){
		shader.Set(sh, true);
		vertex.Set(v, true);
	}
	
}
///EOF
