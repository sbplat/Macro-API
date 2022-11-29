#ifndef _keyboard_h_
#define _keyboard_h_

#include "states.h"

#include <string>

namespace Macro {
namespace Keyboard {

enum Key {
    // clang-format off
    BACKSPACE, TAB,
    CLEAR, ENTER,
    PAUSE, CAPS_LOCK,
    ESCAPE,
    SPACE, PAGE_UP, PAGE_DOWN, END, HOME, LEFT_ARROW, UP_ARROW, RIGHT_ARROW, DOWN_ARROW, SELECT,
    EXECUTE, PRINT_SCREEN, INSERT, DELETE, HELP,
    ZERO, ONE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE,
    A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z,
    NUMPAD0, NUMPAD1, NUMPAD2, NUMPAD3, NUMPAD4, NUMPAD5, NUMPAD6, NUMPAD7, NUMPAD8, NUMPAD9,
    MULTIPLY, ADD, SEPARATOR, SUBTRACT, DECIMAL, DIVIDE,
    F1, F2, F3, F4, F5, F6, F7, F8, F9, F10, F11, F12,
    NUM_LOCK, SCROLL_LOCK,
    LSHIFT, RSHIFT, LCTRL, RCTRL, LALT, RALT, LSUPER, RSUPER, MENU,
    COLON, PLUS, COMMA, MINUS, PERIOD, SLASH, TILDE,
    LEFT_BRACKET, BACKSLASH, RIGHT_BRACKET, QUOTE,
    // clang-format on
};

struct Combo {
    Key key;
    bool shift;
    bool ctrl;
    bool alt;
};

///////////////////////////////////////////////////////////////////////////////
/// \brief Get the key name of a key as a string.
///
/// Example:
/// \code
/// std::string name = GetKeyName(Key::CAPS_LOCK);  // name = "CAPS_LOCK"
/// \endcode
///
/// \param key The key to get the name of.
/// \exception std::runtime_error Thrown if the key is invalid.
///
/// \return The key name of the specified key as a string.
///////////////////////////////////////////////////////////////////////////////
std::string GetKeyName(Key key);
int MapToOSKey(Key key);
Key MapFromOSKey(int osKey);
Combo MapFromChar(char c);

enum KeyState { UP, DOWN };

typedef States<KeyState, Key, Key::QUOTE + 1> KeyStates;

typedef bool (*KeyCallback)(Key key, KeyState state);

// Events
void SetCallback(KeyCallback callback);  // common
void KeyboardHookLoop();

// State
KeyState GetKeyState(Key key);    // common
const KeyStates &GetKeyStates();  // common

// Commands
void Down(Key key);
void Up(Key key);
void Tap(Key key, int ms = 10);                   // common
void Type(const std::string &text, int ms = 10);  // common

}  // namespace Keyboard
}  // namespace Macro

#endif  // _keyboard_h_
