//
//  Text.h
//  HideousGameEngine
//
//  Created by Sid on 23/06/13.
//  Copyright (c) 2013 whackylabs. All rights reserved.
//

#ifndef HideousGameEngine_Text_h
#define HideousGameEngine_Text_h
#include <string>

#include <he/UI/View.h>

#include <he/Utils/GLKMath_Additions.h>
#include <he/Utils/Frame.h>
#include <he/Utils/Asset.h>

namespace he {
	class Glyph;
	class Font;
	class TextShader;
//
//	
//	class Text : public View{
//	public:
//		Text(Frame frame, Glyph **data_m, unsigned int data_len, GLKVector4 color);
//		virtual ~Text();
//		/** The actual size of the text being rendered
//		 @brief This could be different from the passed frome, as it is calculated at run time based on the font size and the string size
//		 */
//		GLKVector2 GetActualSize() const;
//	protected:
//		virtual void update(float dt);
//		virtual void render();
//
//	private:
//		void load();
//		
//		Glyph ** data_;
//		unsigned int data_len_;
//		GLKVector2 eff_size_;
//	};
//
	class Text : public View{
	public:
		Text(Frame frame) : View(frame){}
		virtual ~Text(){}
	};
	
	class TextFactory {
	public:
		TextFactory(TextShader *shdr, Font *fnt_m);
		Text *CreateText(Transform transform, std::string string, GLKVector4 color = GLKVector4Make(0.0f, 0.0f, 0.0f, 1.0f));
		
	private:
		Asset<Font> font;
		Asset<TextShader> shader;
	};

}

#endif