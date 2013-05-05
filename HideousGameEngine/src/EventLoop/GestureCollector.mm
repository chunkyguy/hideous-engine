//
//  GestureCollector.m
//  HideousGameEngine
//
//  Created by Sid on 25/03/13.
//  Copyright (c) 2013 whackylabs. All rights reserved.
//

#import <he/EventLoop/GestureCollector.h>
#include <he/EventLoop/Gesture.h>

@implementation GestureCollector
-(id)initWithView:(UIView *)vw{
	self = [super init];
	if(self){
		view = vw;
		
		// Resgistering Gestures
		UILongPressGestureRecognizer *singleTapDownGesture = [[UILongPressGestureRecognizer alloc] initWithTarget:self action:@selector(singleTapDownGestureAction:)];
		[view addGestureRecognizer:singleTapDownGesture];
		[singleTapDownGesture release];
		
		UITapGestureRecognizer *singleTapGesture = [[UITapGestureRecognizer alloc] initWithTarget:self action:@selector(singleTapGestureAction:)];
		[view addGestureRecognizer:singleTapGesture];
		[singleTapGesture release];
		
		lastPinchScale = 1.0;
		UIPinchGestureRecognizer *pinchGesture = [[UIPinchGestureRecognizer alloc] initWithTarget:self action:@selector(pinchGestureAction:)];
		[view addGestureRecognizer:pinchGesture];
		[pinchGesture release];
		
		UIPanGestureRecognizer *dragGesture = [[UIPanGestureRecognizer alloc] initWithTarget:self action:@selector(dragGestureAction:)];
		[view addGestureRecognizer:dragGesture];
		[dragGesture release];
	}
	return self;
}


-(void)singleTapDownGestureAction:(UILongPressGestureRecognizer *)gesture{
	switch(gesture.state){
		case UIGestureRecognizerStateBegan:
			he::g_Gesture.state_ = he::Gesture::kBegin;
			break;
		case UIGestureRecognizerStateChanged:
			he::g_Gesture.state_ = he::Gesture::kChange;
			break;
		case UIGestureRecognizerStateEnded:
			he::g_Gesture.state_ = he::Gesture::kEnd;
			break;
		case UIGestureRecognizerStateCancelled:
			he::g_Gesture.state_ = he::Gesture::kCancel;
			break;
		case UIGestureRecognizerStateFailed:
			he::g_Gesture.state_ = he::Gesture::kFail;
			break;
		case UIGestureRecognizerStatePossible:
			he::g_Gesture.state_ = he::Gesture::kPossible;
			break;
	}
	
	if(gesture.state == UIGestureRecognizerStateBegan){
		he::g_Gesture.continious_ = true;
		he::g_Gesture.fingers_ = [gesture numberOfTouches];
		he::g_Gesture.taps_ = 1;
		he::g_Gesture.action_ = he::Gesture::kTap;
		CGPoint tPt = [gesture locationInView:view];
		he::g_Gesture.touch_point_ = GLKVector2Make(tPt.x, tPt.y);
	}else if(gesture.state == UIGestureRecognizerStateEnded){
		he::g_Gesture.Reset();
	}
}

-(void)singleTapGestureAction:(UITapGestureRecognizer *)gesture{
	switch(gesture.state){
		case UIGestureRecognizerStateBegan:
			he::g_Gesture.state_ = he::Gesture::kBegin;
			break;
		case UIGestureRecognizerStateChanged:
			he::g_Gesture.state_ = he::Gesture::kChange;
			break;
		case UIGestureRecognizerStateEnded:
			he::g_Gesture.state_ = he::Gesture::kEnd;
			break;
		case UIGestureRecognizerStateCancelled:
			he::g_Gesture.state_ = he::Gesture::kCancel;
			break;
		case UIGestureRecognizerStateFailed:
			he::g_Gesture.state_ = he::Gesture::kFail;
			break;
		case UIGestureRecognizerStatePossible:
			he::g_Gesture.state_ = he::Gesture::kPossible;
			break;
	}
	
	if(gesture.state == UIGestureRecognizerStateEnded){
		he::g_Gesture.continious_ = false;
		he::g_Gesture.fingers_ = [gesture numberOfTouches];
		he::g_Gesture.taps_ = 1;
		he::g_Gesture.action_ = he::Gesture::kTap;
		CGPoint tPt = [gesture locationInView:view];
		he::g_Gesture.touch_point_ = GLKVector2Make(tPt.x, tPt.y);
	}
}

-(void) pinchGestureAction:(UIPinchGestureRecognizer *)gesture{
	switch(gesture.state){
		case UIGestureRecognizerStateBegan:
			he::g_Gesture.state_ = he::Gesture::kBegin;
			break;
		case UIGestureRecognizerStateChanged:
			he::g_Gesture.state_ = he::Gesture::kChange;
			break;
		case UIGestureRecognizerStateEnded:
			he::g_Gesture.state_ = he::Gesture::kEnd;
			break;
		case UIGestureRecognizerStateCancelled:
			he::g_Gesture.state_ = he::Gesture::kCancel;
			break;
		case UIGestureRecognizerStateFailed:
			he::g_Gesture.state_ = he::Gesture::kFail;
			break;
		case UIGestureRecognizerStatePossible:
			he::g_Gesture.state_ = he::Gesture::kPossible;
			break;
	}

	if(gesture.state == UIGestureRecognizerStateBegan){
		if(gesture.scale < lastPinchScale){	//zoom out
			he::g_Gesture.action_ = he::Gesture::kZoomOut;
		}else{	// zoom in
			he::g_Gesture.action_ = he::Gesture::kZoomIn;
		}
		he::g_Gesture.continious_ = true;
		he::g_Gesture.fingers_ = 2;
		he::g_Gesture.velocity_
		= GLKVector2MultiplyScalar(he::g_Gesture.velocity_, fabs(gesture.velocity));
		lastPinchScale = gesture.scale;
	}else if(gesture.state == UIGestureRecognizerStateEnded){
		he::g_Gesture.Reset();
	}
}

-(void)dragGestureAction:(UIPanGestureRecognizer *)gesture{
	switch(gesture.state){
		case UIGestureRecognizerStateBegan:
			he::g_Gesture.state_ = he::Gesture::kBegin;
			break;
		case UIGestureRecognizerStateChanged:
			he::g_Gesture.state_ = he::Gesture::kChange;
			break;
		case UIGestureRecognizerStateEnded:
			he::g_Gesture.state_ = he::Gesture::kEnd;
			break;
		case UIGestureRecognizerStateCancelled:
			he::g_Gesture.state_ = he::Gesture::kCancel;
			break;
		case UIGestureRecognizerStateFailed:
			he::g_Gesture.state_ = he::Gesture::kFail;
			break;
		case UIGestureRecognizerStatePossible:
			he::g_Gesture.state_ = he::Gesture::kPossible;
			break;
	}

	if(gesture.state == UIGestureRecognizerStateBegan || gesture.state == UIGestureRecognizerStateChanged){
		CGPoint pt = [gesture translationInView:view];
		he::g_Gesture.touch_point_ = GLKVector2Make(pt.x, pt.y);
		he::g_Gesture.action_ = he::Gesture::kDrag;
		he::g_Gesture.continious_ = true;
	}else{
		he::g_Gesture.Reset();
	}
}
@end
