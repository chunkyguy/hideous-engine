//
//  gtest_main.h
//  TestGTEST
//
//  Created by Sid on 15/06/13.
//  Copyright (c) 2013 whackylabs. All rights reserved.
//

#ifndef TestGTEST_gtest_main_h
#define TestGTEST_gtest_main_h

#include <he/Utils/DebugHelper.h>

#ifdef __HideousGameEngine__DEBUG_MODE__
#include <gtest/gtest.h>
GTEST_API_ int GTests(int argc, char **argv);
#endif /*__HideousGameEngine__DEBUG_MODE__*/

#endif /*TestGTEST_gtest_main_h*/