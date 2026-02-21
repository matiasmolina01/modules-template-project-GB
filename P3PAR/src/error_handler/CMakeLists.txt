# -----------------------------------------------------
# src/error_handler/CMakeLists.txt
# CMakeLists.txt for error_handler 
#
# This file defines the error_handler static library. It is compiled independently
# and can be tested separately.
# It is included from the top-level CMakeLists.txt via `add_subdirectory(src/error_handler)`.
# The module is compiled as a static library and can be linked by main programs or tests.
# -----------------------------------------------------

# Create the static library from the error_handler source file
add_library(error_handler error_handler.c)

# Include the current source directory for header file access
# Since it is PRIVATE, the includes must include the path to the headers
target_include_directories(error_handler PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
# Link utils because error_handler depends on utils
target_link_libraries(error_handler PRIVATE utils counter)

# Print a status message during CMake configuration to confirm error_handler is processed
message(STATUS "(${PROJECT_NAME}) error_handler configured: Added as static library")
# Optionally, you can set properties or compile options specific to this module