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

# Test for module_io_handler
add_executable(test_module_io_handler test_module_io_handler.c)
target_link_libraries(test_module_io_handler PRIVATE module_io_handler utils)
target_include_directories(test_module_io_handler PRIVATE ${PROJECT_SOURCE_DIR}/src)
add_test(NAME TestModuleIOHandler COMMAND test_module_io_handler)
message(STATUS " - (${PROJECT_NAME}) Test for module_io_handler added")

# Test for module_symbol_table
add_executable(test_module_symbol_table test_module_symbol_table.c)
target_link_libraries(test_module_symbol_table PRIVATE module_symbol_table utils)
target_include_directories(test_module_symbol_table PRIVATE ${PROJECT_SOURCE_DIR}/src)
add_test(NAME TestModuleSymbolTable COMMAND test_module_symbol_table)
message(STATUS " - (${PROJECT_NAME}) Test for module_symbol_table added")

# Test for module_classifier
add_executable(test_module_classifier test_module_classifier.c)
target_link_libraries(test_module_classifier PRIVATE module_classifier utils)
target_include_directories(test_module_classifier PRIVATE ${PROJECT_SOURCE_DIR}/src)
add_test(NAME TestModuleClassifier COMMAND test_module_classifier)
message(STATUS " - (${PROJECT_NAME}) Test for module_classifier added")

# Test for module_recursivity_handler
add_executable(test_module_rh test_module_rh.c)
target_link_libraries(test_module_rh PRIVATE module_recursivity_handler module_symbol_table utils)
target_include_directories(test_module_rh PRIVATE ${PROJECT_SOURCE_DIR}/src)
add_test(NAME TestModuleRecursivityHandler COMMAND test_module_rh)
message(STATUS " - (${PROJECT_NAME}) Test for module_recursivity_handler added")

# Test for module_2
# add_executable(test_module_2 test_module_2.c)
# target_link_libraries(test_module_2 PRIVATE module_2 utils)
# target_include_directories(test_module_2 PRIVATE ${PROJECT_SOURCE_DIR}/src)
# add_test(NAME TestModule_2 COMMAND test_module_2)
# message(STATUS " - (${PROJECT_NAME}) Test for module_2 added")

# message(STATUS " - (${PROJECT_NAME}) Test configuration (executables) completed.")
