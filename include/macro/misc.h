#ifndef _misc_h_
#define _misc_h_

namespace Macro {
namespace Misc {

///////////////////////////////////////////////////////////////////////////////
/// \brief Block the current thread for a specified amount of time.
///
/// This function is a wrapper around std::this_thread::sleep_for.
///
/// \param ms The number of milliseconds to block the current thread for.
///////////////////////////////////////////////////////////////////////////////
void Sleep(int ms);  // common

///////////////////////////////////////////////////////////////////////////////
/// \brief Precisely block the current thread for a specified amount of time.
///
/// This function is very accurate, but also expensive. It utilizes the Sleep
/// function when the specified time is greater than 50ms and spin waits for
/// the remaining time. The accuracy is normally within 1ms.
///
/// \param ms The number of milliseconds to block the current thread for.
///////////////////////////////////////////////////////////////////////////////
void PreciseSleep(int ms);

}  // namespace Misc
}  // namespace Macro

#endif  // _misc_h_
