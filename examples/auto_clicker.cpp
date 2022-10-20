#include <macro/macro.h>

#include <iostream>
#include <thread>

bool buttonCallback(Macro::Mouse::Button button, Macro::Mouse::ButtonState state) {
    // Block X1 and X2 button presses.
    return (button == Macro::Mouse::Button::X1 || button == Macro::Mouse::Button::X2);
}

int main() {
    std::cout << "Starting auto clicker..." << std::endl;

    // Register our button callback.
    Macro::Mouse::SetButtonCallback(buttonCallback);
    std::cout << "Registered button callback." << std::endl;

    // Start the mouse hook in a separate thread so it doesn't block our main loop.
    std::thread(Macro::Mouse::MouseHookLoop).detach();
    std::cout << "Mouse hook started." << std::endl;

    std::cout << "Hold the X1 mouse button down to temporarily enable the left auto clicker.\n"
              << "Hold the X2 mouse button down to temporarily enable the right auto clicker.\n"
              << "Press Ctrl+C to exit." << std::endl;

    while (true) {
        // Get the current mouse button states.
        const Macro::Mouse::ButtonStates &buttonStates = Macro::Mouse::GetButtonStates();

        // We create two variables that store the state of the X1 and X2 buttons.
        // This is to ensure that the clicker releases the button even if the user releases their
        // X1 or X2 mouse button.
        bool x1Pressed = (buttonStates[Macro::Mouse::X1] == Macro::Mouse::ButtonState::DOWN);
        bool x2Pressed = (buttonStates[Macro::Mouse::X2] == Macro::Mouse::ButtonState::DOWN);

        if (x1Pressed) {
            // Press the left mouse button.
            Macro::Mouse::Down(Macro::Mouse::Button::LEFT);
        }

        if (x2Pressed) {
            // Press the right mouse button.
            Macro::Mouse::Down(Macro::Mouse::Button::RIGHT);
        }

        // Hold the mouse buttons down for 20 milliseconds.
        // We are using Sleep instead of PreciseSleep because we don't need the precision.
        Macro::Misc::Sleep(20);

        if (x1Pressed) {
            // Release the left mouse button.
            Macro::Mouse::Up(Macro::Mouse::Button::LEFT);
        }

        if (x2Pressed) {
            // Release the right mouse button.
            Macro::Mouse::Up(Macro::Mouse::Button::RIGHT);
        }

        // Wait 20 milliseconds before clicking again.
        Macro::Misc::Sleep(20);
    }
}
