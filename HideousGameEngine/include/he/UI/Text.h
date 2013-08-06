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
	class GlyphData;
	
	// A block of glyphs...
	class Text {
	public:
		/**
		 *	Construct a Text object.
		 *	@param shader	The TextShader object. Not owned.
		 *	@param font		The font. Not owned.
		 *	@param string	The string to be rendered.
		 */
		Text(TextShader *shader, Font *font, const std::string &string);
		~Text();
		
		/**
		 *	Replace the string
		 *
		 *	@param	string	The new string.
		 */
		void SetString(const std::string &string);
		
		/**
		 *	Get size of the glyph. This is equal to the size of associated TextView.
		 *
		 *	@return	Size.
		 */
		GLKVector2 GetSize() const;
		
		/**
		 *	The length of the string.
		 *
		 *	@return	The length.
		 */
		unsigned int GetLength() const;
		
		/**
		 *	Get Glyph position vector. Used by TextView when moving Glyph objects to itself.
		 *
		 *	@param	index	The index. Must be less than the associated string's lenght. Not checked.
		 *
		 *	@return	The position vector.
		 *
		 *	@note	In future other transform factors like scale and rotation could be added.
		 */
		GLKVector3 GetGlyphTransform(unsigned int index) const;
		
		/**
		 *	Get the absolute size of the associated Glyph.
		 *
		 *	@param	index	The index. Must be less than the associated string's lenght. Not checked.
		 *
		 *	@return	Size of the Glyph.
		 */
		GLKVector2 GetGlyphSize(unsigned int index) const;
		
		/**
		 *	A utility method to create a Glyph object.
		 *
		 *	@param	transform	The transform of the Glyph at this index.
		 *	@param	index	The index. Must be less than the associated string's lenght. Not checked.
		 *	@param	color	Color of the Glyph object.
		 *
		 *	@return	A Glyph object.
		 */
		Glyph *CreateGlyph(const he::Transform &transform, unsigned int index, const GLKVector4 color);
		
	private:
		void unload_string();
		
		GlyphData **gdata_;
		std::string string_;
		GLKVector2 size_;
		TextShader *shader_;
		Font *font_;
	};
	
	/** Render the string
	 @note Currently Text is just a placeholder name for View.
	 I'm not even sure if this name is going to live in future iterations as it serves no special thing.
	 */
	class TextView : public View{
	public:
		/**
		 *	Add glyphs from text to this->MoveSubview()
		 *
		 *	@param	transform	The transform object.
		 *	@param	text			The Text to be rendered.
		 *	@param	color		The color to be rendered.
		 */
		TextView(const Transform &transform, Text *text, GLKVector4 color = GLKVector4Make(0.0f, 0.0f, 0.0f, 1.0f));
		
		virtual void Update(float dt);
		virtual void Render();
		virtual GLKVector2 GetSize() const;
		
	private:
		GLKVector2 size_;
	};
	
	
	//	namespace text {
	//		Text *Create(TextShader *shader, Font *font, const std::string &string);
	//	}
	
	/** Create textviews */
	// TBD
	//	class TextViewFactory {
	//	public:
	//		TextViewFactory(TextShader *shader, Font *font_m);
	//
	//		/** Create a text-view
	//			@param transform		The transform object.
	//			@param string		The string to be rendered.
	//			@param color			The color of the font. Default is black.
	//		 */
	//		TextView *CreateTextView(const Transform &transform, const std::string &string, GLKVector4 color = GLKVector4Make(0.0f, 0.0f, 0.0f, 1.0f));
	//
	//	private:
	//		Asset<Font> font_m_; /**< font asset. Dies with the factory */
	//		Asset<TextShader> shader_; /**< shader asset */
	//	};
}

#endif
