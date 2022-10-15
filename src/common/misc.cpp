#include <macro/misc.h>

#include "../platform.h"

#include <chrono>
#include <thread>

namespace Macro {
namespace Misc {

void Sleep(int ms) { std::this_thread::sleep_for(std::chrono::milliseconds(ms)); }

}  // namespace Misc
}  // namespace Macro
