////////////////////////////////////////////////////////////
//
// SFML - Simple and Fast Multimedia Library
// Copyright (C) 2007-2012 Marco Antognini (antognini.marco@gmail.com),
//                         Laurent Gomila (laurent.gom@gmail.com),
//
// This software is provided 'as-is', without any express or implied warranty.
// In no event will the authors be held liable for any damages arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it freely,
// subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented;
//    you must not claim that you wrote the original software.
//    If you use this software in a product, an acknowledgment
//    in the product documentation would be appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such,
//    and must not be misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source distribution.
//
////////////////////////////////////////////////////////////

/*****************************************************************************************************************************************
 *	Code additions by Sidharth Juyal.
 *****************************************************************************************************************************************/

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#import <Foundation/Foundation.h>

#include <he/Utils/ResourcePath.hpp>
////////////////////////////////////////////////////////////
namespace he{
	
	
	std::string ResourcePath(void)	{
		std::string rpath;

		@autoreleasepool {
			NSBundle* bundle = [NSBundle mainBundle];
			if (bundle == nil) {
#ifdef DEBUG
				NSLog(@"bundle is nil... thus no resources path can be found.");
#endif
			} else {
				NSString* path = [bundle resourcePath];
				rpath = [path UTF8String] + std::string("/");
			}

		}

		return rpath;
	}
	
	std::string DocumentsPath(void) {
		std::string rpath;

		@autoreleasepool {
			NSArray *paths = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES);
			if (!paths || ![paths count]) {
#ifdef DEBUG
				NSLog(@"No path can be found.");
#endif
			} else {
				NSString *path = [paths objectAtIndex:0];
				rpath = [path UTF8String] + std::string("/");
			}
		}
		
		return rpath;
	}
	
}