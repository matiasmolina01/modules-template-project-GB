# -----------------------------------------------------
# src/output_handler/CMakeLists.txt
# CMakeLists.txt for output_handler 
#
# This file defines the output_handler static library. It is compiled independently
# and can be tested separately.
# It is included from the top-level CMakeLists.txt via `add_subdirectory(src/output_handler)`.
# The module is compiled as a static library and can be linked by main programs or tests.
# -----------------------------------------------------

# Create the static library from the output_handler source file
add_library(output_handler output_handler.c)

# Include the current source directory for header file access
# Since it is PRIVATE, the includes must include the path to the headers
target_include_directories(output_handler PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
# Link utils because output_handler depends on utils
target_link_libraries(output_handler PRIVATE utils error_handler counter)

# Print a status message during CMake configuration to confirm output_handler is processed
message(STATUS "(${PROJECT_NAME}) output_handler configured: Added as static library")
# Optionally, you can set properties or compile options specific to this module