file(GLOB TEST_FILES "*.cc")

foreach(test_file ${TEST_FILES})
    get_filename_component(test_file_filename ${test_file} NAME_WE)    
    add_executable(${test_file_filename} ${test_file})
    target_link_libraries(${test_file_filename} tui-lib menu)
endforeach()