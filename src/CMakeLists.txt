add_library(
    macro
    ${MACRO_LIBRARY_TYPE}
    "${MACRO_SOURCE_DIR}/include/macro/macro.h"
    "${MACRO_SOURCE_DIR}/include/macro/keyboard.h"
    "${MACRO_SOURCE_DIR}/include/macro/mouse.h"
    "${MACRO_SOURCE_DIR}/include/macro/misc.h"
    platform.h
    internal.h
    common/keyboard.cpp
    common/keyboard_key_to_string.cpp
    common/mouse.cpp
    common/misc.cpp
)

if(WIN32)
    message(STATUS "Detected platform: Windows")
    if(${CMAKE_SYSTEM_VERSION} MATCHES "^10") # Windows 10
        add_definitions(-D_WIN32_WINNT=0x0A00) # _WIN32_WINNT_WIN10
    elseif(${CMAKE_SYSTEM_VERSION} MATCHES "^6.3") # Windows 8.1
        add_definitions(-D_WIN32_WINNT=0x0603) # _WIN32_WINNT_WINBLUE
    elseif(${CMAKE_SYSTEM_VERSION} MATCHES "^6.2") # Windows 8
        add_definitions(-D_WIN32_WINNT=0x0602) # _WIN32_WINNT_WIN8
    elseif(${CMAKE_SYSTEM_VERSION} MATCHES "^6.1") # Windows 7
        add_definitions(-D_WIN32_WINNT=0x0601) # _WIN32_WINNT_WIN7
    elseif(${CMAKE_SYSTEM_VERSION} MATCHES "^6.0") # Windows Vista
        add_definitions(-D_WIN32_WINNT=0x0600) # _WIN32_WINNT_VISTA
    elseif(${CMAKE_SYSTEM_VERSION} MATCHES "^5.2") # Windows Server 2003
        add_definitions(-D_WIN32_WINNT=0x0502) # _WIN32_WINNT_WS03
    elseif(${CMAKE_SYSTEM_VERSION} MATCHES "^5.1") # Windows XP
        add_definitions(-D_WIN32_WINNT=0x0501) # _WIN32_WINNT_WINXP
    elseif(${CMAKE_SYSTEM_VERSION} MATCHES "^5.0") # Windows 2000
        add_definitions(-D_WIN32_WINNT=0x0500) # _WIN32_WINNT_WIN2K
    endif()
    target_compile_definitions(macro PRIVATE _MACRO_WIN32)
    target_sources(
        macro
        PRIVATE win32/context.cpp
                win32/keyboard.cpp
                win32/keyboard_events.cpp
                win32/key_map.cpp
                win32/mouse.cpp
                win32/mouse_events.cpp
                win32/misc.cpp
    )
elseif(APPLE)
    message(STATUS "Detected platform: macOS")
    target_compile_definitions(macro PRIVATE _MACRO_COCOA)
    target_sources(
        macro
        PRIVATE cocoa/context.cpp
                cocoa/keyboard.cpp
                cocoa/keyboard_events.cpp
                cocoa/key_map.cpp
                cocoa/mouse.cpp
                cocoa/mouse_events.cpp
                cocoa/misc.cpp
    )
elseif(UNIX)
    message(STATUS "Detected platform: Linux")
    find_package(X11 REQUIRED)
    target_compile_definitions(macro PRIVATE _MACRO_X11)
    target_sources(
        macro
        PRIVATE x11/context.cpp
                x11/keyboard.cpp
                x11/keyboard_events.cpp
                x11/key_map.cpp
                x11/mouse.cpp
                x11/mouse_events.cpp
                x11/misc.cpp
    )
else()
    message(FATAL_ERROR "Unsupported platform")
endif()

set_target_properties(
    macro
    PROPERTIES CXX_STANDARD 11
               CXX_EXTENSIONS OFF
               OUTPUT_NAME macro
               VERSION ${PROJECT_VERSION}
               SOVERSION ${PROJECT_VERSION_MAJOR}
               POSITION_INDEPENDENT_CODE ON
               FOLDER "macro"
)

if(WIN32)
    target_link_libraries(macro PRIVATE shcore)
elseif(APPLE)
    target_link_libraries(macro PRIVATE Threads::Threads)
elseif(UNIX)
    target_link_libraries(macro PRIVATE Threads::Threads X11::X11 X11::Xtst)
endif()

target_include_directories(
    macro PUBLIC $<BUILD_INTERFACE:${MACRO_SOURCE_DIR}/include>
                 $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

target_include_directories(macro PRIVATE ${MACRO_SOURCE_DIR}/src ${MACRO_BINARY_DIR}/src)

if(MACRO_INSTALL)
    # TODO
endif()
