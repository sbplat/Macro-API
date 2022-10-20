#include <macro/macro.h>

#include <iostream>
#include <thread>

int main() {
    std::thread(Macro::Keyboard::KeyboardHookLoop).detach();
    Macro::Misc::Sleep(2000);

    const Macro::Keyboard::KeyStates &keyStates = Macro::Keyboard::GetKeyStates();

    for (Macro::Keyboard::Key key = Macro::Keyboard::Key::BACKSPACE;
         key <= Macro::Keyboard::Key::QUOTE; key = static_cast<Macro::Keyboard::Key>(key + 1)) {
        std::cout << "Key: " << Macro::Keyboard::GetKeyName(key) << ", State: "
                  << (keyStates[key] == Macro::Keyboard::KeyState::DOWN ? "DOWN" : "UP")
                  << std::endl;
    }

    std::cout << "Done!" << std::endl;
    std::cin.get();

    return 0;
}
