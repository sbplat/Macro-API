#include <macro/keyboard.h>

#include "../platform.h"

#include <stdexcept>

namespace Macro {
namespace Keyboard {

Combo MapFromChar(char c) {
    SHORT result = VkKeyScanA(c);
    int vkCode = result & 0xFF, shift = result >> 8;
    Key key = MapFromOSKey(vkCode);
    return Combo{key, static_cast<bool>(shift & 0x1), static_cast<bool>(shift & 0x2),
                 static_cast<bool>(shift & 0x4)};
}

void Down(Key key) {
    INPUT input = {0};
    input.type = INPUT_KEYBOARD;
    input.ki.wVk = MapToOSKey(key);
    SendInput(1, &input, sizeof(INPUT));
}

void Up(Key key) {
    INPUT input = {0};
    input.type = INPUT_KEYBOARD;
    input.ki.wVk = MapToOSKey(key);
    input.ki.dwFlags = KEYEVENTF_KEYUP;
    SendInput(1, &input, sizeof(INPUT));
}

}  // namespace Keyboard
}  // namespace Macro
