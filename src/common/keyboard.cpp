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

KeyStateMap keyStates;

KeyCallback keyCallback = nullptr;

}  // namespace Internal

void SetCallback(KeyCallback callback) { Internal::keyCallback = callback; }

const KeyStateMap &GetKeyStates() { return Internal::keyStates; }

void Tap(Key key, int ms) {
    Down(key);
    Misc::Sleep(ms);
    Up(key);
}

void Type(const std::string &text, int ms) {
    for (size_t i = 0; i < text.size(); ++i) {
        Combo combo = MapFromChar(text[i]);
        if (combo.shift) {
            Down(SHIFT);
        }
        if (combo.alt) {
            Down(ALT);
        }
        if (combo.ctrl) {
            Down(CTRL);
        }
        Tap(combo.key, ms);
        if (combo.shift) {
            Up(SHIFT);
        }
        if (combo.alt) {
            Up(ALT);
        }
        if (combo.ctrl) {
            Up(CTRL);
        }
        if (i != text.size() - 1) {
            Misc::Sleep(ms);
        }
    }
}

}  // namespace Keyboard
}  // namespace Macro
