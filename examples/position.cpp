#include <macro/macro.h>

#include <iostream>

int main() {
    while (true) {
        Macro::Mouse::Point point = Macro::Mouse::GetPosition();
        std::cout << point.x << " " << point.y << std::endl;
        Macro::Misc::Sleep(100);
    }

    return 0;
}
