//
//  Gesture.h
//  SCML
//
//  Created by Sid on 25/03/13.
//  Copyright (c) 2013 whackylabs. All rights reserved.
//

#ifndef __HideousGameEngine__Gesture__
#define __HideousGameEngine__Gesture__
#include <ostream>

#include <he/Utils/GLKMath_Additions.h>

namespace he{
	///////////////////////////////////////////////////////////////////////////////////////////////////
	// MARK: Gesture
	///////////////////////////////////////////////////////////////////////////////////////////////////
	//TODO: Gestures not tested for all kind of events.
	class Gesture{
	public:
		typedef enum{ kTap, /*kLongTap,*/ kZoomIn, kZoomOut, kDrag, kNone } Action;
		typedef enum{ kBegin, kChange, kEnd, kCancel, kFail, kPossible } State;

		Gesture();
		
		// The point of contact in OpenGL coord space.
		GLKVector2 GetHitPoint() const;
		
		Action action_;
		bool continious_;
		int fingers_;
		State state_;
		int taps_;
		GLKVector2 touch_point_;		// In UIKit coord space
		GLKVector2 velocity_;
		
	private:
		const float kDefaultMoveSpeed = 2.0; //units per second
	};
	std::ostream &operator<<(std::ostream &os, const Gesture &g);
	
	///////////////////////////////////////////////////////////////////////////////////////////////////
	// MARK: GestureListenable
	///////////////////////////////////////////////////////////////////////////////////////////////////
	/**
		The protocol for GestureListener.
	*/
	class GestureListenable{
	public:
		GestureListenable();
		virtual ~GestureListenable();
		virtual void PerformAction(const Gesture &g) = 0;

		// Points to next GestureListener. Not supposed to be used externally by any other class than EventLoop.
		GestureListenable *next_;
	};
	///////////////////////////////////////////////////////////////////////////////////////////////////
	// MARK: GestureListener.
	///////////////////////////////////////////////////////////////////////////////////////////////////
	template <typename T>
	class GestureListener : public GestureListenable{
	public:
		typedef void(T::*callback)(const Gesture &g);
		GestureListener(T *object, callback method) :
		object_(object),
		method_(method)
		{}
		
		void PerformAction(const Gesture &g){
			(object_->*method_)(g);
		}
	private:
		T *object_;
		callback method_;
	};
	
	///////////////////////////////////////////////////////////////////////////////////////////////////
	// MARK: EventLoop
	///////////////////////////////////////////////////////////////////////////////////////////////////
	/**
	 Broadcasts every gesture event to all listeners.
	 Owns nothing.
	*/
	class EventLoop{
	public:
		EventLoop();
		void AddListener(GestureListenable *listener);
		void RemoveListener(GestureListenable *listener);

		// To be called from GestureCollector, whenever an event happens.
		void SetGesture(const Gesture &gesture);
	private:
		GestureListenable *head_;
	};
	
	// Call the he/Utils/Utils.h => GlobalsCreate() at init stage of the game to create this
	extern EventLoop *g_EventLoop;
	
	///////////////////////////////////////////////////////////////////////////////////////////////////
	// MARK: Utility
	///////////////////////////////////////////////////////////////////////////////////////////////////
	
	/**
	 *	Create a new gesture listener and activate it for listening.
	 *
	 *	@param	object	The listener object. Most probably the this pointer.
	 *	@param	method	The callback to be registered.
	 *
	 *	@return	The listener object
	 */
	template <typename T> GestureListener<T> *CreateGestureListener(T *object, typename GestureListener<T>::callback method) {
		GestureListener<T> *gl = new he::GestureListener<T>(object, method);
		g_EventLoop->AddListener(gl);
		return gl;
	}

	template<typename T>
	struct GestureListenerDeleter {
		/**
		 *	Destroy and deactivate the listener object.
		 *
		 *	@param	gl	The gesture listener object.
		 */
		void operator()(GestureListener<T> *gl) {
			g_EventLoop->RemoveListener(gl);
			delete gl;
		}
	};
}
#endif /* defined(__HideousGameEngine__Gesture__) */
