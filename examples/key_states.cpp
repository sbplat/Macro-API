#include <macro/macro.h>

#include <iostream>
#include <thread>

int main() {
    std::thread(Macro::Keyboard::KeyboardHookLoop).detach();
    Macro::Misc::Sleep(2000);

    const Macro::Keyboard::KeyStateMap &keyStates = Macro::Keyboard::GetKeyStates();
    for (const auto &keyState : keyStates) {
        std::cout << "Key: " << Macro::Keyboard::GetKeyName(keyState.first) << ", State: "
                  << (keyState.second == Macro::Keyboard::KeyState::DOWN ? "DOWN" : "UP")
                  << std::endl;
    }

    std::cout << "Done!" << std::endl;
    std::cin.get();

    return 0;
}
