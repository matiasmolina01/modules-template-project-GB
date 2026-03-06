# -----------------------------------------------------------------------------
# tests/CMakeLists.txt
#
# This file configures unit tests for each module using CTest. Each test is
# built as a standalone executable and linked with the corresponding module,
# allowing for isolated unit testing and debugging.
# -----------------------------------------------------------------------------
 
message(STATUS "(${PROJECT_NAME}) Configuring test executables for modules...")

# Test for automata
# add_executable(test_module_automata test_module_automata.c)
# target_link_libraries(test_module_automata PRIVATE automata utils)
# target_include_directories(test_module_automata PRIVATE ${PROJECT_SOURCE_DIR}/src)
# add_test(NAME TestModuleAutomata COMMAND test_module_automata)
# message(STATUS " - (${PROJECT_NAME}) Test for module_automata added")

# Test for language
add_executable(test_module_language test_module_language.c)
target_link_libraries(test_module_language PRIVATE language utils)
target_include_directories(test_module_language PRIVATE ${PROJECT_SOURCE_DIR}/src)
add_test(NAME TestModuleLanguage COMMAND test_module_language)
message(STATUS " - (${PROJECT_NAME}) Test for module_language added")

# Test for input
add_executable(test_module_input test_module_input.c)
target_link_libraries(test_module_input PRIVATE input_handler token_handler global_context language automata stack sra utils)
target_include_directories(test_module_input PRIVATE ${PROJECT_SOURCE_DIR}/src)
add_test(NAME TestModuleInput COMMAND test_module_input)
message(STATUS " - (${PROJECT_NAME}) Test for module_input added")

# Test for global_context
add_executable(test_module_global_context test_module_global_context.c)
target_link_libraries(test_module_global_context PRIVATE global_context utils)
target_include_directories(test_module_global_context PRIVATE ${PROJECT_SOURCE_DIR}/src)
add_test(NAME TestModuleGlobalContext COMMAND test_module_global_context)
message(STATUS " - (${PROJECT_NAME}) Test for module_global_context added")

# Test for sra
add_executable(test_module_sra test_module_sra.c)
target_link_libraries(test_module_sra PRIVATE sra stack automata utils)
target_include_directories(test_module_sra PRIVATE ${PROJECT_SOURCE_DIR}/src)
add_test(NAME TestModuleSRA COMMAND test_module_sra)
message(STATUS " - (${PROJECT_NAME}) Test for module_sra added")


message(STATUS " - (${PROJECT_NAME}) Test configuration (executables) completed.")
