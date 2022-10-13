link_libraries(macro)

enable_testing()

add_executable(tests "main.cpp")
add_test(tests tests)