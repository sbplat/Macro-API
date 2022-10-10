#ifndef _mouse_h_
#define _mouse_h_

#include <map>

namespace Macro {
namespace Mouse {

enum Button { LEFT, RIGHT, MIDDLE, X1, X2 };
const char* GetButtonName(Button button);

enum State { UP, DOWN };

struct Point {
    int x;
    int y;
};

typedef std::map<Button, State> ButtonStateMap;

typedef void (*MoveCallback)(Point position);
typedef void (*ButtonCallback)(Button button, State state);
typedef void (*ScrollCallback)(int delta);

// Events
void SetMoveCallback(MoveCallback callback); // common
void SetButtonCallback(ButtonCallback callback); // common
void SetScrollCallback(ScrollCallback callback); // common

// State
Point GetPosition();
ButtonStateMap GetButtonStates();

// Commands
void MoveAbsolute(int x, int y);
void MoveRelative(int x, int y);
void Down(Button button);
void Up(Button button);
void Click(Button button); // common
void Scroll(int delta, bool horizontal = false);

}  // namespace Mouse
}  // namespace Macro

#endif  // _mouse_h_
