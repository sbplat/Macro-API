#include <macro/macro.h>

#include <iostream>
#include <thread>

int main() {
    std::thread(Macro::Mouse::MouseHookLoop).detach();
    Macro::Misc::Sleep(2000);

    const Macro::Mouse::ButtonStateMap &buttonStates = Macro::Mouse::GetButtonStates();
    for (const auto &buttonState : buttonStates) {
        std::cout << "Button: " << Macro::Mouse::GetButtonName(buttonState.first)
                  << ", State: " << (buttonState.second == Macro::Mouse::ButtonState::DOWN ? "DOWN" : "UP") << std::endl;
    }

    std::cout << "Done!" << std::endl;
    std::cin.get();

    return 0;
}
