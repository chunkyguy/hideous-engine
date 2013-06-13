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
		View::View(const Transform &transform) :
		add_to_(nullptr),
		head_(nullptr),
		next_(nullptr),
		transform_(transform)
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
			update(dt);
			for(View *p = head_; p; p = p->next_){
				p->Update(dt);
			}
		}
		void View::update(float dt){}
		
		void View::Render(){
			render();
			for(View *p = head_; p; p = p->next_){
				p->Render();
			}
		}
		void View::render(){}
		
		/** Owns the passed component */
		void View::AddSubview(View *view){
			if(!head_){
				head_ = add_to_ = view;
			}else{
				add_to_->next_ = view;
				add_to_ = view;
			}
		}
		
		void View::SetTransform(const he::Transform &transform){
			transform_ = transform;
		}
		
		const Transform &View::GetTransform() const{
			return transform_;
		}
		
		void View::SetNeedsDisplay(){
			refresh();
			for(View *p = head_; p; p = p->next_){
				p->refresh();
			}
		}
		void View::refresh(){}
		
	} /*namespace ui*/
} /*namespace he*/

///EOF