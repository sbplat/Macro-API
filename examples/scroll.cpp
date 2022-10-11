#include <macro/macro.h>

#include <iostream>

int main() {
    Macro::Misc::Sleep(2000);
    Macro::Mouse::Scroll(120);
    Macro::Misc::Sleep(1000);
    Macro::Mouse::Scroll(-240);
    Macro::Misc::Sleep(1000);
    Macro::Mouse::Scroll(120, true);
    Macro::Misc::Sleep(1000);
    Macro::Mouse::Scroll(-240, true);

    std::cout << "Done!" << std::endl;
    std::cin.get();

    return 0;
}
