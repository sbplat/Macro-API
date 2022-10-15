enum = """
BACKSPACE, TAB,
CLEAR, ENTER,
SHIFT, CTRL, ALT, PAUSE, CAPS_LOCK,
ESCAPE,
SPACE, PAGE_UP, PAGE_DOWN, END, HOME, LEFT_ARROW, UP_ARROW, RIGHT_ARROW, DOWN_ARROW, SELECT, PRINT, EXECUTE, PRINT_SCREEN, INSERT, DELETE, HELP,
ZERO, ONE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE,
A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z,
NUMPAD0, NUMPAD1, NUMPAD2, NUMPAD3, NUMPAD4, NUMPAD5, NUMPAD6, NUMPAD7, NUMPAD8, NUMPAD9,
MULTIPLY, ADD, SEPARATOR, SUBTRACT, DECIMAL, DIVIDE,
F1, F2, F3, F4, F5, F6, F7, F8, F9, F10, F11, F12,
NUM_LOCK, SCROLL_LOCK,
LSHIFT, RSHIFT, LCTRL, RCTRL, LALT, RALT, LSUPER, RSUPER, MENU,
COLON, PLUS, COMMA, MINUS, PERIOD, SLASH, TILDE,
LEFT_BRACKET, BACKSLASH, RIGHT_BRACKET, QUOTE, OEM_8,
OEM_102,
"""

values = [value for value in enum.replace("\n", "").replace(" ", "").split(",") if len(value) > 0]

code = """\
#include <macro/keyboard.h>

#include <stdexcept>

namespace Macro {
namespace Keyboard {

std::string GetKeyName(Key key) {
    // clang-format off
    switch (key) {
"""

for i, value in enumerate(values):
    code += f"        case Key::{value}: return \"{value}\";\n"

code += """\
        default: throw std::runtime_error("Unknown key (GetKeyName): " + std::to_string(key));
    }
    // clang-format on
}

} // namespace Keyboard
} // namespace Macro
"""

with open("../src/common/keyboard_key_to_string.cpp", "w") as f:
    f.write(code)
