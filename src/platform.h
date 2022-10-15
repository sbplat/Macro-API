#ifndef _platform_h_
#define _platform_h_

#if defined(_MACRO_WIN32)
    #include <windows.h>
#elif defined(_MACRO_COCOA)
    #warning "Macro API for Cocoa is still WIP"
    #include <CoreFoundation/CoreFoundation.h>
    #include <ApplicationServices/ApplicationServices.h>
#elif defined(_MACRO_X11)
    #warning "Macro API for X11 is still WIP"
    #include <X11/Xlib.h>
    #include <X11/Xutil.h>
#else
    #error "Unknown platform"
#endif

#endif  // _platform_h_
