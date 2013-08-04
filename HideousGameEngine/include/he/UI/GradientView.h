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
#include <he/Vertex/ColorVertex.h>

namespace he {
	
	class ColorShader;
	class RenderObject;

	/** A multi-colored rectangle.
		@note Use GradientViewFactory to create GradientView's easily.
	 */
	class Gradient {
	public:
		/**
		 *	Construct a GradientView.
		 *	@param vertex_m	The vertex data. Owns it.
		 *	@param shader	The color shader.
		 *	@param size		The size.
		 */
		Gradient(const ColorVertex *vertex_m, const ColorShader *shader, const GLKVector2 size);
		~Gradient();
		
		void Render(const Transform &transform);
		GLKVector2 GetSize() const;
		
	private:
		RenderObject *render_object_;
		const ColorVertex *vertex_;
		GLKVector2 size_;
	};

	/** Creates GradientView's
	 @warning Attach ColorShader and Frame before creating a GradientView.
	 Each time the color is updated, the old reference is lost.
	 Use multiple factories for multiple configurations.
	 @brief Could be configured to have single, double or quad colors.
	 */
	namespace gradient {
		Gradient *Create(const GLKVector2 &size, ColorShader *shader, GLKVector4 colorA);
		Gradient *Create(const GLKVector2 &size, ColorShader *shader, GLKVector4 colorA, GLKVector4 colorD);
		Gradient *Create(const GLKVector2 &size, ColorShader *shader, GLKVector4 colorA, GLKVector4 colorB, GLKVector4 colorC, GLKVector4 colorD);
	}


	class GradientView : public View {
	public:
		GradientView(const Transform &transform, Gradient *gradient);
		virtual void Update(float dt);
		virtual void Render();
		virtual GLKVector2 GetSize() const;
		
	private:
		Gradient *gradient_;
	};
}


#endif
