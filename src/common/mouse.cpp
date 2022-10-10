#include <macro/mouse.h>

#include "../internal.h"
#include "../platform.h"

namespace Macro {
namespace Mouse {

const char* GetButtonName(Button button) {
    switch (button) {
        case LEFT: return "Left";
        case RIGHT: return "Right";
        case MIDDLE: return "Middle";
        case X1: return "X1";
        case X2: return "X2";
        default: return "Unknown";
    }
}

namespace Internal {

MoveCallback moveCallback = nullptr;
ButtonCallback buttonCallback = nullptr;
ScrollCallback scrollCallback = nullptr;

} // Internal

void SetMoveCallback(MoveCallback callback) {
    Internal::moveCallback = callback;
}

void SetButtonCallback(ButtonCallback callback) {
    Internal::buttonCallback = callback;
}

void SetScrollCallback(ScrollCallback callback) {
    Internal::scrollCallback = callback;
}

void Click(Button button) {
    Down(button);
    Up(button);
}

}  // namespace Mouse
}  // namespace Macro
