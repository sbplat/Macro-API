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
    do {
        QueryPerformanceCounter(&end);
    } while ((end.QuadPart - start.QuadPart) * 1000 / frequency.QuadPart < ms);
}

}  // namespace Misc
}  // namespace Macro
