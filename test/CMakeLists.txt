link_libraries(macro)

enable_testing()

add_executable(tests "main.cpp")
target_link_libraries(tests Threads::Threads)
add_test(tests tests)
