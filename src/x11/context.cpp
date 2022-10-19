#include <macro/mouse.h>

#include "../internal.h"
#include "../platform.h"

namespace Macro {

Display *_Context::GetDisplay() {
    if (display == nullptr) {
        display = XOpenDisplay(NULL);
    }
    return display;
}

_Context::_Context() : display(nullptr) {}

_Context::~_Context() {
    if (display != nullptr) {
        XCloseDisplay(display);
    }
}

_Context ctx;

}  // namespace Macro
