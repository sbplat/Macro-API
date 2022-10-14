#ifndef _internal_h_
#define _internal_h_

#include <macro/keyboard.h>
#include <macro/misc.h>
#include <macro/mouse.h>

namespace Macro {

namespace Keyboard {
namespace Internal {

bool KeyCb(Key key, KeyState state);

extern KeyStateMap keyStates;

extern KeyCallback keyCallback;

}  // namespace Internal
}  // namespace Keyboard

namespace Mouse {
namespace Internal {

extern MoveCallback moveCallback;
extern ButtonCallback buttonCallback;
extern ScrollCallback scrollCallback;

}  // namespace Internal
}  // namespace Mouse

}  // namespace Macro

#endif  // _internal_h_
