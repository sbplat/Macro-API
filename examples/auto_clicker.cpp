#include <macro/macro.h>

#include <iostream>
#include <thread>

using namespace Macro;

bool buttonCallback(Mouse::Button button, Mouse::ButtonState state) {
    // Block X1 and X2 button presses.
    return (button == Mouse::Button::X1 || button == Mouse::Button::X2);
}

int main() {
    std::cout << "Starting auto clicker..." << std::endl;

    // Register our button callback.
    Mouse::SetButtonCallback(buttonCallback);
    std::cout << "Registered button callback." << std::endl;

    // Start the mouse hook in a separate thread so it doesn't block our main loop.
    std::thread(Mouse::MouseHookLoop).detach();
    std::cout << "Mouse hook started." << std::endl;

    std::cout << "Hold the X1 mouse button down to temporarily enable the left auto clicker.\n"
              << "Hold the X2 mouse button down to temporarily enable the right auto clicker.\n"
              << "Press Ctrl+C to exit." << std::endl;

    while (true) {
        // Get the current mouse button states.
        const Mouse::ButtonStates &buttonStates = Mouse::GetButtonStates();

        // We create two variables that store the state of the X1 and X2 buttons.
        // This is to ensure that the clicker releases the button even if the user releases their
        // X1 or X2 mouse button.
        bool x1Pressed = (buttonStates[Mouse::X1] == Mouse::ButtonState::DOWN);
        bool x2Pressed = (buttonStates[Mouse::X2] == Mouse::ButtonState::DOWN);

        if (x1Pressed) {
            // Press the left mouse button.
            Mouse::Down(Mouse::Button::LEFT);
        }

        if (x2Pressed) {
            // Press the right mouse button.
            Mouse::Down(Mouse::Button::RIGHT);
        }

        // Hold the mouse buttons down for 20 milliseconds.
        // We are using Sleep instead of PreciseSleep because we don't need the precision.
        Misc::Sleep(20);

        if (x1Pressed) {
            // Release the left mouse button.
            Mouse::Up(Mouse::Button::LEFT);
        }

        if (x2Pressed) {
            // Release the right mouse button.
            Mouse::Up(Mouse::Button::RIGHT);
        }

        // Wait 20 milliseconds before clicking again.
        Misc::Sleep(20);
    }
}
