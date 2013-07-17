//
//  Button.h
//  HideousGameEngine
//
//  Created by Sid on 13/06/13.
//  Copyright (c) 2013 whackylabs. All rights reserved.
//

#ifndef HideousGameEngine_Button_h
#define HideousGameEngine_Button_h
#include <he/UI/View.h>

#include <he/EventLoop/Gesture.h>
#include <he/Utils/Frame.h>

namespace he {
	
	/** Interface of the protocol */
	class ButtonView;

	struct IButtonListener{
		virtual ~IButtonListener(){}
		virtual void Hit(ButtonView *sender) = 0;
	};
	
	/**	Anon delegate */
	template<typename T>
	class ButtonListener : public IButtonListener{
	public:
		typedef void(T::*callback)(ButtonView *sender);
		ButtonListener(T *object, callback callback) :
		object_(object),
		method_(callback)
		{}
		
		void Hit(ButtonView *sender){
			(object_->*method_)(sender);
		}
	private:
		T *object_;
		callback method_;
	};
	
	
	class ButtonView : public View {
	public:
		ButtonView(const Frame &frame, IButtonListener *listner, int tag = -1);
		virtual ~ButtonView();
		virtual void Update(float dt);
		virtual void Render();

		void HandleGesture(const Gesture &g);
		int GetTag() const;

	private:
		int tag_;	/**< tag to identify the object */
		GestureListener<ButtonView> *gesture_listener_; /**< Registered gesture listener */
		IButtonListener *listner_;	/**< Registered button listener */
	};
	
} /*namespace he*/

#endif
