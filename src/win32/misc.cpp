#include <macro/misc.h>

#include "../platform.h"

namespace Macro {
namespace Misc {

void PreciseSleep(int ms) {
    LARGE_INTEGER frequency;
    LARGE_INTEGER start;
    LARGE_INTEGER end;
    QueryPerformanceFrequency(&frequency);
    QueryPerformanceCounter(&start);
    if (ms > 50) {
        // Use the OS sleep for large intervals to avoid wasting CPU cycles.
        // Spin wait for at most 50ms to avoid the OS sleep overhead and delay.
        Sleep(ms - 50);
    }
    // Spin wait for the remaining time.
    do {
        QueryPerformanceCounter(&end);
    } while ((end.QuadPart - start.QuadPart) * 1000 / frequency.QuadPart < ms);
}

}  // namespace Misc
}  // namespace Macro
