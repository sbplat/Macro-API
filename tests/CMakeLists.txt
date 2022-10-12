link_libraries(macro)

enable_testing()

set(pass_regex "Passed")
set(fail_regex "Failed")

if (NOT CTEST_CONFIGURATION_TYPE)
  set(CTEST_CONFIGURATION_TYPE ${CMAKE_BUILD_TYPE})
endif()

file(GLOB test_srcs "*.cpp")
foreach(test_src ${test_srcs})
    get_filename_component(test_name ${test_src} NAME_WE)
    add_executable(${test_name} ${test_src})
    add_test(
        NAME ${test_name}
        COMMAND ${test_name}
    )
    set_property(TEST ${test_name}
        PROPERTY PASS_REGULAR_EXPRESSION ${pass_regex}
    )
    add_custom_command(TARGET ${test_name}
        POST_BUILD
            COMMAND ${CMAKE_CTEST_COMMAND} -C ${CTEST_CONFIGURATION_TYPE}
    )
endforeach()
