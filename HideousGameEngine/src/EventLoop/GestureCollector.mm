//
//  GestureCollector.m
//  HideousGameEngine
//
//  Created by Sid on 25/03/13.
//  Copyright (c) 2013 whackylabs. All rights reserved.
//

#import <he/EventLoop/GestureCollector.h>
#include <he/EventLoop/Gesture.h>

@interface GestureCollector (){

}
@end

@implementation GestureCollector
-(id)initWithView:(UIView *)vw{
	self = [super init];
	if(self){
		view = vw;
		
		// Resgistering Gestures
//		UILongPressGestureRecognizer *singleTapDownGesture = [[UILongPressGestureRecognizer alloc] initWithTarget:self action:@selector(singleTapDownGestureAction:)];
//		[view addGestureRecognizer:singleTapDownGesture];
//		[singleTapDownGesture release];
		
//		UITapGestureRecognizer *singleTapGesture = [[UITapGestureRecognizer alloc] initWithTarget:self action:@selector(singleTapGestureAction:)];
//		[view addGestureRecognizer:singleTapGesture];
//		[singleTapGesture release];
		
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

// Long press event.
/*
-(void)singleTapDownGestureAction:(UILongPressGestureRecognizer *)gesture{
	he::Gesture g;
	g.continious_ = true;
	g.fingers_ = [gesture numberOfTouches];
	g.taps_ = 1;
	g.action_ = he::Gesture::kLongTap;
	CGPoint tPt = [gesture locationInView:view];
	g.touch_point_ = GLKVector2Make(tPt.x, tPt.y);

	switch(gesture.state){
			
		case UIGestureRecognizerStateBegan:		g.state_ = he::Gesture::kBegin;		break;
		case UIGestureRecognizerStateChanged:	g.state_ = he::Gesture::kChange;		break;
		case UIGestureRecognizerStateEnded:		g.state_ = he::Gesture::kEnd;		break;
		case UIGestureRecognizerStateCancelled:	g.state_ = he::Gesture::kCancel;		break;
		case UIGestureRecognizerStateFailed:		g.state_ = he::Gesture::kFail;		break;
		case UIGestureRecognizerStatePossible:	g.state_ = he::Gesture::kPossible;	break;
	}

	he::g_EventLoop->SetGesture(g);
}
*/

-(void) pinchGestureAction:(UIPinchGestureRecognizer *)gesture{
	he::Gesture g;
	if(gesture.scale < lastPinchScale){	//zoom out
		g.action_ = he::Gesture::kZoomOut;
	}else{	// zoom in
		g.action_ = he::Gesture::kZoomIn;
	}
	g.continious_ = true;
	g.fingers_ = 2;
	g.velocity_ = GLKVector2MultiplyScalar(g.velocity_, fabs(gesture.velocity));
	lastPinchScale = gesture.scale;
	
	switch(gesture.state){
		case UIGestureRecognizerStateBegan:		g.state_ = he::Gesture::kBegin;		break;
		case UIGestureRecognizerStateChanged:	g.state_ = he::Gesture::kChange;		break;
		case UIGestureRecognizerStateEnded:		g.state_ = he::Gesture::kEnd;		break;
		case UIGestureRecognizerStateCancelled:	g.state_ = he::Gesture::kCancel;		break;
		case UIGestureRecognizerStateFailed:		g.state_ = he::Gesture::kFail;		break;
		case UIGestureRecognizerStatePossible:	g.state_ = he::Gesture::kPossible;	break;
	}
	
	he::g_EventLoop->SetGesture(g);
}

-(void)dragGestureAction:(UIPanGestureRecognizer *)gesture{	
	he::Gesture g;
	CGPoint pt = [gesture translationInView:view];
	g.touch_point_ = GLKVector2Make(pt.x, pt.y);
	g.action_ = he::Gesture::kDrag;
	g.continious_ = true;

	switch(gesture.state){
		case UIGestureRecognizerStateBegan:		g.state_ = he::Gesture::kBegin;		break;
		case UIGestureRecognizerStateChanged:	g.state_ = he::Gesture::kChange;		break;
		case UIGestureRecognizerStateEnded:		g.state_ = he::Gesture::kEnd;		break;
		case UIGestureRecognizerStateCancelled:	g.state_ = he::Gesture::kCancel;		break;
		case UIGestureRecognizerStateFailed:		g.state_ = he::Gesture::kFail;		break;
		case UIGestureRecognizerStatePossible:	g.state_ = he::Gesture::kPossible;	break;
	}

	he::g_EventLoop->SetGesture(g);
}

// For single tap gesture
-(void)touches:(NSSet *)touches action:(TouchesAction)action withEvent:(UIEvent *)event{
	he::Gesture g;
	g.continious_ = false;
	g.fingers_ = 1;
	g.taps_ = 1;
	g.action_ = he::Gesture::kTap;
	CGPoint tPt = [[touches anyObject] locationInView:view];
	g.touch_point_ = GLKVector2Make(tPt.x, tPt.y);
	
	switch(action){
			
		case kBegan:		g.state_ = he::Gesture::kBegin;	break;
		case kEnded:		g.state_ = he::Gesture::kEnd;	break;
		case kCancelled:	g.state_ = he::Gesture::kCancel;	break;
		case kMoved:
		default:
			break;
	}
	
	he::g_EventLoop->SetGesture(g);
}

@end
