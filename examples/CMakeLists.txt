link_libraries(macro)

file(GLOB example_srcs "*.cpp")
foreach(example_src ${example_srcs})
    get_filename_component(example_name ${example_src} NAME_WE)
    add_executable(${example_name} ${example_src})
endforeach()
