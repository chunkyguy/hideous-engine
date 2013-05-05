//
//  GestureCollector.h
//  HideousGameEngine
//
//  Created by Sid on 25/03/13.
//  Copyright (c) 2013 whackylabs. All rights reserved.
// 

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

@interface GestureCollector : NSObject{
	UIView *view;
	double lastPinchScale;	// To monitor change in scale
}
-(id)initWithView:(UIView *)view;
@end
