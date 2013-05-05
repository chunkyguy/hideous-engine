//
//  HEViewController.h
//  HideousGameEngine
//
//  Created by Sid on 10/02/13.
//  Copyright (c) 2013 whackylabs. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <GLKit/GLKit.h>

#include <GestureCollector.h>

#include "TestTemplate.h"

@interface MainLoop : NSObject <GLKViewControllerDelegate, GLKViewDelegate>{
	ITest *t;
}
-(id)initWithSize:(CGSize)size;
@end

@interface HEViewController : GLKViewController{
	EAGLContext *_context;
	GestureCollector *_gestureCollector;
	MainLoop *_loop;
}
@property (retain, nonatomic) EAGLContext *context;
@property (retain, nonatomic) GestureCollector *gestureCollector;
@property (retain, nonatomic) MainLoop *loop;

@end
