//
//  Label.cpp
//  HideousGameEngine
//
//  Created by Sid on 23/06/13.
//  Copyright (c) 2013 whackylabs. All rights reserved.
//

#include <he/UI/Label.h>

#include <he/Font/Font.h>
namespace he {
		///////////////////////////////////////////////////////////////////////////////////////////////////
		// MARK: Label
		///////////////////////////////////////////////////////////////////////////////////////////////////
		Label::Label(const Frame frame, const LabelFactory *factory, const std::string &string, const GLKVector4 color) :
		View(frame),
		text_(new Text(string, frame.GetTransform(), color))
		{
			factory->font.Get()->LoadText(text_);
		}
		
		Label::~Label(){
			delete text_;
		}
		
		void Label::update(float dt){			
		}
		
		void Label::render(){
			text_->Render();
		}
		
		///////////////////////////////////////////////////////////////////////////////////////////////////
		// MARK: LabelFactory
		///////////////////////////////////////////////////////////////////////////////////////////////////
		LabelFactory::LabelFactory(Font *f){
			font.Load(f, false);
		}
		
}

///EOF

