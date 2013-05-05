//
//  TextureCreator.m
//  HideousGameEngine
//
//  Created by Sid on 11/02/13.
//  Copyright (c) 2013 whackylabs. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

#include <he/Texture/TextureData.h>
#import <he/Utils/Utils.h>

namespace he{
		
	TextureData::TextureData(std::string &name, std::string extension){
		NSString *name_str = [[NSString alloc] initWithCString:name.c_str() encoding:NSASCIIStringEncoding];
		NSString *extension_str = [[NSString alloc] initWithCString:extension.c_str() encoding:NSASCIIStringEncoding];
		NSData *texData = [[NSData alloc] initWithContentsOfFile:[[NSBundle mainBundle] pathForResource:name_str ofType:extension_str]];
		UIImage *image = [[UIImage alloc] initWithData:texData];
		NSLog(@"Loading texture: %@.%@",name_str,extension_str);
		assert(image);
		width_ = NextPOT(CGImageGetWidth(image.CGImage));
		height_ = NextPOT(CGImageGetHeight(image.CGImage));
		CGColorSpaceRef colorSpace = CGColorSpaceCreateDeviceRGB();
		data_ = new GLubyte[height_ * width_ * 4];	//4 bytes per pixel RGBA
		CGContextRef context = CGBitmapContextCreate( data_, width_, height_, 8, 4 * width_, colorSpace, kCGImageAlphaPremultipliedLast | kCGBitmapByteOrder32Big );
		CGColorSpaceRelease( colorSpace );
		CGContextClearRect( context, CGRectMake( 0, 0, width_, height_ ) );
		//flip the image
		CGContextTranslateCTM( context, 0, height_ );
		CGContextScaleCTM(context, 1, -1);
		CGContextDrawImage( context, CGRectMake( 0, 0, width_, height_ ), image.CGImage );
		
		//free up
		CGContextRelease(context);
		[image release];
		[texData release];
		[extension_str release];
		[name_str release];
	}
	
	TextureData::~TextureData(){
		delete data_;
	}

}//EOF