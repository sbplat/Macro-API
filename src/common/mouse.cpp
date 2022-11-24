#include <macro/mouse.h>

#include "../internal.h"
#include "../platform.h"

#include <stdexcept>

namespace Macro {
namespace Mouse {

std::string GetButtonName(Button button) {
    // clang-format off
    switch (button) {
        case LEFT: return "LEFT";
        case RIGHT: return "RIGHT";
        case MIDDLE: return "MIDDLE";
        case X1: return "X1";
        case X2: return "X2";
        default: throw std::runtime_error("Unknown button (GetButtonName): " + std::to_string(button));
    }
    // clang-format on
}

namespace Internal {

ButtonStates buttonStates(ButtonState::UP);

bool MoveCb(Point position) {
    // Reserved for future use.
    (void)position;

    return false;
}

bool ButtonCb(Button button, ButtonState state) {
    Internal::buttonStates[button] = state;

    return false;
}

bool ScrollCb(int delta, bool isHorizontal) {
    // Reserved for future use.
    (void)delta;
    (void)isHorizontal;

    return false;
}

MoveCallback moveCallback = nullptr;
ButtonCallback buttonCallback = nullptr;
ScrollCallback scrollCallback = nullptr;

}  // namespace Internal

void SetMoveCallback(MoveCallback callback) { Internal::moveCallback = callback; }

void SetButtonCallback(ButtonCallback callback) { Internal::buttonCallback = callback; }

void SetScrollCallback(ScrollCallback callback) { Internal::scrollCallback = callback; }

ButtonState GetButtonState(Button button) { return Internal::buttonStates[button]; }

const ButtonStates &GetButtonStates() { return Internal::buttonStates; }

void Click(Button button, int ms) {
    Down(button);
    Misc::Sleep(ms);
    Up(button);
}

}  // namespace Mouse
}  // namespace Macro
