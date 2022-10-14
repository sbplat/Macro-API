#include <macro/keyboard.h>

#include "../platform.h"

#include <stdexcept>

namespace Macro {
namespace Keyboard {

#ifndef VK_KEY_0
#define VK_KEY_0 0x30
#endif  // VK_KEY_0
#ifndef VK_KEY_9
#define VK_KEY_9 0x39
#endif  // VK_KEY_9

#ifndef VK_KEY_A
#define VK_KEY_A 0x41
#endif  // VK_KEY_A
#ifndef VK_KEY_Z
#define VK_KEY_Z 0x5A
#endif  // VK_KEY_Z

int MapToOSKey(Key key) {
    int vkCode;

    if (key >= BACKSPACE && key <= TAB) {
        vkCode = key - BACKSPACE + VK_BACK;
    } else if (key >= CLEAR && key <= ENTER) {
        vkCode = key - CLEAR + VK_CLEAR;
    } else if (key >= SHIFT && key <= CAPS_LOCK) {
        vkCode = key - SHIFT + VK_SHIFT;
    } else if (key >= ESCAPE && key <= ESCAPE) {
        vkCode = key - ESCAPE + VK_ESCAPE;
    } else if (key >= SPACE && key <= HELP) {
        vkCode = key - SPACE + VK_SPACE;
    } else if (key >= ZERO && key <= NINE) {
        vkCode = key - ZERO + VK_KEY_0;
    } else if (key >= A && key <= Z) {
        vkCode = key - A + VK_KEY_A;
    } else if (key >= NUMPAD0 && key <= NUMPAD9) {
        vkCode = key - NUMPAD0 + VK_NUMPAD0;
    } else if (key >= MULTIPLY && key <= DIVIDE) {
        vkCode = key - MULTIPLY + VK_MULTIPLY;
    } else if (key >= F1 && key <= F12) {
        vkCode = key - F1 + VK_F1;
    } else if (key >= NUM_LOCK && key <= SCROLL_LOCK) {
        vkCode = key - NUM_LOCK + VK_NUMLOCK;
    } else if (key >= LSHIFT && key <= RALT) {
        vkCode = key - LSHIFT + VK_LSHIFT;
    } else if (key >= LSUPER && key <= MENU) {
        vkCode = key - LSUPER + VK_LWIN;
    } else if (key >= COLON && key <= TILDE) {
        vkCode = key - COLON + VK_OEM_1;
    } else if (key >= LEFT_BRACKET && key <= OEM_8) {
        vkCode = key - LEFT_BRACKET + VK_OEM_4;
    } else if (key >= OEM_102 && key <= OEM_102) {
        vkCode = key - OEM_102 + VK_OEM_102;
    } else {
        throw std::runtime_error(std::string("Unrecognized key (MapToOSKey): ") + std::to_string(key));
    }

    return vkCode;
}

Key MapFromOSKey(int osKey) {
    Key key;

    if (osKey >= VK_BACK && osKey <= VK_TAB) {
        key = static_cast<Key>(osKey - VK_BACK + BACKSPACE);
    } else if (osKey >= VK_CLEAR && osKey <= VK_RETURN) {
        key = static_cast<Key>(osKey - VK_CLEAR + CLEAR);
    } else if (osKey >= VK_SHIFT && osKey <= VK_CAPITAL) {
        key = static_cast<Key>(osKey - VK_SHIFT + SHIFT);
    } else if (osKey >= VK_ESCAPE && osKey <= VK_ESCAPE) {
        key = static_cast<Key>(osKey - VK_ESCAPE + ESCAPE);
    } else if (osKey >= VK_SPACE && osKey <= VK_HELP) {
        key = static_cast<Key>(osKey - VK_SPACE + SPACE);
    } else if (osKey >= VK_KEY_0 && osKey <= VK_KEY_9) {
        key = static_cast<Key>(osKey - VK_KEY_0 + ZERO);
    } else if (osKey >= VK_KEY_A && osKey <= VK_KEY_Z) {
        key = static_cast<Key>(osKey - VK_KEY_A + A);
    } else if (osKey >= VK_NUMPAD0 && osKey <= VK_NUMPAD9) {
        key = static_cast<Key>(osKey - VK_NUMPAD0 + NUMPAD0);
    } else if (osKey >= VK_MULTIPLY && osKey <= VK_DIVIDE) {
        key = static_cast<Key>(osKey - VK_MULTIPLY + MULTIPLY);
    } else if (osKey >= VK_F1 && osKey <= VK_F12) {
        key = static_cast<Key>(osKey - VK_F1 + F1);
    } else if (osKey >= VK_NUMLOCK && osKey <= VK_SCROLL) {
        key = static_cast<Key>(osKey - VK_NUMLOCK + NUM_LOCK);
    } else if (osKey >= VK_LSHIFT && osKey <= VK_RMENU) {
        key = static_cast<Key>(osKey - VK_LSHIFT + LSHIFT);
    } else if (osKey >= VK_LWIN && osKey <= VK_APPS) {
        key = static_cast<Key>(osKey - VK_LWIN + LSUPER);
    } else if (osKey >= VK_OEM_1 && osKey <= VK_OEM_3) {
        key = static_cast<Key>(osKey - VK_OEM_1 + COLON);
    } else if (osKey >= VK_OEM_4 && osKey <= VK_OEM_8) {
        key = static_cast<Key>(osKey - VK_OEM_4 + LEFT_BRACKET);
    } else if (osKey >= VK_OEM_102 && osKey <= VK_OEM_102) {
        key = static_cast<Key>(osKey - VK_OEM_102 + OEM_102);
    } else {
        throw std::runtime_error(std::string("Unrecognized key (MapFromOSKey): ") + std::to_string(osKey));
    }

    return key;
}

Combo MapFromChar(char c) {
    short result = VkKeyScanA(c);
    int vkCode = result & 0xFF, shift = result >> 8;
    Key key = MapFromOSKey(vkCode);
    return Combo{key, static_cast<bool>(shift & 0x1), static_cast<bool>(shift & 0x2), static_cast<bool>(shift & 0x4)};
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
