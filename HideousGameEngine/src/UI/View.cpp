//
//  View.cpp
//  HideousGameEngine
//
//  Created by Sid on 13/06/13.
//  Copyright (c) 2013 whackylabs. All rights reserved.
//

#include <he/UI/View.h>

namespace he {
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
		for(View *p = head_; p; p = p->next_){
			p->Update(dt);
		}
	}
	
	void View::Render(){
		for(View *p = head_; p; p = p->next_){
			p->Render();
		}
	}
	
	GLKVector2 View::GetSize() const {
		return GLKVector2Make(0.0f, 0.0f);
	}
	
	/** Owns the passed component */
	void View::MoveSubview(View *view){
		if(!head_){
			head_ = add_to_ = view;
		}else{
			add_to_->next_ = view;
			add_to_ = view;
		}
		view->transform_.parent = &transform_;
	}
	
	void View::RemoveSubview(View *view){
		View *p = nullptr;
		if(view == head_){
			head_ = head_->next_;
		}else{
			for(p = head_; p->next_ != view; p = p->next_){
			}
			p->next_ = view->next_;
		}
		delete view;
		view = nullptr;
	}

	void View::SetTransform(const he::Transform &transform) {
		transform_ = transform;
	}
	
	const Transform &View::GetTransform() const{
		return transform_;
	}
	
	Frame CreateFrame(const View *view) {
		return Frame(view->GetTransform(), view->GetSize());
	}

//	Frame *View::GetFramePtr(){
//		return &frame_;
//	}
	
	//		const GLKMatrix4 View::GetMVP() const{
	//			return frame_.GetTransform().GetMVP();
	//		}
	//
	//		bool View::Contains(const GLKVector2 &point){
	//			return he::Vertex::Contains(frame_.GetRect(), point);
	//		}
	
} /*namespace he*/

///EOF