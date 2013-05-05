//
//  TextureAtlasParser.m
//  HideousGameEngine
//
//  Created by Sid on 12/02/13.
//  Copyright (c) 2013 whackylabs. All rights reserved.
//

#import <he/Texture/TextureAtlasParser.h>

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

namespace he{
	//	Do the parsing. Store normalized {name, tex_coord} in table
	TextureAtlasParser::TextureAtlasParser(std::string &filename){
		
		NSString *fname = [[NSString alloc] initWithCString:filename.c_str() encoding:NSASCIIStringEncoding];
		
		NSString *fpath = [[NSBundle mainBundle] pathForResource:fname ofType:@"plist"];
		NSDictionary *texDict = [[NSDictionary alloc] initWithContentsOfFile:fpath];
		[fname release];
		
		NSDictionary *framesDict = [texDict objectForKey:@"frames"];
		NSArray *imageNames = [[NSArray alloc] initWithArray:[framesDict allKeys]];
		NSArray *imageValues = [[NSArray alloc] initWithArray:[framesDict allValues]];
		
		NSDictionary *metaDict = [texDict objectForKey:@"metadata"];
		NSString *sizeStr = [metaDict objectForKey:@"size"];
		
		NSString *fullFrameStr = [[NSString alloc] initWithFormat:@"{{0,0},%@}",sizeStr];
		CGRect fullFrame = CGRectFromString(fullFrameStr);
		[fullFrameStr release];
		
		for(int i = 0; i < [imageNames count]; ++i){

			NSDictionary *frameDict = [imageValues objectAtIndex:i];
			NSString *frameStr = [frameDict objectForKey:@"textureRect"];
			CGRect frame = CGRectFromString(frameStr);

			float u = frame.origin.x;
			float v = frame.origin.y;
			v += frame.size.height;
			v = fullFrame.size.height - v;
			float s = u + frame.size.width;
			float t = v + frame.size.height;
			
			NSString *name = [imageNames objectAtIndex:i];
			std::string str_name([name cStringUsingEncoding:NSASCIIStringEncoding]);
			GLKVector4 coords = GLKVector4Make(u/fullFrame.size.width, v/fullFrame.size.height, s/fullFrame.size.width, t/fullFrame.size.height);
			table_[str_name] = coords;
		}
		[imageValues release];
		[imageNames release];
		[texDict release];
		
	}

	TextureAtlasParser::~TextureAtlasParser(){
		table_.clear();
	}

	std::map<std::string, GLKVector4> & TextureAtlasParser::GetTable(){
		return table_;
	}

	
}