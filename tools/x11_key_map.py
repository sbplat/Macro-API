key_map = [
    ("BACKSPACE", "XK_BackSpace"),
    ("TAB", "XK_Tab"),
    ("CLEAR", "XK_Clear"),
    ("ENTER", "XK_Return"),
    ("PAUSE", "XK_Pause"),
    ("CAPS_LOCK", "XK_Caps_Lock"),
    ("ESCAPE", "XK_Escape"),
    ("SPACE", "XK_space"),
    ("PAGE_UP", "XK_Page_Up"),
    ("PAGE_DOWN", "XK_Page_Down"),
    ("END", "XK_End"),
    ("HOME", "XK_Home"),
    ("LEFT_ARROW", "XK_Left"),
    ("UP_ARROW", "XK_Up"),
    ("RIGHT_ARROW", "XK_Right"),
    ("DOWN_ARROW", "XK_Down"),
    ("SELECT", "XK_Select"),
    ("EXECUTE", "XK_Execute"),
    ("PRINT_SCREEN", "XK_Print"),
    ("INSERT", "XK_Insert"),
    ("DELETE", "XK_Delete"),
    ("HELP", "XK_Help"),
    ("ZERO", "XK_0"),
    ("ONE", "XK_1"),
    ("TWO", "XK_2"),
    ("THREE", "XK_3"),
    ("FOUR", "XK_4"),
    ("FIVE", "XK_5"),
    ("SIX", "XK_6"),
    ("SEVEN", "XK_7"),
    ("EIGHT", "XK_8"),
    ("NINE", "XK_9"),
    ("A", "XK_A"),
    ("B", "XK_B"),
    ("C", "XK_C"),
    ("D", "XK_D"),
    ("E", "XK_E"),
    ("F", "XK_F"),
    ("G", "XK_G"),
    ("H", "XK_H"),
    ("I", "XK_I"),
    ("J", "XK_J"),
    ("K", "XK_K"),
    ("L", "XK_L"),
    ("M", "XK_M"),
    ("N", "XK_N"),
    ("O", "XK_O"),
    ("P", "XK_P"),
    ("Q", "XK_Q"),
    ("R", "XK_R"),
    ("S", "XK_S"),
    ("T", "XK_T"),
    ("U", "XK_U"),
    ("V", "XK_V"),
    ("W", "XK_W"),
    ("X", "XK_X"),
    ("Y", "XK_Y"),
    ("Z", "XK_Z"),
    ("NUMPAD0", "XK_KP_0"),
    ("NUMPAD1", "XK_KP_1"),
    ("NUMPAD2", "XK_KP_2"),
    ("NUMPAD3", "XK_KP_3"),
    ("NUMPAD4", "XK_KP_4"),
    ("NUMPAD5", "XK_KP_5"),
    ("NUMPAD6", "XK_KP_6"),
    ("NUMPAD7", "XK_KP_7"),
    ("NUMPAD8", "XK_KP_8"),
    ("NUMPAD9", "XK_KP_9"),
    ("MULTIPLY", "XK_KP_Multiply"),
    ("ADD", "XK_KP_Add"),
    ("SEPARATOR", "XK_KP_Separator"),
    ("SUBTRACT", "XK_KP_Subtract"),
    ("DECIMAL", "XK_KP_Decimal"),
    ("DIVIDE", "XK_KP_Divide"),
    ("F1", "XK_F1"),
    ("F2", "XK_F2"),
    ("F3", "XK_F3"),
    ("F4", "XK_F4"),
    ("F5", "XK_F5"),
    ("F6", "XK_F6"),
    ("F7", "XK_F7"),
    ("F8", "XK_F8"),
    ("F9", "XK_F9"),
    ("F10", "XK_F10"),
    ("F11", "XK_F11"),
    ("F12", "XK_F12"),
    ("NUM_LOCK", "XK_Num_Lock"),
    ("SCROLL_LOCK", "XK_Scroll_Lock"),
    ("LSHIFT", "XK_Shift_L"),
    ("RSHIFT", "XK_Shift_R"),
    ("LCTRL", "XK_Control_L"),
    ("RCTRL", "XK_Control_R"),
    ("LALT", "XK_Alt_L"),
    ("RALT", "XK_Alt_R"),
    ("LSUPER", "XK_Super_L"),
    ("RSUPER", "XK_Super_R"),
    ("MENU", "XK_Menu"),
    ("COLON", "XK_colon"),
    ("PLUS", "XK_plus"),
    ("COMMA", "XK_comma"),
    ("MINUS", "XK_minus"),
    ("PERIOD", "XK_period"),
    ("SLASH", "XK_slash"),
    ("TILDE", "XK_asciitilde"),
    ("LEFT_BRACKET", "XK_bracketleft"),
    ("BACKSLASH", "XK_backslash"),
    ("RIGHT_BRACKET", "XK_bracketright"),
    ("QUOTE", "XK_apostrophe"),
]

code = """\
#include <macro/keyboard.h>

#include "../platform.h"

#include <stdexcept>

namespace Macro {
namespace Keyboard {

int MapToOSKey(Key key) {
    // clang-format off
    switch (key) {
"""

for key, os_key in key_map:
    code += f"        case Key::{key}: return {os_key};\n"

code += """\
        default:
            throw std::runtime_error("Unrecognized key (MapToOSKey): " + std::to_string(key));
    }
    // clang-format on
}

Key MapFromOSKey(int osKey) {
    // clang-format off
    switch (osKey) {
"""

for key, os_key in key_map:
    code += f"        case {os_key}: return Key::{key};\n"

code += """\
        default:
            throw std::runtime_error("Unrecognized key (MapFromOSKey): " + std::to_string(osKey));
    }
    // clang-format on
}

}  // namespace Keyboard
}  // namespace Macro
"""

with open("../src/x11/key_map.cpp", "w") as f:
    f.write(code)
