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
		struct Factory{
			Factory(ColorShader *sh, ColorVertex *v);
			
			Asset<ColorShader> shader;
			Asset<ColorVertex> vertex;
		};
		
		GradientView(const Frame frame, const Factory *gv_factory);
		virtual ~GradientView();
		
	protected:
		virtual void update(float dt);
		virtual void render();
		
	private:
		RenderObject *render_object_;
	};
	
}


#endif
