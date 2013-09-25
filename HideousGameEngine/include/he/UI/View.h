//
//  View.h
//  HideousGameEngine
//
//  Created by Sid on 13/06/13.
//  Copyright (c) 2013 whackylabs. All rights reserved.
//

#ifndef HideousGameEngine_View_h
#define HideousGameEngine_View_h
#include <he/Utils/Frame.h>

namespace he {
 /** Container of all kind of Views.
  Adds child component in stack order.
  If AddSubview-order is like [btn_01, btn_01, bg, icon_01]
  Draw order will be [btn_01, btn_01, bg, icon_01]
  */
 class View{
 public:
  View(const Transform &transform, const GLKVector2 &size = GLKVector2Make(0.0f, 0.0f));
  virtual ~View();
  
  /** Update self. Update all children in draw order */
  virtual void Update(float dt);
  
  /** Render self. Render all children in draw order */
  virtual void Render();
  
  virtual GLKVector2 GetSize() const;
  
  /**
   *	Owns the passed component
   *
   *	@param	view	 The view to be moved. Is owned.
   *
   *	@return	Reference to the view.
   *
   *	@note	Use like: View *my_view = some_view->MoveSubview(new View(...));
   *			The point is to keep new inside the MoveSubview all the time. It's just a matter of convention.
   */
  View *MoveSubview(View *view);
  
  /** Remove the passed component */
  void RemoveSubview(View *view);
  
  /** Update frame */
  void SetTransform(const Transform &transform);
  /** Get the current frame */
  const Transform &GetTransform() const;
  
  //			/** Returns pointer to transform
  //			@warning This is more like a design bug, can get modified in future. Use minimum.
  //			 */
  //			Transform *GetTransformPtr();
  
 protected:
  Transform transform_; /**< The frame of the view */
  
 private:
  View *head_;		/**< The head pointer to the first child UIComponent. Starts drawing from here */
  View *tail_;	/**< Next Submit adds to this node. */
  View *next_;	/**< Points to the next sibling UIComponent */
  GLKVector2 default_size_; /**< Default size */
 };
 
 Frame CreateFrame(const View *view);
 
 /**
  *	Collision detection test between two View objects.
  *
  *	@param	one	View one.
  *	@param	two	View two.
  *
  *	@return	true if the collision happens else false.
  */
 bool HitTest(const he::View *one, const he::View *two);
} /*namespace he*/

#endif
