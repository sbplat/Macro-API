#ifndef _keyboard_h_
#define _keyboard_h_

#include "states.h"

#include <string>

namespace Macro {
namespace Keyboard {

///////////////////////////////////////////////////////////////////////////////
/// \brief Enumeration of standard virtual key codes.
///
/// This enumeration contains all standard virtual key codes that can be used
/// to represent the keys in a platform-agnotic way.
///
/// \see MapToOSKey Map a virtual key code to a platform-specific key code.
/// \see MapFromOSKey Map a platform-specific key code to a virtual key code.
///////////////////////////////////////////////////////////////////////////////
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

///////////////////////////////////////////////////////////////////////////////
/// \brief A combination of a \ref Key and the state of modifier keys.
///
/// This struct is used to represent a combination of a \ref Key and the state
/// of modifier keys (shift, ctrl, and alt).
///////////////////////////////////////////////////////////////////////////////
struct Combo {
    Key key;     ///< The \ref Key.
    bool shift;  ///< Whether the shift key is pressed.
    bool ctrl;   ///< Whether the ctrl key is pressed.
    bool alt;    ///< Whether the alt key is pressed.
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

///////////////////////////////////////////////////////////////////////////////
/// \brief The state of all keys.
///
/// KeyStates is a wrapper around the \ref States class. It is used to
/// represent the state of all keys at a certain point in time. The state of a
/// key can be accessed or modified using the subscript operator with a
/// \ref Key as the index.
///
/// \see States
///////////////////////////////////////////////////////////////////////////////
typedef States<KeyState, Key, Key::QUOTE + 1> KeyStates;

///////////////////////////////////////////////////////////////////////////////
/// \brief Key callback function type.
///
/// This type is used to represent a key callback function. The callback should
/// return as quickly as possible, as it blocks the system thread that handles
/// keyboard input.
///
/// \param key The \ref Key that triggered the callback.
/// \param state The current \ref KeyState of the key.
///
/// \return Whether the event should be cancelled. If `true`, the event will be
/// cancelled. If `false`, the event will be passed to the next callback
/// handler.
///
/// \see examples/keyboard_hook.cpp An example of a key callback function.
///////////////////////////////////////////////////////////////////////////////
typedef bool (*KeyCallback)(Key key, KeyState state);

// Events
///////////////////////////////////////////////////////////////////////////////
/// \brief Set the key callback function.
///
/// This function sets the key callback function. The callback function must
/// be of type \ref KeyCallback. The callback function is called whenever a
/// keyboard event is triggered (pressing or releasing a key).
///
/// \param callback The key callback function. If a callback function already
/// exists, it will be replaced. If the callback function is set to `nullptr`,
/// no callback function will be called.
///
/// \see KeyCallback
/// \see examples/keyboard_hook.cpp An example of setting the key callback
/// function.
///////////////////////////////////////////////////////////////////////////////
void SetCallback(KeyCallback callback);  // common

///////////////////////////////////////////////////////////////////////////////
/// \brief Start the keyboard hook loop.
///
/// This function starts the keyboard hook loop. The loop calls the key
/// callback function whenever a keyboard event is triggered. It is recommended
/// to spawn a new thread, and call this function in the new thread, as the
/// function blocks the thread that it is called in. This function never
/// returns, so it should only be called once.
///
/// \see KeyCallback
/// \see SetCallback
/// \see examples/keyboard_hook.cpp An example of starting the keyboard hook
///////////////////////////////////////////////////////////////////////////////
void KeyboardHookLoop();

// State
///////////////////////////////////////////////////////////////////////////////
/// \brief Get the \ref KeyState of a single \ref Key.
///
/// This function gets the \ref KeyState of a \ref Key. The internal key state
/// cache is only updated when a keyboard event is triggered, so a key may not
/// be in the correct state if the \ref KeyboardHookLoop has recently been
/// started.
///
/// \param key The \ref Key to get the \ref KeyState of.
///
/// \return The \ref KeyState of the specified \ref Key.
///
/// \see GetKeyStates
///////////////////////////////////////////////////////////////////////////////
KeyState GetKeyState(Key key);  // common

///////////////////////////////////////////////////////////////////////////////
/// \brief Get the \ref KeyStates of all keys.
///
/// This function gets the \ref KeyStates of all keys. The key states may not
/// be in the correct state if the \ref KeyboardHookLoop has recently been
/// started (see \ref GetKeyState for more information).
///
/// \return The \ref KeyStates of all keys.
///
/// \see GetKeyState
///////////////////////////////////////////////////////////////////////////////
const KeyStates &GetKeyStates();  // common

// Commands
void Down(Key key);
void Up(Key key);
void Tap(Key key, int ms = 10);                   // common
void Type(const std::string &text, int ms = 10);  // common

}  // namespace Keyboard
}  // namespace Macro

#endif  // _keyboard_h_
