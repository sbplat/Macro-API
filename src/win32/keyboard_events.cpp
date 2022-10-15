#include <macro/keyboard.h>

#include "../internal.h"
#include "../platform.h"

#include <stdexcept>

namespace Macro {
namespace Keyboard {

LRESULT CALLBACK LowLevelKeyboardProc(int nCode, WPARAM wParam, LPARAM lParam) {
    KBDLLHOOKSTRUCT *keyboard = reinterpret_cast<KBDLLHOOKSTRUCT *>(lParam);

    // Ignore injected events.
    if (nCode >= 0 && !(keyboard->flags & LLKHF_INJECTED)) {
        KeyState state =
            (wParam == WM_KEYDOWN || wParam == WM_SYSKEYDOWN) ? KeyState::DOWN : KeyState::UP;

        Key key = MapFromOSKey(keyboard->vkCode);

        if (Internal::KeyCb(key, state)) {
            return 1;
        }

        if (Internal::keyCallback != nullptr) {
            bool shouldBlock = Internal::keyCallback(key, state);

            if (shouldBlock) {
                return 1;
            }
        }
    }

    return CallNextHookEx(NULL, nCode, wParam, lParam);
}

void KeyboardHookLoop() {
    HHOOK keyboardHook =
        SetWindowsHookEx(WH_KEYBOARD_LL, LowLevelKeyboardProc, GetModuleHandle(NULL), 0);

    if (keyboardHook == NULL) {
        throw std::runtime_error("Failed to set keyboard hook");
    }

    MSG msg;

    while (GetMessage(&msg, NULL, 0, 0) != 0) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    UnhookWindowsHookEx(keyboardHook);
}

}  // namespace Keyboard
}  // namespace Macro
