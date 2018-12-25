add_executable(complex_test complex_test)
set_property(TARGET complex_test PROPERTY CXX_STANDARD 14)

add_executable(dynamic_array_t_test dynamic_array_t_test)
set_property(TARGET dynamic_array_t_test PROPERTY CXX_STANDARD 14)

add_executable(dynamic_array_test dynamic_array_test)
set_property(TARGET dynamic_array_test PROPERTY CXX_STANDARD 14)

add_executable(matrix_test matrix_test)
set_property(TARGET matrix_test PROPERTY CXX_STANDARD 14)

add_executable(priority_queue_on_array_test priority_queue_on_array_test)
set_property(TARGET priority_queue_on_array_test PROPERTY CXX_STANDARD 14)

add_executable(priority_queue_on_list_test priority_queue_on_list_test)
set_property(TARGET priority_queue_on_list_test PROPERTY CXX_STANDARD 14)

add_executable(queue_on_array_test queue_on_array_test)
set_property(TARGET queue_on_array_test PROPERTY CXX_STANDARD 14)

add_executable(rational_test rational_test)
set_property(TARGET rational_test PROPERTY CXX_STANDARD 14)

add_executable(stack_on_list_test stack_on_list_test)
set_property(TARGET stack_on_list_test PROPERTY CXX_STANDARD 14)

target_link_libraries(complex_test complex)
target_link_libraries(dynamic_array_test dynamic_array)
target_link_libraries(dynamic_array_t_test dynamic_array_t)
target_link_libraries(matrix_test matrix)
target_link_libraries(priority_queue_on_array_test priority_queue_on_array)
target_link_libraries(priority_queue_on_list_test priority_queue_on_list)
target_link_libraries(queue_on_array_test queue_on_array)
target_link_libraries(rational_test rational)
target_link_libraries(stack_on_list_test stack_on_list)