# -----------------------------------------------------
# src/module_input_handler/CMakeLists.txt
# CMakeLists.txt for Module_input_handler 
#
# This file defines the module_input_handler static library. It is compiled independently
# and can be tested separately.
# It is included from the top-level CMakeLists.txt via `add_subdirectory(src/module_input_handler)`.
# The module is compiled as a static library and can be linked by main programs or tests.
# -----------------------------------------------------

# Create the static library from the module_input_handler source file
add_library(module_input_handler module_input_handler.c)

# Include the current source directory for header file access
# Since it is PRIVATE, the includes must include the path to the headers
target_include_directories(module_input_handler PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
# Link utils because module_input_handler depends on utils
target_link_libraries(module_input_handler PRIVATE utils)

# Print a status message during CMake configuration to confirm module_input_handler is processed
message(STATUS "(${PROJECT_NAME}) Module_input_handler configured: Added as static library")
# Optionally, you can set properties or compile options specific to this module