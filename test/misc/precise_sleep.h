#include <chrono>
#include <thread>

TEST_CASE("[misc] precise sleep") {
    int ms = 100;

    auto start = std::chrono::high_resolution_clock::now();
    Macro::Misc::PreciseSleep(ms);
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);

    int ns = duration.count();

    INFO("Slept for ", ns, "ns");
    CHECK_GE(ns, ms * 1e6);
    CHECK_LE(ns, ms * 1e6 * 1.5);
}
