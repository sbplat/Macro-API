#include <macro/macro.h>

#include <iostream>
#include <thread>

bool keyCallback(Macro::Keyboard::Key key, Macro::Keyboard::KeyState state) {
    std::cout << "Key: " << Macro::Keyboard::GetKeyName(key) << ", State: " << (state == Macro::Keyboard::KeyState::UP ? "UP" : "DOWN") << std::endl;

    // Block the escape key.
    if (key == Macro::Keyboard::Key::ESCAPE) {
        return true;
    }

    return false;
}

int main() {
    Macro::Keyboard::SetCallback(keyCallback);
    std::thread keyboardHookThread(Macro::Keyboard::KeyboardHookLoop);
    keyboardHookThread.detach();

    while (true) {
        Macro::Misc::Sleep(1000);
    }

    return 0;
}
