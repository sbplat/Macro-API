#include <macro/mouse.h>

#include "../platform.h"

namespace Macro {
namespace Mouse {

Point GetPosition() {
    Display *display = XOpenDisplay(NULL);
    Window root_window = DefaultRootWindow(display), child;
    Point root, win;
    unsigned int mask;
    XQueryPointer(display, root_window, &root_window, &child, &root.x, &root.y, &win.x, &win.y,
                  &mask);
    XCloseDisplay(display);
    return root;
}

void MoveAbsolute(int x, int y) {
    Display *display = XOpenDisplay(NULL);
    int screen = DefaultScreen(display);
    XTestFakeMotionEvent(display, screen, x, y, 0);
    XCloseDisplay(display);
}

void MoveRelative(int x, int y) {
    Display *display = XOpenDisplay(NULL);
    XTestFakeRelativeMotionEvent(display, x, y, 0);
    XCloseDisplay(display);
}

void Down(Button button) {
    Display *display = XOpenDisplay(NULL);
    int buttonCode;
    switch (button) {
        case LEFT:
            buttonCode = 1;
            break;
        case RIGHT:
            buttonCode = 3;
            break;
        case MIDDLE:
            buttonCode = 2;
            break;
        case X1:
            buttonCode = 8;
            break;
        case X2:
            buttonCode = 9;
            break;
    }
    XTestFakeButtonEvent(display, buttonCode, True, 0);
    XCloseDisplay(display);
}

void Up(Button button) {
    Display *display = XOpenDisplay(NULL);
    int buttonCode;
    switch (button) {
        case LEFT:
            buttonCode = 1;
            break;
        case RIGHT:
            buttonCode = 3;
            break;
        case MIDDLE:
            buttonCode = 2;
            break;
        case X1:
            buttonCode = 8;
            break;
        case X2:
            buttonCode = 9;
            break;
    }
    XTestFakeButtonEvent(display, buttonCode, False, 0);
    XCloseDisplay(display);
}

void Scroll(int delta, bool horizontal) {
    Display *display = XOpenDisplay(NULL);
    int absoluteDelta = abs(delta);
    int button;
    if (horizontal) {
        button = delta > 0 ? 7 : 6;
    } else {
        button = delta > 0 ? 4 : 5;
    }
    for (int i = 0; i < absoluteDelta; i++) {
        XTestFakeButtonEvent(display, button, True, 0);
        XTestFakeButtonEvent(display, button, False, 0);
    }
    XCloseDisplay(display);
}

}  // namespace Mouse
}  // namespace Macro
