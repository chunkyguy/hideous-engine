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
	TextureAtlasParser::TextureAtlasParser(std::string &path){
		
		NSString *path_str = [[NSString alloc] initWithCString:path.c_str() encoding:NSASCIIStringEncoding];
		NSDictionary *texDict = [[NSDictionary alloc] initWithContentsOfFile:path_str];
		[path_str release];

		// Get metadata
		NSDictionary *metaDict = [texDict objectForKey:@"metadata"];
		NSString *sizeStr = [metaDict objectForKey:@"size"];
		CGSize size = CGSizeFromString(sizeStr);
		size_.x = size.width;
		size_.y = size.height;

		NSDictionary *framesDict = [texDict objectForKey:@"frames"];
		NSArray *imageNames = [[NSArray alloc] initWithArray:[framesDict allKeys]];
		NSArray *imageValues = [[NSArray alloc] initWithArray:[framesDict allValues]];
			
		
		for(int i = 0; i < [imageNames count]; ++i){
			NSDictionary *frameDict = [imageValues objectAtIndex:i];
			NSString *name = [imageNames objectAtIndex:i];
			std::string str_name([name cStringUsingEncoding:NSASCIIStringEncoding]);

			TextureAtlasRegion region;
			region.name = str_name;
			
			CGRect spriteColorRect = CGRectFromString([frameDict objectForKey:@"spriteColorRect"]);
			region.sprite_color_rect = GLKVector4Make(spriteColorRect.origin.x, spriteColorRect.origin.y, spriteColorRect.size.width, spriteColorRect.size.height);
			
			CGSize spriteOffset = CGSizeFromString([frameDict objectForKey:@"spriteOffset"]);
			region.sprite_offset = GLKVector2Make(spriteOffset.width, spriteOffset.height);
			
			CGSize spriteSize = CGSizeFromString([frameDict objectForKey:@"spriteSize"]);
			region.sprite_size = GLKVector2Make(spriteSize.width, spriteSize.height);
			
			CGSize spriteSourceSize = CGSizeFromString([frameDict objectForKey:@"spriteSourceSize"]);
			region.sprite_source_size = GLKVector2Make(spriteSourceSize.width, spriteSourceSize.height);
			
			BOOL spriteTrimmed = [[frameDict  objectForKey:@"spriteColorRect"] boolValue];
			region.sprite_trimmed = spriteTrimmed ? true : false;
			
			CGRect textureRect = CGRectFromString([frameDict objectForKey:@"textureRect"]);
			region.texture_rect = GLKVector4Make(textureRect.origin.x, textureRect.origin.y, textureRect.size.width, textureRect.size.height);
			
			BOOL textureRotated = [[frameDict objectForKey:@"textureRotated"]boolValue];
			region.texture_rotated = textureRotated ? true : false;
			

			float u = textureRect.origin.x;
			float v = textureRect.origin.y;
			v += textureRect.size.height;
			v = size.height - v;
			float s = u + textureRect.size.width;
			float t = v + textureRect.size.height;
			
			region.tex_coords = GLKVector4Make(u/size.width, v/size.height, s/size.width, t/size.height);
			table_[str_name] = region;
		}
		[imageValues release];
		[imageNames release];
		[texDict release];
		
	}

	TextureAtlasParser::~TextureAtlasParser(){
		table_.clear();
	}

	std::map<std::string, TextureAtlasRegion> & TextureAtlasParser::GetTable(){
		return table_;
	}

	
}