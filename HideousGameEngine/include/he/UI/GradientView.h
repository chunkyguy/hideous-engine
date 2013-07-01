//
//  GradientView.h
//  HideousGameEngine
//
//  Created by Sid on 26/06/13.
//  Copyright (c) 2013 whackylabs. All rights reserved.
//

#ifndef HideousGameEngine_GradientView_h
#define HideousGameEngine_GradientView_h
#include <he/UI/View.h>

#include <he/Utils/Frame.h>
#include <he/Utils/Asset.h>

namespace he {
	
	class ColorShader;
	class RenderObject;
	class ColorVertex;
	
	class GradientView : public View{
	public:
		GradientView(const Frame frame, const ColorVertex *vertex_m, const ColorShader *shader);
		virtual ~GradientView();
		
	protected:
		virtual void update(float dt);
		virtual void render();
		
	private:
		RenderObject *render_object_;
		const ColorVertex *vertex_;
	};

	
	class GradientViewFactory{
	public:
		GradientViewFactory(ColorShader *shadr);
		GradientView *CreateGradientView(Frame frame, GLKVector4 colorA);
		GradientView *CreateGradientView(Frame frame, GLKVector4 colorA, GLKVector4 colorD);
		GradientView *CreateGradientView(Frame frame, GLKVector4 colorA, GLKVector4 colorB, GLKVector4 colorC, GLKVector4 colorD);
	private:
		Asset<ColorShader> shader;
	};
}


#endif
