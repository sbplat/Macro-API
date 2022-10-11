#include <macro/keyboard.h>

#include "../internal.h"
#include "../platform.h"

namespace Macro {
namespace Keyboard {

namespace Internal {

KeyCallback keyCallback = nullptr;

} // Internal

void SetCallback(KeyCallback callback) {
    Internal::keyCallback = callback;
}

void Tap(Key key) {
    Down(key);
    Up(key);
}

void Type(const std::string& text) {
    for (char c : text) {
        Combo combo = MapFromChar(c);
        if (combo.shift) {
            Down(SHIFT);
        }
        if (combo.alt) {
            Down(ALT);
        }
        if (combo.ctrl) {
            Down(CTRL);
        }
        Tap(combo.key);
        if (combo.shift) {
            Up(SHIFT);
        }
        if (combo.alt) {
            Up(ALT);
        }
        if (combo.ctrl) {
            Up(CTRL);
        }
    }
}

}  // namespace Keyboard
}  // namespace Macro
