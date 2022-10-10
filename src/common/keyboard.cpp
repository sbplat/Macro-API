#include <macro/keyboard.h>

#include "../internal.h"
#include "../platform.h"

namespace Macro {
namespace Keyboard {

std::string GetKeyName(Key key) {
    int vkCode = MapToOSKey(key);
    char buffer[256];
    int scanCode = MapVirtualKey(vkCode, MAPVK_VK_TO_VSC);
    int result = GetKeyNameTextA(scanCode << 16, buffer, 256);
    return result > 0 ? std::string(buffer) : "Unknown";
}

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
