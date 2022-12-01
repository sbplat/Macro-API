#ifndef _mouse_h_
#define _mouse_h_

#include "states.h"

#include <string>

namespace Macro {
namespace Mouse {

enum Button { LEFT, RIGHT, MIDDLE, X1, X2 };

///////////////////////////////////////////////////////////////////////////////
/// \brief Get the button name of a \ref Button as a std::string.
///
/// Example:
/// \code
/// std::string name = GetButtonName(Button::LEFT);  // name = "LEFT"
/// \endcode
///
/// \param button The \ref Button to get the name of.
/// \exception std::runtime_error Thrown if the \ref Button is invalid.
///
/// \return The button name of the specified \ref Button as a std::string.
///////////////////////////////////////////////////////////////////////////////
std::string GetButtonName(Button button);

///////////////////////////////////////////////////////////////////////////////
/// \brief The state of a mouse \ref Button.
///
/// This enum represents the state of a mouse button.
///////////////////////////////////////////////////////////////////////////////
enum ButtonState {
    UP,   ///< The button is released.
    DOWN  ///< The button is pressed.
};

///////////////////////////////////////////////////////////////////////////////
/// \brief An x, y coordinate pair.
///
/// This struct is used to represent an integer x, y coordinate pair.
///////////////////////////////////////////////////////////////////////////////
struct Point {
    int x;  ///< The x coordinate.
    int y;  ///< The y coordinate.
};

///////////////////////////////////////////////////////////////////////////////
/// \brief The state of all mouse buttons.
///
/// ButtonStates is a wrapper around the \ref States class. It is used to
/// represent the state of all buttons at a certain point in time. The state of
/// a button can be accessed or modified using the subscript operator with a
/// \ref Button as the index.
///
/// \see States
///////////////////////////////////////////////////////////////////////////////
typedef States<ButtonState, Button, Button::X2 + 1> ButtonStates;

typedef bool (*MoveCallback)(Point position);
typedef bool (*ButtonCallback)(Button button, ButtonState state);
typedef bool (*ScrollCallback)(int delta, bool horizontal);

// Events
void SetMoveCallback(MoveCallback callback);      // common
void SetButtonCallback(ButtonCallback callback);  // common
void SetScrollCallback(ScrollCallback callback);  // common
void MouseHookLoop();

// State
Point GetPosition();
ButtonState GetButtonState(Button button);  // common
const ButtonStates &GetButtonStates();      // common

// Commands
void MoveAbsolute(int x, int y);
void MoveRelative(int x, int y);
void Down(Button button);
void Up(Button button);
void Click(Button button, int ms = 10);  // common
void Scroll(int delta, bool horizontal = false);

}  // namespace Mouse
}  // namespace Macro

#endif  // _mouse_h_
