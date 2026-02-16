# -----------------------------------------------------------------------------
# tests/CMakeLists.txt
#
# This file configures unit tests for each module using CTest. Each test is
# built as a standalone executable and linked with the corresponding module,
# allowing for isolated unit testing and debugging.
# -----------------------------------------------------------------------------
 
message(STATUS "(${PROJECT_NAME}) Configuring test executables for modules...")

# Test for module_args
add_executable(test_module_args test_module_args.c)
target_link_libraries(test_module_args PRIVATE module_args utils)
target_include_directories(test_module_args PRIVATE ${PROJECT_SOURCE_DIR}/src)
add_test(NAME TestModuleArgs COMMAND test_module_args arg90 arg91 arg92)
message(STATUS " - (${PROJECT_NAME}) Test for module_args added")

# Test for alphabet

# Test for automata
add_executable(test_module_automata test_module_automata.c)
target_link_libraries(test_module_automata PRIVATE automata utils)
target_include_directories(test_module_automata PRIVATE ${PROJECT_SOURCE_DIR}/src)
add_test(NAME TestModuleAutomata COMMAND test_module_automata)
message(STATUS " - (${PROJECT_NAME}) Test for module_automata added")

# Test for scanner

# Test for counter

# Test for error_handler
add_executable(test_module_error_handler test_module_error_handler.c)
target_link_libraries(test_module_error_handler PRIVATE error_handler utils)
target_include_directories(test_module_error_handler PRIVATE ${PROJECT_SOURCE_DIR}/src)
add_test(NAME TestModuleErrorHandler COMMAND test_module_error_handler)
message(STATUS " - (${PROJECT_NAME}) Test for module_error_handler added")

# Test for input_handler
add_executable(test_module_input_handler test_module_input_handler.c)
target_link_libraries(test_module_input_handler PRIVATE input_handler utils)
target_include_directories(test_module_input_handler PRIVATE ${PROJECT_SOURCE_DIR}/src)
add_test(NAME TestModuleInputHandler COMMAND test_module_input_handler)
message(STATUS " - (${PROJECT_NAME}) Test for module_input_handler added")

# Test for output_handler

# Test for token_handler
add_executable(test_module_token_handler test_module_token_handler.c)
target_link_libraries(test_module_token_handler PRIVATE token_handler utils)
target_include_directories(test_module_token_handler PRIVATE ${PROJECT_SOURCE_DIR}/src)
add_test(NAME TestModuleTokenHandler COMMAND test_module_token_handler)
message(STATUS " - (${PROJECT_NAME}) Test for module_token_handler added")


message(STATUS " - (${PROJECT_NAME}) Test configuration (executables) completed.")
