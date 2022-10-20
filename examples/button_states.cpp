#include <macro/macro.h>

#include <iostream>
#include <thread>

int main() {
    std::thread(Macro::Mouse::MouseHookLoop).detach();
    Macro::Misc::Sleep(2000);

    const Macro::Mouse::ButtonStates &buttonStates = Macro::Mouse::GetButtonStates();

    for (Macro::Mouse::Button button = Macro::Mouse::Button::LEFT;
         button <= Macro::Mouse::Button::X2;
         button = static_cast<Macro::Mouse::Button>(button + 1)) {
        std::cout << "Button: " << Macro::Mouse::GetButtonName(button) << ", State: "
                  << (buttonStates[button] == Macro::Mouse::ButtonState::DOWN ? "DOWN" : "UP")
                  << std::endl;
    }

    std::cout << "Done!" << std::endl;
    std::cin.get();

    return 0;
}
