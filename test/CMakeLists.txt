link_libraries(macro)

enable_testing()

add_executable(tests "main.cpp")
if(NOT WIN32)
    target_link_libraries(tests Threads::Threads)
endif()
add_test(tests tests)
