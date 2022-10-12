#include <macro/macro.h>

#include <iostream>

bool check(Macro::Keyboard::Key key) {
    int osKey = Macro::Keyboard::MapToOSKey(key);
    Macro::Keyboard::Key key2 = Macro::Keyboard::MapFromOSKey(osKey);
    if (key != key2) {
        std::cerr << "Key mismatch for " << Macro::Keyboard::GetKeyName(key) << ": " << key << " != " << key2 << std::endl;
        return false;
    }
    return true;
}

int main() {
    bool failed = false;

    for (Macro::Keyboard::Key key = Macro::Keyboard::Key::BACKSPACE; key <= Macro::Keyboard::Key::OEM_102;
         key = static_cast<Macro::Keyboard::Key>(key + 1)) {
        if (!check(key)) {
            failed = true;
        }
    }

    if (failed) {
        std::cout << "Failed" << std::endl;
        return 1;
    } else {
        std::cout << "Passed" << std::endl;
        return 0;
    }
}
