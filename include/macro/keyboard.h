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
/// \brief Get the key name of a \ref Key as a std::string.
///
/// Example:
/// \code
/// std::string name = GetKeyName(Key::CAPS_LOCK);  // name = "CAPS_LOCK"
/// \endcode
///
/// \param key The \ref Key to get the name of.
/// \exception std::runtime_error Thrown if the \ref Key is invalid.
///
/// \return The key name of the specified \ref Key as a std::string.
///////////////////////////////////////////////////////////////////////////////
std::string GetKeyName(Key key);

///////////////////////////////////////////////////////////////////////////////
/// \brief Map a \ref Key to the OS-specific key code.
///
/// The OS-specific key code is different for each OS. This function maps the
/// \ref Key to the OS-specific key code. The OS used is determined by CMake.
///
/// Example (win32):
/// \code
/// int osKey = MapToOSKey(Key::BACKSPACE);  // osKey = VK_BACK (0x08)
/// \endcode
///
/// \param key The \ref Key to map to the OS-specific key code.
/// \exception std::runtime_error Thrown if the \ref Key is invalid.
///
/// \return The OS-specific key code of the specified key as an int.
///////////////////////////////////////////////////////////////////////////////
int MapToOSKey(Key key);

///////////////////////////////////////////////////////////////////////////////
/// \brief Map an OS-specific key code to a \ref Key.
///
/// The OS-specific key code is different for each OS. This function maps the
/// OS-specific key code to a \ref Key. The OS used is determined by CMake.
///
/// Example (win32):
/// \code
/// Key key = MapFromOSKey(VK_BACK);  // key = Key::BACKSPACE
/// \endcode
///
/// \param osKey The OS-specific key code to map to a \ref Key.
/// \exception std::runtime_error Thrown if the OS-specific key code is invalid.
///
/// \return The key code of the specified OS-specific key code.
Key MapFromOSKey(int osKey);

///////////////////////////////////////////////////////////////////////////////
/// \brief Map a character to a \ref Combo.
///
/// This function maps a character to a \ref Combo. The key and modifiers of
/// the \ref Combo are the ones that would be used to type the given character
/// on a standard US keyboard.
///
/// Example (win32):
/// \code
/// Combo combo = MapFromChar('!');
/// // combo.key = Key::ONE
/// // combo.shift = true
/// // combo.ctrl = false
/// // combo.alt = false
/// \endcode
///
/// \param c The character to map to a \ref Combo.
/// \exception std::runtime_error Thrown if the character cannot be mapped.
///
/// \return The \ref Combo that would be used to type the given character.
Combo MapFromChar(char c);

///////////////////////////////////////////////////////////////////////////////
/// \brief The state of a \ref Key.
///
/// This enum represents the state of a keybord key.
///////////////////////////////////////////////////////////////////////////////
enum KeyState {
    UP,   ///< The key is released.
    DOWN  ///< The key is pressed.
};

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
