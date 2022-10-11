#ifndef _keyboard_h_
#define _keyboard_h_

#include <map>
#include <string>

namespace Macro {
namespace Keyboard {

enum Key {
    BACKSPACE, TAB,
    ENTER,
    SHIFT, CTRL, ALT, PAUSE, CAPS_LOCK,
    ESCAPE,
    SPACE, PAGE_UP, PAGE_DOWN, END, HOME, LEFT_ARROW, UP_ARROW, RIGHT_ARROW, DOWN_ARROW, SELECT, PRINT, EXECUTE, PRINT_SCREEN, INSERT, DELETE, HELP,
    ZERO, ONE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE,
    A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z,
    NUM0, NUM1, NUM2, NUM3, NUM4, NUM5, NUM6, NUM7, NUM8, NUM9,
    NUMPAD0, NUMPAD1, NUMPAD2, NUMPAD3, NUMPAD4, NUMPAD5, NUMPAD6, NUMPAD7, NUMPAD8, NUMPAD9,
    MULTIPLY, ADD, SEPARATOR, SUBTRACT, DECIMAL, DIVIDE,
    F1, F2, F3, F4, F5, F6, F7, F8, F9, F10, F11, F12,
    LSHIFT, RSHIFT, LCTRL, RCTRL, LALT, RALT, LSUPER, RSUPER,
    COLON, PLUS, COMMA, MINUS, PERIOD, SLASH, TILDE,
    LEFT_BRACKET, BACKSLASH, RIGHT_BRACKET, QUOTE, OEM_8, OEM_102,
};

struct Combo {
    Key key;
    bool shift;
    bool ctrl;
    bool alt;
};

std::string GetKeyName(Key key);
int MapToOSKey(Key key);
Key OSKeyToKey(int osKey);
Combo MapFromChar(char c);

enum KeyState { UP, DOWN };

typedef std::map<Key, KeyState> KeyStateMap;

typedef void (*KeyCallback)(Key key, KeyState state);

// Events
void SetCallback(KeyCallback callback); // common

// State
KeyStateMap GetState();

// Commands
void Down(Key key);
void Up(Key key);
void Tap(Key key); // common
void Type(const std::string& text); // common

}  // namespace Keyboard
}  // namespace Macro

#endif // _keyboard_h_
