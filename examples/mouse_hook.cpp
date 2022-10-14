#include <macro/macro.h>

#include <iostream>
#include <thread>

bool moveCallback(Macro::Mouse::Point position) {
    std::cout << "Move: " << position.x << ", " << position.y << std::endl;

    // Block the mouse from moving to the left of the screen.
    if (position.x < 100) {
        return true;
    }

    return false;
}

bool buttonCallback(Macro::Mouse::Button button, Macro::Mouse::ButtonState state) {
    std::cout << "Button: " << Macro::Mouse::GetButtonName(button) << ", " << (state == Macro::Mouse::UP ? "UP" : "DOWN") << std::endl;

    // Block the right mouse button from being pressed.
    if (button == Macro::Mouse::RIGHT) {
        return true;
    }

    return false;
}

bool scrollCallback(int delta) {
    std::cout << "Scroll: " << delta << std::endl;

    // Block scrolling down.
    if (delta < 0) {
        return true;
    }

    return false;
}

int main() {
    Macro::Mouse::SetMoveCallback(moveCallback);
    Macro::Mouse::SetButtonCallback(buttonCallback);
    Macro::Mouse::SetScrollCallback(scrollCallback);
    std::thread mouseHookThread(Macro::Mouse::MouseHookLoop);
    mouseHookThread.detach();

    while (true) {
        Macro::Misc::Sleep(1000);
    }

    return 0;
}
