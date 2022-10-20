#ifndef _mouse_h_
#define _mouse_h_

#include <map>
#include <string>

namespace Macro {
namespace Mouse {

enum Button { LEFT, RIGHT, MIDDLE, X1, X2 };
std::string GetButtonName(Button button);

enum ButtonState { UP, DOWN };

struct Point {
    int x;
    int y;
};

typedef std::map<Button, ButtonState> ButtonStateMap;

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
const ButtonStateMap &GetButtonStates();    // common

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
