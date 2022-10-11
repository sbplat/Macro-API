add_library(macro ${MACRO_LIBRARY_TYPE}
    "${MACRO_SOURCE_DIR}/include/macro/macro.h"
    "${MACRO_SOURCE_DIR}/include/macro/keyboard.h"
    "${MACRO_SOURCE_DIR}/include/macro/mouse.h"
    "${MACRO_SOURCE_DIR}/include/macro/misc.h"
    platform.h internal.h
    common/keyboard.cpp common/keyboard_key_to_string.cpp
    common/mouse.cpp common/misc.cpp
)

if (WIN32)
    message(STATUS "Detected platform: Windows")
    target_compile_definitions(macro PRIVATE _MACRO_WIN32)
    target_sources(macro PRIVATE
        win32/keyboard.cpp win32/keyboard_events.cpp
        win32/mouse.cpp win32/mouse_events.cpp
        win32/misc.cpp
    )
elseif (APPLE)
    message(STATUS "Detected platform: macOS")
    target_compile_definitions(macro PRIVATE _MACRO_COCOA)
    target_sources(macro PRIVATE
        cocoa/keyboard.cpp cocoa/mouse.cpp cocoa/misc.cpp
    )
elseif (UNIX)
    message(STATUS "Detected platform: Linux")
    target_compile_definitions(macro PRIVATE _MACRO_X11)
    target_sources(macro PRIVATE
        x11/keyboard.cpp x11/mouse.cpp x11/misc.cpp
    )
else ()
    message(FATAL_ERROR "Unsupported platform")
endif()

set_target_properties(macro PROPERTIES
    CXX_STANDARD 11
    CXX_EXTENSIONS OFF
    OUTPUT_NAME macro
    VERSION ${PROJECT_VERSION}
    SOVERSION ${PROJECT_VERSION_MAJOR}
    POSITION_INDEPENDENT_CODE ON
    FOLDER "macro"
)

target_include_directories(macro PUBLIC
    $<BUILD_INTERFACE:${MACRO_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

target_include_directories(macro PRIVATE
    ${MACRO_SOURCE_DIR}/src
    ${MACRO_BINARY_DIR}/src
)

if (MACRO_INSTALL)
    #todo
endif()
