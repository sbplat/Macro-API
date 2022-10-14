#include <macro/mouse.h>

#include <stdexcept>
#include <string>

#include "../platform.h"

namespace Macro {
namespace Mouse {

LRESULT CALLBACK LowLevelMouseProc(int nCode, WPARAM wParam, LPARAM lParam) {
    MSLLHOOKSTRUCT *mouse = reinterpret_cast<MSLLHOOKSTRUCT *>(lParam);

    // Ignore injected events.
    if (nCode >= 0 && !(mouse->flags & LLMHF_INJECTED)) {
        bool shouldBlock = false;

        if (wParam == WM_MOUSEMOVE) {
            if (Internal::moveCallback != nullptr) {
                shouldBlock = Internal::moveCallback({mouse->pt.x, mouse->pt.y});
            }
        } else if (wParam == WM_MOUSEWHEEL || wParam == WM_MOUSEHWHEEL) {
            if (Internal::scrollCallback != nullptr) {
                shouldBlock = Internal::scrollCallback(GET_WHEEL_DELTA_WPARAM(mouse->mouseData));
            }
        } else {
            State state = (wParam == WM_LBUTTONDOWN || wParam == WM_RBUTTONDOWN || wParam == WM_MBUTTONDOWN || wParam == WM_XBUTTONDOWN) ? State::DOWN : State::UP;
            Button button;

            if (wParam == WM_LBUTTONDOWN || wParam == WM_LBUTTONUP) {
                button = Button::LEFT;
            } else if (wParam == WM_RBUTTONDOWN || wParam == WM_RBUTTONUP) {
                button = Button::RIGHT;
            } else if (wParam == WM_MBUTTONDOWN || wParam == WM_MBUTTONUP) {
                button = Button::MIDDLE;
            } else if (wParam == WM_XBUTTONDOWN || wParam == WM_XBUTTONUP) {
                button = (GET_XBUTTON_WPARAM(mouse->mouseData) == XBUTTON1) ? Button::X1 : Button::X2;
            } else {
                throw std::runtime_error("Unknown mouse button (LowLevelMouseProc): " + std::to_string(wParam));
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

} // namespace Mouse
} // namespace Macro
