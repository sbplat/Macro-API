#include <macro/macro.h>

#include <iostream>

int main() {
    Macro::Misc::Sleep(2000);
    
    std::cout << "Copy Me Once and Paste Me Twice!";

    Macro::Misc::Sleep(400);
    Macro::Keyboard::Down(Macro::Keyboard::Key::LCTRL);
    Macro::Keyboard::Tap(Macro::Keyboard::Key::A);
    Macro::Keyboard::Up(Macro::Keyboard::Key::LCTRL);

    Macro::Keyboard::Down(Macro::Keyboard::Key::LCTRL);
    Macro::Keyboard::Tap(Macro::Keyboard::Key::INSERT, 40);
    Macro::Keyboard::Up(Macro::Keyboard::Key::LCTRL);

    Macro::Keyboard::Down(Macro::Keyboard::Key::LSHIFT);
    Macro::Keyboard::Tap(Macro::Keyboard::Key::INSERT, 40);
    Macro::Keyboard::Up(Macro::Keyboard::Key::LSHIFT);

    Macro::Keyboard::Down(Macro::Keyboard::Key::LCTRL);
    Macro::Keyboard::Tap(Macro::Keyboard::Key::V, 40);
    Macro::Keyboard::Up(Macro::Keyboard::Key::LCTRL);

    Macro::Misc::Sleep(300);
    std::cout << "Done!" << std::endl;
    std::cin.get();

    return 0;
}
