#include <macro/keyboard.h>

#include <stdexcept>

#include "../platform.h"

namespace Macro {
namespace Keyboard {

LRESULT CALLBACK LowLevelKeyboardProc(int nCode, WPARAM wParam, LPARAM lParam) {
    KBDLLHOOKSTRUCT *key = reinterpret_cast<KBDLLHOOKSTRUCT *>(lParam);

    // Ignore injected events.
    if (nCode >= 0 && !(key->flags & LLKHF_INJECTED)) {
        KeyState state = (wParam == WM_KEYDOWN || wParam == WM_SYSKEYDOWN) ? KeyState::DOWN : KeyState::UP;

        if (Internal::keyCallback != nullptr) {
            bool shouldBlock = Internal::keyCallback(MapFromOSKey(key->vkCode), state);
            if (shouldBlock) {
                return 1;
            }
        }
    }

    return CallNextHookEx(NULL, nCode, wParam, lParam);
}

void KeyboardHookLoop() {
    HHOOK keyboardHook = SetWindowsHookEx(WH_KEYBOARD_LL, LowLevelKeyboardProc, GetModuleHandle(NULL), 0);

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
