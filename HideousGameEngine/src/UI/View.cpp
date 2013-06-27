//
//  View.cpp
//  HideousGameEngine
//
//  Created by Sid on 13/06/13.
//  Copyright (c) 2013 whackylabs. All rights reserved.
//

#include <he/UI/View.h>

namespace he {
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
			update(dt);
			for(View *p = head_; p; p = p->next_){
				p->Update(dt);
			}
		}
		void View::update(float dt){		}
				
		void View::Render(){
			render();
			for(View *p = head_; p; p = p->next_){
				p->Render();
			}
		}
		void View::render(){		}
		
		/** Owns the passed component */
		void View::MoveSubview(View *view){
			if(!head_){
				head_ = add_to_ = view;
			}else{
				add_to_->next_ = view;
				add_to_ = view;
			}
			view->frame_.GetTransformPtr()->parent = frame_.GetTransformPtr();
		}
		
		void View::SetFrame(const he::Frame &frame){
			frame_ = frame;
		}
		
		const Frame &View::GetFrame() const{
			return frame_;
		}

		Frame *View::GetFramePtr(){
			return &frame_;
		}

//		const GLKMatrix4 View::GetMVP() const{
//			return frame_.GetTransform().GetMVP();
//		}
//		
//		bool View::Contains(const GLKVector2 &point){
//			return he::Vertex::Contains(frame_.GetRect(), point);
//		}
				
} /*namespace he*/

///EOF