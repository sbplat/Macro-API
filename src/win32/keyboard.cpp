#include <macro/keyboard.h>

#include "../platform.h"

#include <stdexcept>

namespace Macro {
namespace Keyboard {

int MapToOSKey(Key key) {
    if (key >= BACKSPACE && key <= TAB) {
        return key - BACKSPACE + 0x08;
    } else if (key >= ENTER && key <= ENTER) {
        return key - ENTER + 0x0D;
    } else if (key >= SHIFT && key <= CAPS_LOCK) {
        return key - SHIFT + 0x10;
    } else if (key >= ESCAPE && key <= ESCAPE) {
        return key - ESCAPE + 0x1B;
    } else if (key >= SPACE && key <= HELP) {
        return key - SPACE + 0x20;
    } else if (key >= ZERO && key <= NINE) {
        return key - ZERO + 0x30;
    } else if (key >= A && key <= Z) {
        return key - A + 0x41;
    } else if (key >= NUM0 && key <= NUM9) {
        return key - NUM0 + 0x60;
    } else if (key >= NUMPAD0 && key <= NUMPAD9) {
        return key - NUMPAD0 + 0x60;
    } else if (key >= MULTIPLY && key <= DIVIDE) {
        return key - MULTIPLY + 0x6A;
    } else if (key >= F1 && key <= F12) {
        return key - F1 + 0x70;
    } else if (key >= LSHIFT && key <= RALT) {
        return key - LSHIFT + 0xA0;
    } else if (key >= LSUPER && key <= RSUPER) {
        return key - LSUPER + 0x5B;
    } else if (key >= COLON && key <= TILDE) {
        return key - COLON + 0xBA;
    } else if (key >= LEFT_BRACKET && key <= OEM_8) {
        return key - LEFT_BRACKET + 0xDB;
    } else if (key >= OEM_102 && key <= OEM_102) {
        return key - OEM_102 + 0xE2;
    } else {
        throw std::runtime_error(std::string("Unrecognized key: ") + std::to_string(key));
    }
}

#ifndef VK_KEY_0
#define VK_KEY_0 0x30
#endif // VK_KEY_0
#ifndef VK_KEY_9
#define VK_KEY_9 0x39
#endif // VK_KEY_9

#ifndef VK_KEY_A
#define VK_KEY_A 0x41
#endif // VK_KEY_A
#ifndef VK_KEY_Z
#define VK_KEY_Z 0x5A
#endif // VK_KEY_Z

Key OSKeyToKey(int osKey) {
    Key key;
    if (osKey >= VK_KEY_0 && osKey <= VK_KEY_9) {
        key = static_cast<Key>(osKey - VK_KEY_0 + ZERO);
    } else if (osKey >= VK_KEY_A && osKey <= VK_KEY_Z) {
        key = static_cast<Key>(osKey - VK_KEY_A + A);
    } else if (osKey == VK_SPACE) {
        key = SPACE;
    } else if (osKey == VK_OEM_3) {
        key = TILDE;
    } else if (osKey == VK_OEM_MINUS) {
        key = MINUS;
    } else if (osKey == VK_OEM_PLUS) {
        key = PLUS;
    } else if (osKey == VK_OEM_4) {
        key = LEFT_BRACKET;
    } else if (osKey == VK_OEM_6) {
        key = RIGHT_BRACKET;
    } else if (osKey == VK_OEM_5) {
        key = BACKSLASH;
    } else if (osKey == VK_OEM_1) {
        key = COLON;
    } else if (osKey == VK_OEM_7) {
        key = QUOTE;
    } else if (osKey == VK_OEM_COMMA) {
        key = COMMA;
    } else if (osKey == VK_OEM_PERIOD) {
        key = PERIOD;
    } else if (osKey == VK_OEM_2) {
        key = SLASH;
    } else {
        throw std::runtime_error(std::string("Unsupported osKey: ") + std::to_string(osKey));
    }
    return key;
}

Combo MapFromChar(char c) {
    short result = VkKeyScanA(c);
    int vkCode = result & 0xFF, shift = result >> 8;
    Key key = OSKeyToKey(vkCode);
    return Combo{key, static_cast<bool>(shift & 0x1), static_cast<bool>(shift & 0x2), static_cast<bool>(shift & 0x4)};
}

State GetState() {
    State state;
    // todo fill
    return state;
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
