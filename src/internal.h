#ifndef _internal_h_
#define _internal_h_

#include <macro/keyboard.h>
#include <macro/misc.h>
#include <macro/mouse.h>

namespace Macro {

namespace Keyboard {
namespace Internal {

extern KeyCallback keyCallback;

} // Internal
} // Keyboard

namespace Mouse {
namespace Internal {

extern MoveCallback moveCallback;
extern ButtonCallback buttonCallback;
extern ScrollCallback scrollCallback;

}  // namespace Internal
} // Mouse

}  // namespace Macro

#endif  // _internal_h_
