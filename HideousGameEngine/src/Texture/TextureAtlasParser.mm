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

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// MARK: StarlingXMLParser
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
@interface StarlingXMLParser : NSObject <NSXMLParserDelegate>{
	std::map<const std::string, he::TextureAtlasRegion> *table_;
	NSXMLParser *parser_;
	bool done_;
	std::string image_name_;
	std::map<const std::string, he::TextureAtlasRegion>::iterator pos_hint_;
	GLKVector2 size_;
}
-(bool) parse;
-(std::string) getImageName;
@end

@implementation StarlingXMLParser
-(id) initWithPath:(const char *)path
			 table:(std::map<const std::string, he::TextureAtlasRegion> *)table
size:(const GLKVector2)size
{
	self = [super init];
	if(self){
		table_ = table;
		done_ = false;
		pos_hint_ = table_->begin();
		size_ = size;
		
		NSString *xml_path = [[NSString alloc] initWithCString:path encoding:NSASCIIStringEncoding];
		NSURL *xml_url = [[NSURL alloc] initFileURLWithPath:xml_path];
		[xml_path release];
		
		parser_ = [[NSXMLParser alloc] initWithContentsOfURL:xml_url];
		[parser_ setDelegate:self];
		[xml_url release];
	}
	return self;
}

-(void) dealloc{
	[parser_ release];
	[super dealloc];
}

//	Returns true if done, else false
-(bool) parse{
	[parser_ parse];
	
	return done_;
}

-(std::string) getImageName{
	return image_name_;
}

-(void) parser:(NSXMLParser *)parser
didStartElement:(NSString *)elementName
  namespaceURI:(NSString *)namespaceURI
 qualifiedName:(NSString *)qName
	attributes:(NSDictionary *)attributeDict{
	
	if([elementName isEqualToString:@"TextureAtlas"]){
		NSString *name = [attributeDict objectForKey:@"imagePath"];
		image_name_ = std::string([name cStringUsingEncoding:NSASCIIStringEncoding]);
	}else if ([elementName isEqualToString:@"SubTexture"]){
		std::string name([[attributeDict objectForKey:@"name"] cStringUsingEncoding:NSASCIIStringEncoding]);
		float x = [[attributeDict objectForKey:@"x"] floatValue];
		float y = [[attributeDict objectForKey:@"y"] floatValue];
		float width = [[attributeDict objectForKey:@"width"] floatValue];
		float height = [[attributeDict objectForKey:@"height"] floatValue];

		NSArray *keys = [attributeDict allKeys];
		float frame_x = ([keys containsObject:@"frameX"]) ? [[attributeDict objectForKey:@"frameX"] floatValue] * -1 : 0.0f;
		float frame_y = ([keys containsObject:@"frameY"]) ? [[attributeDict objectForKey:@"frameY"] floatValue] : 0.0f;

// TODO: WTF is frameWidth, frameHeight?
//		float frame_width = ([keys containsObject:@"frameWidth"]) ? [[attributeDict objectForKey:@"frameWidth"] floatValue] : width;
//		float frame_height = ([keys containsObject:@"frameHeight"]) ? [[attributeDict objectForKey:@"frameHeight"] floatValue] : height;
		float frame_width = width; float frame_height = height;
		
		GLKVector4 texture_rect = GLKVector4Make(x, y, width, height);
		GLKVector2 sprite_offset = GLKVector2Make(frame_x, frame_y);
		GLKVector2 sprite_size = GLKVector2Make(frame_width, frame_height);
		he::TextureAtlasRegion region(name, texture_rect, size_, sprite_offset, sprite_size);
		// save
		pos_hint_ = table_->insert(pos_hint_, std::make_pair(name, region));
	}
}

-(void) parser:(NSXMLParser *)parser
 didEndElement:(NSString *)elementName
  namespaceURI:(NSString *)namespaceURI
 qualifiedName:(NSString *)qName{
	
	if([elementName isEqualToString:@"TextureAtlas"]){
		done_ = true;
	}else if ([elementName isEqualToString:@"SubTexture"]){
	}
}
@end

#include <he/Utils/DebugHelper.h>

namespace he{
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// MARK: StarlingDataParser
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	StarlingDataParser::StarlingDataParser(const std::string &path, const GLKVector2 img_size) :
	size_(img_size)
	{
		NSString *path_str = [[NSString alloc] initWithCString:path.c_str() encoding:NSASCIIStringEncoding];
		NSDictionary *texDict = [[NSDictionary alloc] initWithContentsOfFile:path_str];
		[path_str release];

		StarlingXMLParser *parser = [[StarlingXMLParser alloc] initWithPath:path.c_str() table:&table_ size:size_];
		bool ret = [parser parse];
		assert(ret);		// Parsing was incomplete
		[parser release];
		[texDict release];		
	}
	
	StarlingDataParser::~StarlingDataParser(){
		table_.clear();
	}
	
	const std::map<const std::string, TextureAtlasRegion> &StarlingDataParser::GetTable() const{
		return table_;
	}
	
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// MARK: ZwoptexDataParser
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//	Do the parsing. Store normalized {name, tex_coord} in table
	ZwoptexDataParser::ZwoptexDataParser(const std::string &path){
		
		NSString *path_str = [[NSString alloc] initWithCString:path.c_str() encoding:NSASCIIStringEncoding];
		NSDictionary *texDict = [[NSDictionary alloc] initWithContentsOfFile:path_str];
		[path_str release];
		
		// Get metadata
		NSDictionary *metaDict = [texDict objectForKey:@"metadata"];
		NSString *sizeStr = [metaDict objectForKey:@"size"];
		CGSize sz = CGSizeFromString(sizeStr);
		size_.x = sz.width;
		size_.y = sz.height;
		
		NSDictionary *framesDict = [texDict objectForKey:@"frames"];
		NSArray *imageNames = [[NSArray alloc] initWithArray:[framesDict allKeys]];
		NSArray *imageValues = [[NSArray alloc] initWithArray:[framesDict allValues]];
		
		std::map<const std::string, TextureAtlasRegion>::iterator pos_hint = table_.begin();
		for(int i = 0; i < [imageNames count]; ++i){
			NSDictionary *frameDict = [imageValues objectAtIndex:i];
			
			/*mandatory*/
			NSString *img_name = [imageNames objectAtIndex:i];
			std::string name([img_name cStringUsingEncoding:NSASCIIStringEncoding]);

			CGRect textureRect = CGRectFromString([frameDict objectForKey:@"textureRect"]);
			GLKVector4 texture_rect = GLKVector4Make(textureRect.origin.x, textureRect.origin.y, textureRect.size.width, textureRect.size.height);

			GLKVector2 total_texture_size = size_;

			/*optional*/
			CGSize spriteOffset = CGSizeFromString([frameDict objectForKey:@"spriteOffset"]);
			GLKVector2 sprite_offset = GLKVector2Make(spriteOffset.width, spriteOffset.height);

			BOOL spriteTrimmed = [[frameDict  objectForKey:@"spriteColorRect"] boolValue];
			bool sprite_trimmed = spriteTrimmed ? true : false;


			BOOL textureRotated = [[frameDict objectForKey:@"textureRotated"]boolValue];
			bool texture_rotated = textureRotated ? true : false;


			/*derivable from other data*/
			CGRect spriteColorRect = CGRectFromString([frameDict objectForKey:@"spriteColorRect"]);
			GLKVector4 sprite_color_rect = GLKVector4Make(spriteColorRect.origin.x, spriteColorRect.origin.y, spriteColorRect.size.width, spriteColorRect.size.height);

			CGSize spriteSize = CGSizeFromString([frameDict objectForKey:@"spriteSize"]);
			GLKVector2 sprite_size = GLKVector2Make(spriteSize.width, spriteSize.height);

			CGSize spriteSourceSize = CGSizeFromString([frameDict objectForKey:@"spriteSourceSize"]);
			GLKVector2 sprite_source_size = GLKVector2Make(spriteSourceSize.width, spriteSourceSize.height);
			
			
			TextureAtlasRegion region(name,
									  texture_rect,
									  total_texture_size,
									  sprite_offset,
									  sprite_size,
									  sprite_trimmed,
									  texture_rotated,
									  sprite_color_rect,
									  sprite_source_size);


			pos_hint = table_.insert(pos_hint, std::make_pair(name, region));
		}
		[imageValues release];
		[imageNames release];
		[texDict release];		
	}
	
	ZwoptexDataParser::~ZwoptexDataParser(){
		table_.clear();
	}
	
	const std::map<const std::string, TextureAtlasRegion> & ZwoptexDataParser::GetTable() const{
		return table_;
	}
}

///EOF