#include <macro/mouse.h>

#include "../internal.h"
#include "../platform.h"

#include <stdexcept>

namespace Macro {
namespace Mouse {

std::string GetButtonName(Button button) {
    // clang-format off
    switch (button) {
        case LEFT: return "Left";
        case RIGHT: return "Right";
        case MIDDLE: return "Middle";
        case X1: return "X1";
        case X2: return "X2";
        default: throw std::runtime_error("Unknown button (GetButtonName): " + std::to_string(button));
    }
    // clang-format on
}

namespace Internal {

bool ButtonCb(Button button, ButtonState state) {
    Internal::buttonStates[button] = state;

    return false;
}

ButtonStateMap buttonStates;

MoveCallback moveCallback = nullptr;
ButtonCallback buttonCallback = nullptr;
ScrollCallback scrollCallback = nullptr;

}  // namespace Internal

void SetMoveCallback(MoveCallback callback) { Internal::moveCallback = callback; }

void SetButtonCallback(ButtonCallback callback) { Internal::buttonCallback = callback; }

void SetScrollCallback(ScrollCallback callback) { Internal::scrollCallback = callback; }

const ButtonStateMap &GetButtonStates() { return Internal::buttonStates; }

void Click(Button button) {
    Down(button);
    Up(button);
}

}  // namespace Mouse
}  // namespace Macro
