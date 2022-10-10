#include <macro/macro.h>

int main() {
    Macro::Misc::Sleep(2000);
    Macro::Mouse::MoveRelative(-300, -300);
    Macro::Misc::Sleep(2000);
    Macro::Mouse::MoveAbsolute(30000, 30000);
    return 0;
}
