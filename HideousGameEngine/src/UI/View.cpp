//
//  View.cpp
//  HideousGameEngine
//
//  Created by Sid on 13/06/13.
//  Copyright (c) 2013 whackylabs. All rights reserved.
//

#include <he/UI/View.h>

namespace he {
	namespace ui{
		View::View(const Frame &frame) :
		add_to_(nullptr),
		head_(nullptr),
		next_(nullptr),
		frame_(frame)
		{}
		
		View::~View(){
			if(head_){
				View *del = nullptr;
				for(View *p = head_; p; p = p->next_){
					if(del){
						delete del; del = nullptr;
					}
					del = p;
				}
				if(del){
					delete del; del = nullptr;
				}
			}
		}
		
		void View::Update(float dt){
			self_update(dt);
			for(View *p = head_; p; p = p->next_){
				p->Update(dt);
			}
		}
		void View::self_update(float dt){}
		
		void View::Render(){
			self_render();
			for(View *p = head_; p; p = p->next_){
				p->Render();
			}
		}
		void View::self_render(){}
		
		/** Owns the passed component */
		void View::AddSubview(View *view){
			if(!head_){
				head_ = add_to_ = view;
			}else{
				add_to_->next_ = view;
				add_to_ = view;
			}
		}
		
		void View::SetFrame(const he::Frame &frame){
			frame_ = frame;
		}
		
		const Frame &View::GetFrame() const{
			return frame_;
		}
		
		void View::SetNeedsDisplay(){
			self_set_needs_display();
			for(View *p = head_; p; p = p->next_){
				p->SetNeedsDisplay();
			}
		}
		void View::self_set_needs_display(){}
		
	} /*namespace ui*/
} /*namespace he*/

///EOF