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
        vkCode = key - Key::BACKSPACE + VK_BACK;
    } else if (key >= CLEAR && key <= ENTER) {
        vkCode = key - Key::CLEAR + VK_CLEAR;
    } else if (key >= PAUSE && key <= CAPS_LOCK) {
        vkCode = key - Key::PAUSE + VK_PAUSE;
    } else if (key >= ESCAPE && key <= ESCAPE) {
        vkCode = key - Key::ESCAPE + VK_ESCAPE;
    } else if (key >= SPACE && key <= SELECT) {
        vkCode = key - Key::SPACE + VK_SPACE;
    } else if (key >= EXECUTE && key <= HELP) {
        vkCode = key - Key::EXECUTE + VK_EXECUTE;
    } else if (key >= ZERO && key <= NINE) {
        vkCode = key - Key::ZERO + VK_KEY_0;
    } else if (key >= A && key <= Z) {
        vkCode = key - Key::A + VK_KEY_A;
    } else if (key >= NUMPAD0 && key <= NUMPAD9) {
        vkCode = key - Key::NUMPAD0 + VK_NUMPAD0;
    } else if (key >= MULTIPLY && key <= DIVIDE) {
        vkCode = key - Key::MULTIPLY + VK_MULTIPLY;
    } else if (key >= F1 && key <= F12) {
        vkCode = key - Key::F1 + VK_F1;
    } else if (key >= NUM_LOCK && key <= SCROLL_LOCK) {
        vkCode = key - Key::NUM_LOCK + VK_NUMLOCK;
    } else if (key >= LSHIFT && key <= RALT) {
        vkCode = key - Key::LSHIFT + VK_LSHIFT;
    } else if (key >= LSUPER && key <= MENU) {
        vkCode = key - Key::LSUPER + VK_LWIN;
    } else if (key >= COLON && key <= TILDE) {
        vkCode = key - Key::COLON + VK_OEM_1;
    } else if (key >= LEFT_BRACKET && key <= QUOTE) {
        vkCode = key - Key::LEFT_BRACKET + VK_OEM_4;
    } else {
        throw std::runtime_error("Unrecognized key (MapToOSKey): " + std::to_string(key));
    }

    return vkCode;
}

Key MapFromOSKey(int osKey) {
    Key key;

    if (osKey >= VK_BACK && osKey <= VK_TAB) {
        key = static_cast<Key>(osKey - VK_BACK + Key::BACKSPACE);
    } else if (osKey >= VK_CLEAR && osKey <= VK_RETURN) {
        key = static_cast<Key>(osKey - VK_CLEAR + Key::CLEAR);
    } else if (osKey >= VK_PAUSE && osKey <= VK_CAPITAL) {
        key = static_cast<Key>(osKey - VK_PAUSE + Key::PAUSE);
    } else if (osKey >= VK_ESCAPE && osKey <= VK_ESCAPE) {
        key = static_cast<Key>(osKey - VK_ESCAPE + Key::ESCAPE);
    } else if (osKey >= VK_SPACE && osKey <= VK_SELECT) {
        key = static_cast<Key>(osKey - VK_SPACE + Key::SPACE);
    } else if (osKey >= VK_EXECUTE && osKey <= VK_HELP) {
        key = static_cast<Key>(osKey - VK_EXECUTE + Key::EXECUTE);
    } else if (osKey >= VK_KEY_0 && osKey <= VK_KEY_9) {
        key = static_cast<Key>(osKey - VK_KEY_0 + Key::ZERO);
    } else if (osKey >= VK_KEY_A && osKey <= VK_KEY_Z) {
        key = static_cast<Key>(osKey - VK_KEY_A + Key::A);
    } else if (osKey >= VK_NUMPAD0 && osKey <= VK_NUMPAD9) {
        key = static_cast<Key>(osKey - VK_NUMPAD0 + Key::NUMPAD0);
    } else if (osKey >= VK_MULTIPLY && osKey <= VK_DIVIDE) {
        key = static_cast<Key>(osKey - VK_MULTIPLY + Key::MULTIPLY);
    } else if (osKey >= VK_F1 && osKey <= VK_F12) {
        key = static_cast<Key>(osKey - VK_F1 + Key::F1);
    } else if (osKey >= VK_NUMLOCK && osKey <= VK_SCROLL) {
        key = static_cast<Key>(osKey - VK_NUMLOCK + Key::NUM_LOCK);
    } else if (osKey >= VK_LSHIFT && osKey <= VK_RMENU) {
        key = static_cast<Key>(osKey - VK_LSHIFT + Key::LSHIFT);
    } else if (osKey >= VK_LWIN && osKey <= VK_APPS) {
        key = static_cast<Key>(osKey - VK_LWIN + Key::LSUPER);
    } else if (osKey >= VK_OEM_1 && osKey <= VK_OEM_3) {
        key = static_cast<Key>(osKey - VK_OEM_1 + Key::COLON);
    } else if (osKey >= VK_OEM_4 && osKey <= VK_OEM_7) {
        key = static_cast<Key>(osKey - VK_OEM_4 + Key::LEFT_BRACKET);
    } else {
        throw std::runtime_error("Unrecognized key (MapFromOSKey): " + std::to_string(osKey));
    }

    return key;
}

}  // namespace Keyboard
}  // namespace Macro
