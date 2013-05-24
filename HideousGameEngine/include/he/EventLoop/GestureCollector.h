//
//  GestureCollector.h
//  HideousGameEngine
//
//  Created by Sid on 25/03/13.
//  Copyright (c) 2013 whackylabs. All rights reserved.
// 

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

typedef enum{
	kBegan, kMoved, kEnded, kCancelled
} TouchesAction;

@interface GestureCollector : NSObject{
	UIView *view;
	double lastPinchScale;	// To monitor change in scale
}
-(id)initWithView:(UIView *)view;
-(void)touches:(NSSet *)touches action:(TouchesAction)action withEvent:(UIEvent *)event;
@end
