#include <macro/misc.h>

#include "../platform.h"

#include <time.h>

namespace Macro {
namespace Misc {

void PreciseSleep(int ms) {
    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start);
    if (ms > 50) {
        // Use the OS sleep for large intervals to avoid wasting CPU cycles.
        // Spin wait for at most 50ms to avoid the OS sleep overhead and delay.
        Sleep(ms - 50);
    }
    // Spin wait for the remaining time.
    do {
        clock_gettime(CLOCK_MONOTONIC, &end);
    } while ((end.tv_sec - start.tv_sec) * 1000 + (end.tv_nsec - start.tv_nsec) / 1000000 <
             ms + 1);  // We add 1 due to rounding errors.
}

}  // namespace Misc
}  // namespace Macro
