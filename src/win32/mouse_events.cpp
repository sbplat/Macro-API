#include <macro/mouse.h>

#include "../internal.h"
#include "../platform.h"

#include <stdexcept>
#include <string>

namespace Macro {
namespace Mouse {

Point MapToVirtualScreen(const Point &point) {
#if NTDDI_VERSION >= NTDDI_WINBLUE
    POINT pt = {point.x, point.y};

    // Get the monitor that the cursor is on.
    HMONITOR monitor = MonitorFromPoint(pt, MONITOR_DEFAULTTONEAREST);

    // Obtain the scale factor for the monitor.
    DEVICE_SCALE_FACTOR scale_factor;
    GetScaleFactorForMonitor(monitor, &scale_factor);

    // Convert to virtual screen pixels using the DPI of the monitor.
    return {MulDiv(pt.x, 100, scale_factor), MulDiv(pt.y, 100, scale_factor)};
#else
    // Early versions of Windows don't support per-monitor DPI awareness.
    // We'll just assume 100% scaling.
    return point;
#endif
}

LRESULT CALLBACK LowLevelMouseProc(int nCode, WPARAM wParam, LPARAM lParam) {
    MSLLHOOKSTRUCT *mouse = reinterpret_cast<MSLLHOOKSTRUCT *>(lParam);

    // Ignore injected events.
    if (nCode >= 0 && !(mouse->flags & LLMHF_INJECTED)) {
        bool shouldBlock = false;

        if (wParam == WM_MOUSEMOVE) {
            Point point = MapToVirtualScreen({mouse->pt.x, mouse->pt.y});

            if (Internal::MoveCb(point)) {
                return 1;
            }

            if (Internal::moveCallback != nullptr) {
                shouldBlock = Internal::moveCallback(point);
            }
        } else if (wParam == WM_MOUSEWHEEL || wParam == WM_MOUSEHWHEEL) {
            int delta = GET_WHEEL_DELTA_WPARAM(mouse->mouseData);
            bool isHorizontal = (wParam == WM_MOUSEHWHEEL);

            if (Internal::ScrollCb(delta, isHorizontal)) {
                return 1;
            }

            if (Internal::scrollCallback != nullptr) {
                shouldBlock = Internal::scrollCallback(delta, isHorizontal);
            }
        } else {
            ButtonState state = (wParam == WM_LBUTTONDOWN || wParam == WM_RBUTTONDOWN ||
                                 wParam == WM_MBUTTONDOWN || wParam == WM_XBUTTONDOWN)
                                    ? ButtonState::DOWN
                                    : ButtonState::UP;
            Button button;

            if (wParam == WM_LBUTTONDOWN || wParam == WM_LBUTTONUP) {
                button = Button::LEFT;
            } else if (wParam == WM_RBUTTONDOWN || wParam == WM_RBUTTONUP) {
                button = Button::RIGHT;
            } else if (wParam == WM_MBUTTONDOWN || wParam == WM_MBUTTONUP) {
                button = Button::MIDDLE;
            } else if (wParam == WM_XBUTTONDOWN || wParam == WM_XBUTTONUP) {
                button =
                    (GET_XBUTTON_WPARAM(mouse->mouseData) == XBUTTON1) ? Button::X1 : Button::X2;
            } else {
                throw std::runtime_error("Unknown mouse button (LowLevelMouseProc): " +
                                         std::to_string(wParam));
            }

            if (Internal::ButtonCb(button, state)) {
                return 1;
            }

            if (Internal::buttonCallback != nullptr) {
                shouldBlock = Internal::buttonCallback(button, state);
            }
        }

        if (shouldBlock) {
            return 1;
        }
    }

    return CallNextHookEx(NULL, nCode, wParam, lParam);
}

void MouseHookLoop() {
    HHOOK mouseHook = SetWindowsHookEx(WH_MOUSE_LL, LowLevelMouseProc, GetModuleHandle(NULL), 0);

    if (mouseHook == NULL) {
        throw std::runtime_error("Failed to set mouse hook");
    }

    MSG msg;

    while (GetMessage(&msg, NULL, 0, 0) != 0) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    UnhookWindowsHookEx(mouseHook);
}

}  // namespace Mouse
}  // namespace Macro
