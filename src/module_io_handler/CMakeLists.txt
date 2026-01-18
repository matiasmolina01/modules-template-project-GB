# -----------------------------------------------------
# src/module_io_handler/CMakeLists.txt
# CMakeLists.txt for Module_io_handler 
#
# This file defines the module_io_handler static library. It is compiled independently
# and can be tested separately.
# It is included from the top-level CMakeLists.txt via `add_subdirectory(src/module_io_handler)`.
# The module is compiled as a static library and can be linked by main programs or tests.
# -----------------------------------------------------

# Create the static library from the module_io_handler source file
add_library(module_io_handler module_io_handler.c)

# Include the current source directory for header file access
# Since it is PRIVATE, the includes must include the path to the headers
target_include_directories(module_io_handler PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
# Link utils because module_io_handler depends on utils
target_link_libraries(module_io_handler PRIVATE utils)

# Print a status message during CMake configuration to confirm module_io_handler is processed
message(STATUS "(${PROJECT_NAME}) Module_io_handler configured: Added as static library")
# Optionally, you can set properties or compile options specific to this module