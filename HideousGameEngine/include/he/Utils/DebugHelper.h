//
//  DebugHelper.h
//  HideousGameEngine
//
//  Created by Sid on 06/06/13.
//  Copyright (c) 2013 whackylabs. All rights reserved.
//

#ifndef __HideousGameEngine__DebugHelper__
#define __HideousGameEngine__DebugHelper__

/*******************************************************************************
 *	Select mode:
 *	Comment/Uncomment '__HideousGameEngine__DEBUG_MODE__' to disable/enable debug mode.
 ******************************************************************************/

//#define __HideousGameEngine__DEBUG_MODE__


#ifdef __HideousGameEngine__DEBUG_MODE__ /* DEBUG MODE */
#include <iostream>
#include <stdexcept>
#include <iomanip>

void he_Trace(const char* s);

template<typename T, typename... Args>
void he_Trace(const char* s, const T& value, const Args&... args) {
	std::cout << std::setprecision(10);
	std::cout << std::boolalpha;
	while (*s) {
		if (*s == '%' && *++s != '%') {
			std::cout << value;
			return he_Trace(++s, args...);
		}else{
			std::cout << *s++;
		}
	}
	throw std::runtime_error("extra arguments provided to he_Trace");
}

#else					/* RELEASE MODE */
#define he_Trace(...)	// Comment trace statements
#define NDEBUG			// Comment asserts
#endif					/*__HideousGameEngine__DEBUG_MODE__*/
#include <cassert>


#endif /* defined(__HideousGameEngine__DebugHelper__) */

/**	Usage: Just like a printf/NSLog
 std::string str("Hello World");
 int i = 100;
 float f = 100.2250011245;
 Rect r(20, 40);
 
 he_Trace( "Printing string: %@\n", str);
 he_Trace("Printing int: %d\n", i);
 he_Trace("Printing float: %f\n", f);
 he_Trace("Printing rect: %@\n", r);
 he_Trace("Printing int %d + float: %f\n", i, f);
 he_Trace("Printing int %d + rect: %@\n", i, r);
 he_Trace("Printing int %d + float %f + rect: %@\n", i, f, r);
 */

//	To trace a custom class, provide a operator<<().
//	Example:
/*
 #include <ostream>
 
 template <typename T>
 friend std::ostream &operator<<(std::ostream &os, const T &rec){
 // stream data to os here...
 return os;
 }
 */