#ifndef _internal_h_
#define _internal_h_

#include <macro/keyboard.h>
#include <macro/misc.h>
#include <macro/mouse.h>

#include "platform.h"

namespace Macro {
namespace Internal {
#if defined(_MACRO_WIN32)
#elif defined(_MACRO_COCOA)
#elif defined(_MACRO_X11)
extern Display *display;
#endif
}  // namespace Internal

namespace Keyboard {
namespace Internal {

bool KeyCb(Key key, KeyState state);

extern KeyStateMap keyStates;

extern KeyCallback keyCallback;

}  // namespace Internal
}  // namespace Keyboard

namespace Mouse {
namespace Internal {

extern ButtonStateMap buttonStates;

bool MoveCb(Point position);
bool ButtonCb(Button button, ButtonState state);
bool ScrollCb(int delta, bool isHorizontal);

extern MoveCallback moveCallback;
extern ButtonCallback buttonCallback;
extern ScrollCallback scrollCallback;

}  // namespace Internal
}  // namespace Mouse

}  // namespace Macro

#endif  // _internal_h_
