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
	head_(nullptr),
	tail_(nullptr),
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
	View *View::MoveSubview(View *view){
		if(!head_){
			head_ = tail_ = view;
		}else{
			tail_->next_ = view;
			tail_ = view;
		}
		view->transform_.parent = &transform_;
		return view;
	}
	
	void View::RemoveSubview(View *view){
		if(view == head_){
			head_ = head_->next_;
			if (view == tail_) {		// if only one node exists. Adjust the tail_ too.
				tail_ = head_;
			}
		}else{
			View *p = nullptr;
			for(p = head_; p->next_ != view; p = p->next_){
			}
			p->next_ = view->next_;
			if (view == tail_) {	// if deleting the last node. Move tail_ one step back.
				tail_ = p;
			}
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