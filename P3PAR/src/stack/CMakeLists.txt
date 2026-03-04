# -----------------------------------------------------
# src/stack/CMakeLists.txt
# CMakeLists.txt for stack 
#
# This file defines the stack static library. It is compiled independently
# and can be tested separately.
# It is included from the top-level CMakeLists.txt via `add_subdirectory(src/stack)`.
# The module is compiled as a static library and can be linked by main programs or tests.
# -----------------------------------------------------

# Create the static library from the stack source file
add_library(stack stack.c)

# Include the current source directory for header file access
# Since it is PRIVATE, the includes must include the path to the headers
target_include_directories(stack PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
# Link utils because stack depends on utils
target_link_libraries(stack PRIVATE utils)

# Print a status message during CMake configuration to confirm stack is processed
message(STATUS "(${PROJECT_NAME}) stack configured: Added as static library")
# Optionally, you can set properties or compile options specific to this module