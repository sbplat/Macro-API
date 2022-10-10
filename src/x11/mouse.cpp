#include <macro/mouse.h>

#include "../platform.h"

#include <vector>

namespace Macro {
namespace Mouse {

Point GetPosition() {

}

ButtonStateMap GetButtonStates() {
    ButtonStateMap buttonStates;
    // todo fill
    return buttonStates;
}

void MoveAbsolute(int x, int y) {
    // (0, 0) is the top left corner
    // (65535, 65535) is the bottom right corner

}

void MoveRelative(int x, int y) {

}

void Down(Button button) {

}

void Up(Button button) {

}

void Scroll(int delta, bool horizontal) {

}

}  // namespace Mouse
}  // namespace Macro
