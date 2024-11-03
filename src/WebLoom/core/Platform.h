//  WebLoom Framework
//  Copyright (C) 2024 WebLoom Framework contributors
//  Released under LGPL 3.0 license (see LICENSE)
#ifndef CORE_PLATFORM_H_
#define CORE_PLATFORM_H_
#include <assert.h>

namespace webloom::core {

#define WEBLOOM_PLATFORM_WINDOWS      1
#define WEBLOOM_PLATFORM_WINDOWS_MSVC 2
#define WEBLOOM_PLATFORM_LINUX        3

#if (defined( __WIN32__ ) || defined( _WIN32 )) && !defined(__ANDROID__)
#  if defined(_MSC_VER)
#    define WEBLOOM_PLATFORM WEBLOOM_PLATFORM_WINDOWS_MSVC
#  else
#    define WEBLOOM_PLATFORM WEBLOOM_PLATFORM_WINDOWS
#  endif
#else
#    define WEBLOOM_PLATFORM WEBLOOM_PLATFORM_LINUX
#endif

}   // namespace webloom::core

#endif  // CORE_PLATFORM_H_
