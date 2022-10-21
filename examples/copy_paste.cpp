#include <macro/macro.h>

#include <iostream>

int main() {
    std::cout << "Copy me and paste me!" << std::endl;

    // Select all text (Ctrl+A)
    Macro::Keyboard::Down(Macro::Keyboard::Key::LCTRL);
    Macro::Keyboard::Tap(Macro::Keyboard::Key::A, 40);
    Macro::Keyboard::Up(Macro::Keyboard::Key::LCTRL);

    // Copy the selected text (Ctrl+C)
    Macro::Keyboard::Down(Macro::Keyboard::Key::LCTRL);
    Macro::Keyboard::Tap(Macro::Keyboard::Key::C, 40);
    Macro::Keyboard::Up(Macro::Keyboard::Key::LCTRL);

    Macro::Misc::Sleep(2000);

    // Paste the copied text again (Ctrl+V)
    Macro::Keyboard::Down(Macro::Keyboard::Key::LCTRL);
    Macro::Keyboard::Tap(Macro::Keyboard::Key::V, 40);
    Macro::Keyboard::Up(Macro::Keyboard::Key::LCTRL);

    std::cout << "Done!" << std::endl;
    std::cin.get();

    return 0;
}
