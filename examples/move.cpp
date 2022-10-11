#include <macro/macro.h>

#include <iostream>

int main() {
    Macro::Misc::Sleep(2000);
    Macro::Mouse::MoveRelative(-300, -300);
    Macro::Misc::Sleep(1000);
    Macro::Mouse::MoveAbsolute(30000, 30000);

    std::cout << "Done!" << std::endl;
    std::cin.get();

    return 0;
}
