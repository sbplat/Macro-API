#include <macro/mouse.h>

#include "../platform.h"

#include <vector>

namespace Macro {
namespace Mouse {

Point GetPosition() {
    POINT point = {0};
    GetCursorPos(&point);
    return {point.x, point.y};
}

void MoveAbsolute(int x, int y) {
    // (0, 0) is the top left corner
    // (65535, 65535) is the bottom right corner
    INPUT input = {0};
    input.type = INPUT_MOUSE;
    input.mi.dx = x;
    input.mi.dy = y;
    input.mi.dwFlags = MOUSEEVENTF_MOVE | MOUSEEVENTF_ABSOLUTE;
    SendInput(1, &input, sizeof(INPUT));
}

void MoveRelative(int x, int y) {
    INPUT input = {0};
    input.type = INPUT_MOUSE;
    input.mi.dx = x;
    input.mi.dy = y;
    input.mi.dwFlags = MOUSEEVENTF_MOVE;
    SendInput(1, &input, sizeof(INPUT));
}

void Down(Button button) {
    INPUT input = {0};
    input.type = INPUT_MOUSE;
    switch (button) {
        case LEFT:
            input.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
            break;
        case RIGHT:
            input.mi.dwFlags = MOUSEEVENTF_RIGHTDOWN;
            break;
        case MIDDLE:
            input.mi.dwFlags = MOUSEEVENTF_MIDDLEDOWN;
            break;
        case X1:
            input.mi.dwFlags = MOUSEEVENTF_XDOWN;
            input.mi.mouseData = XBUTTON1;
            break;
        case X2:
            input.mi.dwFlags = MOUSEEVENTF_XDOWN;
            input.mi.mouseData = XBUTTON2;
            break;
    }
    SendInput(1, &input, sizeof(INPUT));
}

void Up(Button button) {
    INPUT input = {0};
    input.type = INPUT_MOUSE;
    switch (button) {
        case LEFT:
            input.mi.dwFlags = MOUSEEVENTF_LEFTUP;
            break;
        case RIGHT:
            input.mi.dwFlags = MOUSEEVENTF_RIGHTUP;
            break;
        case MIDDLE:
            input.mi.dwFlags = MOUSEEVENTF_MIDDLEUP;
            break;
        case X1:
            input.mi.dwFlags = MOUSEEVENTF_XUP;
            input.mi.mouseData = XBUTTON1;
            break;
        case X2:
            input.mi.dwFlags = MOUSEEVENTF_XUP;
            input.mi.mouseData = XBUTTON2;
            break;
    }
    SendInput(1, &input, sizeof(INPUT));
}

void Scroll(int delta, bool horizontal) {
    INPUT input = {0};
    input.type = INPUT_MOUSE;
    input.mi.dwFlags = horizontal ? MOUSEEVENTF_HWHEEL : MOUSEEVENTF_WHEEL;
    input.mi.mouseData = delta;
    SendInput(1, &input, sizeof(INPUT));
}

}  // namespace Mouse
}  // namespace Macro
