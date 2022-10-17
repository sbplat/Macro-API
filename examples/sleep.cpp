#include <macro/macro.h>

#include <chrono>
#include <iostream>

int main() {
    std::cout << "Sleeping for 1000 milliseconds..." << std::endl;
    auto start = std::chrono::high_resolution_clock::now();
    Macro::Misc::Sleep(1000);
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
    std::cout << "Sleep(1000) took " << duration.count() << " nanoseconds" << std::endl;

    std::cout << "Sleeping for 10000 milliseconds..." << std::endl;
    start = std::chrono::high_resolution_clock::now();
    Macro::Misc::Sleep(10000);
    end = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
    std::cout << "Sleep(10000) took " << duration.count() << " nanoseconds" << std::endl;

    std::cout << "Done!" << std::endl;
    std::cin.get();

    return 0;
}
