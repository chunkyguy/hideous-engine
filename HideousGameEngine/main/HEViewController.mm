//
//  HEViewController.m
//  HideousGameEngine
//
//  Created by Sid on 10/02/13.
//  Copyright (c) 2013 whackylabs. All rights reserved.
//

#import "HEViewController.h"

#include <GLState.h>

#include "TestFactory.h"
//////////////////////////////////////////////////////////////////////////////////////////////////////
// MARK: Helper
//////////////////////////////////////////////////////////////////////////////////////////////////////

//Enable only one of these
#define TEST_RECT_COLOR
//#define TEST_RECT_TEXTURE
//#define TEST_RECT_TEXT
//#define TEST_MULTI_SHADERS
//#define TEST_MULTI_FONT
//#define TEST_ANIMATION
//#define TEST_TEXTURE_BIG_BANG
//#define TEST_GESTURE
//#define TEST_PARTICLES
//#define TEST_UI
//#define TEST_SPINE
//#define TEST_FLASH

ITest *GetTestFromFactory(float w, float h){
	
#if defined(TEST_RECT_COLOR)
	return MakeTest<RectColorTest>(w, h);
#elif defined(TEST_RECT_TEXTURE)
	return MakeTest<RectTextureTest>(w, h);
#elif defined(TEST_RECT_TEXT)
	return MakeTest<RectTextTest>(w, h);
#elif defined(TEST_MULTI_SHADERS)
	return MakeTest<MultiShadersTest>(w, h);
#elif defined(TEST_MULTI_FONT)
	return MakeTest<MultiFontTest>(w, h);
#elif defined(TEST_ANIMATION)
	return MakeTest<AnimationTest>(w, h);
#elif defined(TEST_TEXTURE_BIG_BANG)
	return MakeTest<TextureBigBangTest>(w, h);
#elif defined(TEST_GESTURE)
	return MakeTest<GestureTest>(w, h);
#elif defined(TEST_UI)
	return MakeTest<UITest>(w, h);
#elif defined(TEST_PARTICLES)
	return MakeTest<ParticleTest>(w, h);
#elif defined(TEST_SPINE)
	return MakeTest<SpineTest>(w, h);
#elif defined(TEST_FLASH)
	return MakeTest<FlashTest>(w, h);
#endif
	
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
// MARK: MainLoop
//////////////////////////////////////////////////////////////////////////////////////////////////////
@implementation MainLoop
-(void)dealloc{
	delete t;
	[super dealloc];
}
-(id)initWithSize:(CGSize)size{
	self = [super init];
	if(self){
		he::SetDefaultState();
		t = GetTestFromFactory(size.width,size.height);
	}
	return self;
}
- (void)glkViewControllerUpdate:(GLKViewController *)controller{
	t->Update(controller.timeSinceLastUpdate);
}
- (void)glkView:(GLKView *)view drawInRect:(CGRect)rect{
	t->Render();
}
- (void)glkViewController:(GLKViewController *)controller willPause:(BOOL)pause{
	
}
@end

//////////////////////////////////////////////////////////////////////////////////////////////////////
// MARK: HEViewController
//////////////////////////////////////////////////////////////////////////////////////////////////////
@interface HEViewController (_private)
@end

@implementation HEViewController
@synthesize context = _context;
@synthesize gestureCollector = _gestureCollector;
@synthesize loop = _loop;

- (void)didReceiveMemoryWarning{
    [super didReceiveMemoryWarning];
	
    if ([self isViewLoaded] && ([[self view] window] == nil)) {
        self.view = nil;
        if ([EAGLContext currentContext] == self.context) {
            [EAGLContext setCurrentContext:nil];
        }
        self.context = nil;
    }
}
-(BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)toInterfaceOrientation{
	return UIInterfaceOrientationIsLandscape(toInterfaceOrientation);
}
- (void)dealloc{
    if ([EAGLContext currentContext] == self.context) {
        [EAGLContext setCurrentContext:nil];
    }
    [_context release];
	[_gestureCollector release];
    [super dealloc];
}
- (void)viewDidLoad{
    [super viewDidLoad];
	self.delegate = nil;
    self.context = [[[EAGLContext alloc] initWithAPI:kEAGLRenderingAPIOpenGLES2] autorelease];
	NSAssert(self.context, @"Failed to create ES context");
    GLKView *view = (GLKView *)self.view;
    view.context = self.context;
	view.delegate = nil;
}
-(void)viewDidAppear:(BOOL)animated{
	
	[self setPreferredFramesPerSecond:60];
	self.loop = [[[MainLoop alloc] initWithSize:self.view.bounds.size] autorelease];
	self.delegate = self.loop;
	GLKView *view = (GLKView *)self.view;
	self.gestureCollector = [[[GestureCollector alloc] initWithView:view] autorelease];
	view.delegate = self.loop;
    [EAGLContext setCurrentContext:self.context];
}
-(void)viewDidDisapper:(BOOL)animated{
	[super viewDidDisappear:YES];
	self.loop = nil;
    [EAGLContext setCurrentContext:self.context];
}
-(void)touchesBegan:(NSSet *)touches withEvent:(UIEvent *)event{
	NSLog(@"ViewController: touchesBegan");
	[self.gestureCollector touches:touches action:kBegan withEvent:event];
}
-(void)touchesEnded:(NSSet *)touches withEvent:(UIEvent *)event{
	NSLog(@"ViewController: touchesEnded");
	[self.gestureCollector touches:touches action:kEnded withEvent:event];
}
-(void)touchesCancelled:(NSSet *)touches withEvent:(UIEvent *)event{
	NSLog(@"ViewController: touchesCancelled");
	[self.gestureCollector touches:touches action:kCancelled withEvent:event];
}
-(void)touchesMoved:(NSSet *)touches withEvent:(UIEvent *)event{
	NSLog(@"ViewController: touchesMoved");
	[self.gestureCollector touches:touches action:kMoved withEvent:event];
}
@end
