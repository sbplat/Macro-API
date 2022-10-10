#ifndef _platform_h_
#define _platform_h_

#include "internal.h"

#if defined(_MACRO_WIN32)
    #include <windows.h>
#elif defined(_MACRO_COCOA)
    #error "Unimplemented platform"
#elif defined(_MACRO_X11)
    #error "Unimplemented platform"
#else
    #error "Unknown platform"
#endif

#endif // _platform_h_
