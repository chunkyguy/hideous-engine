//
//  HideousEngine.cpp
//  HideousGameEngine
//
//  Created by Sid on 15/06/13.
//  Copyright (c) 2013 whackylabs. All rights reserved.
//

#import <he/Main/HideousEngine.h>
#import <he/EventLoop/GestureCollector.h>
#import <he/Utils/GLState.h>
#import <he/Utils/DebugHelper.h>

he::GameConfig *g_config = nullptr;

/////////////////////////////////////////////////////////////////////////////////////////////////////////
// MARK: HELoop
/////////////////////////////////////////////////////////////////////////////////////////////////////////
@interface HELoop : NSObject <GLKViewControllerDelegate, GLKViewDelegate>{
 he::Game *game;
}
-(id)initWithSize:(CGSize)size;
@end

@implementation HELoop
-(void)dealloc{
 [super dealloc];
}
-(id)initWithSize:(CGSize)size{
 self = [super init];
 if(self){
  he::SetDefaultState();
  GLKVector2 sz = GLKVector2Make(size.width, size.height);
  game = g_config->CreateGame(sz);
 }
 return self;
}
- (void)glkViewControllerUpdate:(GLKViewController *)controller{
 game->Update(controller.timeSinceLastUpdate);
}
- (void)glkView:(GLKView *)view drawInRect:(CGRect)rect{
 game->Render();
}
- (void)glkViewController:(GLKViewController *)controller willPause:(BOOL)pause{
 game->Pause(pause==YES);
}
@end


/////////////////////////////////////////////////////////////////////////////////////////////////////////
// MARK: HEController
/////////////////////////////////////////////////////////////////////////////////////////////////////////
@interface HEController(){
 EAGLContext *_context;
 GestureCollector *_gestureCollector;
 HELoop *_loop;
}
@property (retain, nonatomic) EAGLContext *context;
@property (retain, nonatomic) GestureCollector *gestureCollector;
@property (retain, nonatomic) HELoop *loop;
@end

@implementation HEController
@synthesize context;
@synthesize gestureCollector;
@synthesize loop;

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
#if defined(__HideousGameEngine__DEBUG_MODE__)
 GLKView *glvw = (GLKView*)self.view;
 switch (glvw.drawableColorFormat) {
  case GLKViewDrawableColorFormatRGBA8888: NSLog(@"Color: RGBA8888"); break;
  case GLKViewDrawableColorFormatRGB565: NSLog(@"Color: RGBA565"); break;
 }
 switch (glvw.drawableDepthFormat) {
  case GLKViewDrawableDepthFormatNone: NSLog(@"Depth: None"); break;
  case GLKViewDrawableDepthFormat16: NSLog(@"Depth: 16 bit"); break;
  case GLKViewDrawableDepthFormat24: NSLog(@"Depth: 24 bit"); break;
 }
 switch (glvw.drawableStencilFormat) {
  case GLKViewDrawableStencilFormatNone: NSLog(@"Stencil: None"); break;
  case GLKViewDrawableStencilFormat8: NSLog(@"Stencil: 8 bit"); break;
 }
 switch (glvw.drawableMultisample) {
  case GLKViewDrawableMultisampleNone: NSLog(@"Multisample: None"); break;
  case GLKViewDrawableMultisample4X: NSLog(@"Multisample: 4x"); break;
 }
#endif
}
-(void)viewDidAppear:(BOOL)animated{
 [self setPreferredFramesPerSecond:60];
 self.loop = [[[HELoop alloc] initWithSize:self.view.bounds.size] autorelease];
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
 [self.gestureCollector touches:touches action:kBegan withEvent:event];
}
-(void)touchesEnded:(NSSet *)touches withEvent:(UIEvent *)event{
 [self.gestureCollector touches:touches action:kEnded withEvent:event];
}
-(void)touchesCancelled:(NSSet *)touches withEvent:(UIEvent *)event{
 [self.gestureCollector touches:touches action:kCancelled withEvent:event];
}
-(void)touchesMoved:(NSSet *)touches withEvent:(UIEvent *)event{
 [self.gestureCollector touches:touches action:kMoved withEvent:event];
}
@end

/////////////////////////////////////////////////////////////////////////////////////////////////////////
// MARK: HEAppDelegate
/////////////////////////////////////////////////////////////////////////////////////////////////////////
@interface HEAppDelegate()
@property (strong, nonatomic) HEController * viewController;
@end

@implementation HEAppDelegate
@synthesize viewController;
@synthesize window;

- (void)dealloc{
 self.window = nil;
 self.viewController = nil;
 [super dealloc];
}


- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions{
 [application setStatusBarHidden:YES];
 self.window = [[[UIWindow alloc] initWithFrame:[[UIScreen mainScreen] bounds]] autorelease];
 // Override point for customization after application launch.
 self.viewController = [[[HEController alloc] initWithNibName:nil bundle:nil] autorelease];
 self.window.rootViewController = self.viewController;
 [self.window makeKeyAndVisible];
 return YES;
}

- (void)applicationWillResignActive:(UIApplication *)application{
 // Sent when the application is about to move from active to inactive state. This can occur for certain types of temporary interruptions (such as an incoming phone call or SMS message) or when the user quits the application and it begins the transition to the background state.
 // Use this method to pause ongoing tasks, disable timers, and throttle down OpenGL ES frame rates. Games should use this method to pause the game.
}

- (void)applicationDidEnterBackground:(UIApplication *)application{
 // Use this method to release shared resources, save user data, invalidate timers, and store enough application state information to restore your application to its current state in case it is terminated later.
 // If your application supports background execution, this method is called instead of applicationWillTerminate: when the user quits.
}

- (void)applicationWillEnterForeground:(UIApplication *)application{
 // Called as part of the transition from the background to the inactive state; here you can undo many of the changes made on entering the background.
}

- (void)applicationDidBecomeActive:(UIApplication *)application{
 // Restart any tasks that were paused (or not yet started) while the application was inactive. If the application was previously in the background, optionally refresh the user interface.
}

- (void)applicationWillTerminate:(UIApplication *)application{
 // Called when the application is about to terminate. Save data if appropriate. See also applicationDidEnterBackground:.
}
@end

/////////////////////////////////////////////////////////////////////////////////////////////////////////
// MARK: main
/////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifdef __HideousGameEngine__DEBUG_MODE__
#import <he/Utils/GTests.h>
#endif

int HideousEngineInit(int argc, char **argv, he::GameConfig &config){
 g_config = &config;
 
#ifdef __HideousGameEngine__DEBUG_MODE__
 int utest_res = GTests(argc, argv);	// If unit tests fails return, else launch the app.
 if(utest_res != 0){
  return utest_res;
 }
#endif
 
 @autoreleasepool {
  return UIApplicationMain(argc, argv, nil, NSStringFromClass([HEAppDelegate class]));
 }
}

///EOF
