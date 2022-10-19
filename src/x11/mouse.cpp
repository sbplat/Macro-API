#include <macro/mouse.h>

#include "../internal.h"
#include "../platform.h"

namespace Macro {
namespace Mouse {

Point GetPosition() {
    Window root_window = DefaultRootWindow(ctx.GetDisplay()), child_window;
    Point root_pt, win_pt;
    unsigned int mask;
    XQueryPointer(ctx.GetDisplay(), root_window, &root_window, &child_window, &root_pt.x,
                  &root_pt.y, &win_pt.x, &win_pt.y, &mask);
    return root_pt;
}

void MoveAbsolute(int x, int y) {
    int screen = -1;  // The screen that the pointer is on
    XTestFakeMotionEvent(ctx.GetDisplay(), screen, x, y, CurrentTime);
    XFlush(ctx.GetDisplay());
}

void MoveRelative(int x, int y) {
    XTestFakeRelativeMotionEvent(ctx.GetDisplay(), x, y, CurrentTime);
    XFlush(ctx.GetDisplay());
}

static int ButtonToX11ButtonCode(Button button) {
    int buttonCode = 0;

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

    return buttonCode;
}

void Down(Button button) {
    int buttonCode = ButtonToX11ButtonCode(button);
    XTestFakeButtonEvent(ctx.GetDisplay(), buttonCode, true, CurrentTime);
    XFlush(ctx.GetDisplay());
}

void Up(Button button) {
    int buttonCode = ButtonToX11ButtonCode(button);
    XTestFakeButtonEvent(ctx.GetDisplay(), buttonCode, false, CurrentTime);
    XFlush(ctx.GetDisplay());
}

void Scroll(int delta, bool horizontal) {
    int absoluteDelta = std::abs(delta);
    int button;
    if (horizontal) {
        button = delta > 0 ? 7 : 6;
    } else {
        button = delta > 0 ? 4 : 5;
    }
    for (int i = 0; i < absoluteDelta; i++) {
        XTestFakeButtonEvent(ctx.GetDisplay(), button, true, CurrentTime);
        XSync(ctx.GetDisplay(), false);
        XTestFakeButtonEvent(ctx.GetDisplay(), button, false, CurrentTime);
        XFlush(ctx.GetDisplay());
    }
}

}  // namespace Mouse
}  // namespace Macro
