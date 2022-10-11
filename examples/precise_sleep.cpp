#include <macro/macro.h>

#include <chrono>
#include <iostream>

int main() {
    auto start = std::chrono::high_resolution_clock::now();
    Macro::Misc::PreciseSleep(1000);
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
    std::cout << "PreciseSleep(1000) took " << duration.count() << " nanoseconds" << std::endl;

    std::cout << "Done!" << std::endl;
    std::cin.get();

    return 0;
}
