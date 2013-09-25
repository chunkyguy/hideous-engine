//
//  View.cpp
//  HideousGameEngine
//
//  Created by Sid on 13/06/13.
//  Copyright (c) 2013 whackylabs. All rights reserved.
//

#include <he/UI/View.h>
#include <he/Utils/Utils.h>

namespace he {
 View::View(const Transform &transform, const GLKVector2 &size) :
 head_(nullptr),
 tail_(nullptr),
 next_(nullptr),
 transform_(transform),
 default_size_(size)
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
  return default_size_;
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
 
 
 
 bool HitTest(const he::View *one, const he::View *two) {
  struct Line {
   int a, b;
  } lines[4] = {
   {0,1},		//AB
   {0,2},		//AC
   {1,3},		//BD
   {2,3}		//CD
  };
  
  GLKVector2 size = one->GetSize();
  GLKVector2 v_one_i[4] = {
   {-size.x/2.0f, -size.y/2.0f},
   {size.x/2.0f, -size.y/2.0f},
   {-size.x/2.0f, size.y/2.0f},
   {size.x/2.0f, size.y/2.0f}
  };
  Transform_GetWorldCoordinates(one->GetTransform(), 4, v_one_i);
  
  size = two->GetSize();
  GLKVector2 v_two_i[4] = {
   {-size.x/2.0f, -size.y/2.0f},
   {size.x/2.0f, -size.y/2.0f},
   {-size.x/2.0f, size.y/2.0f},
   {size.x/2.0f, size.y/2.0f}
  };
  Transform_GetWorldCoordinates(two->GetTransform(), 4, v_two_i);
  
  
  int l_one, l_two;
  bool hit = false;
  for (l_one = 0; l_one < 4; ++l_one) {
   for (l_two = 0; l_two < 4; ++l_two) {
    if (LinesIntersect(v_one_i[lines[l_one].a], v_one_i[lines[l_one].b], v_two_i[lines[l_two].a], v_two_i[lines[l_two].b])) {
     hit = true;
     //he_Trace("Line1[%d]: {%@, %@}\nLine2[%d]: {%@, %@}\n",l_one,v_one_i[lines[l_one].a], v_one_i[lines[l_one].b],l_two, v_two_i[lines[l_two].a], v_two_i[lines[l_two].b]);
    }
    if (hit) {break;}
   }
   if (hit) {break;}
  }
  
  //		he_Trace("Trans[0]:%@\nSize[0]:%@\n",one->GetTransform(), one->GetSize());
  //		he_Trace("Trans[1]:%@\nSize[1]:%@\n",two->GetTransform(), two->GetSize());
  //			he_Trace("View[1]:\n%@\n",two_mv);
  //			for (int i = 0; i < 4; ++i) {
  //				he_Trace("one: %d:\t%@\n",i,v_one_i[i]);
  //			}
  //			for (int i = 0; i < 4; ++i) {
  //				he_Trace("two: %d:\t%@\n",i,v_two_i[i]);
  //			}
  
  return hit;
 }
 
} /*namespace he*/

///EOF