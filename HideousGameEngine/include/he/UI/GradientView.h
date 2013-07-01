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

	/** A multi-colored rectangle.
		@note Use GradientViewFactory to create GradientView's easily.
	 */
	class GradientView : public View{
	public:
		/** Construct a GradientView.
			@param frame		The frame.
			@param vertex_m	The vertex data. Owns it.
			@param shader	The color shader.
		 */
		GradientView(const Frame frame, const ColorVertex *vertex_m, const ColorShader *shader);
		virtual ~GradientView();
		
	protected:
		virtual void update(float dt);
		virtual void render();
		
	private:
		RenderObject *render_object_;
		const ColorVertex *vertex_;
	};


	/** Creates GradientView's 
		@note Could be configured to have single, double or quad colors.
	 */
	class GradientViewFactory{
	public:
		/** Contruct a GradientViewFactory 
		 @param	shadr	The color-shader.
		 */
		GradientViewFactory(ColorShader *shadr);
		
		/** Create GradientView with a single color 
		 @param frame The frame.
		 @param colorA The fill color.
		 */
		GradientView *CreateGradientView(Frame frame, GLKVector4 colorA);

		/** Create GradientView with a two colors
		 @param frame The frame.
		 @param colorA The fill color at end A (bottom-left).
		 @param colorD The fill color at end D (top-right).
		 @note The colors at end B and C are interpolated.
		 */
		GradientView *CreateGradientView(Frame frame, GLKVector4 colorA, GLKVector4 colorD);

		/** Create GradientView with a four colors
		 @param frame The frame.
		 @param colorA The fill color at end A.
		 @param colorB The fill color at end B.
		 @param colorC The fill color at end C.
		 @param colorD The fill color at end D.
		 */
		GradientView *CreateGradientView(Frame frame, GLKVector4 colorA, GLKVector4 colorB, GLKVector4 colorC, GLKVector4 colorD);
		
	private:
		Asset<ColorShader> shader;
	};
}


#endif
