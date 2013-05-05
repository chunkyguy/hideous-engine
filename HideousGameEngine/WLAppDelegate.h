//
//  WLAppDelegate.h
//  HideousGameEngine
//
//  Created by Sid on 02/05/13.
//  Copyright (c) 2013 whackylabs. All rights reserved.
//

#import <UIKit/UIKit.h>
@class HEViewController;
@interface WLAppDelegate : UIResponder <UIApplicationDelegate>
@property (strong, nonatomic) HEViewController * viewController;
@property (strong, nonatomic) UIWindow *window;

@end
