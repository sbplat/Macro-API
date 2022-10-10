#include <macro/macro.h>

int main() {
    Macro::Misc::Sleep(2000);
    Macro::Mouse::Click(Macro::Mouse::Button::LEFT);
    Macro::Misc::Sleep(2000);
    Macro::Mouse::Click(Macro::Mouse::Button::RIGHT);
    Macro::Misc::Sleep(2000);
    Macro::Mouse::Click(Macro::Mouse::Button::MIDDLE);
    Macro::Misc::Sleep(2000);
    Macro::Mouse::Click(Macro::Mouse::Button::X1);
    Macro::Misc::Sleep(2000);
    Macro::Mouse::Click(Macro::Mouse::Button::X2);
    return 0;
}
