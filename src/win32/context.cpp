#include <macro/mouse.h>

#include "../internal.h"
#include "../platform.h"

namespace Macro {

_Context::_Context() {
    // Make our process DPI-aware.
    SetProcessDPIAware();
}

_Context::~_Context() {}

_Context ctx;

}  // namespace Macro
