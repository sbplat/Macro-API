#include <macro/keyboard.h>

#include "../internal.h"
#include "../platform.h"

namespace Macro {
namespace Keyboard {

namespace Internal {

bool KeyCb(Key key, KeyState state) {
    Internal::keyStates[key] = state;

    return false;
}

KeyStates keyStates(KeyState::UP);

KeyCallback keyCallback = nullptr;

}  // namespace Internal

void SetCallback(KeyCallback callback) { Internal::keyCallback = callback; }

const KeyStates &GetKeyStates() { return Internal::keyStates; }

KeyState GetKeyState(Key key) {
    return Internal::keyStates[key];
}

void Tap(Key key, int ms) {
    Down(key);
    Misc::Sleep(ms);
    Up(key);
}

void Type(const std::string &text, int ms) {
    for (size_t i = 0; i < text.size(); ++i) {
        Combo combo = MapFromChar(text[i]);
        if (combo.shift) {
            Down(LSHIFT);
        }
        if (combo.alt) {
            Down(LALT);
        }
        if (combo.ctrl) {
            Down(LCTRL);
        }
        Tap(combo.key, ms);
        if (combo.shift) {
            Up(LSHIFT);
        }
        if (combo.alt) {
            Up(LALT);
        }
        if (combo.ctrl) {
            Up(LCTRL);
        }
        if (i != text.size() - 1) {
            Misc::Sleep(ms);
        }
    }
}

}  // namespace Keyboard
}  // namespace Macro
