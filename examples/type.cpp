#include <macro/macro.h>

#include <iostream>

int main() {
    Macro::Misc::Sleep(2000);
    Macro::Keyboard::Type(R"(abcdefghijklmnopqrstuvwxyz ABCDEFGHIJKLMNOPQRSTUVWXYZ 1234567890 !@#$%^&*() _+-=[]\{}|;':",./<>?`~)");

    std::cout << "Done!" << std::endl;
    std::cin.get();

    return 0;
}
