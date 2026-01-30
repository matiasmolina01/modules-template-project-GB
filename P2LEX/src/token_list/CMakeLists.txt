# -----------------------------------------------------
# src/token_list/CMakeLists.txt
# CMakeLists.txt for token_list 
#
# This file defines the token_list static library. It is compiled independently
# and can be tested separately.
# It is included from the top-level CMakeLists.txt via `add_subdirectory(src/token_list)`.
# The module is compiled as a static library and can be linked by main programs or tests.
# -----------------------------------------------------

# Create the static library from the token source file
add_library(token_list token_list.c)

# Include the current source directory for header file access
# Since it is PRIVATE, the includes must include the path to the headers
target_include_directories(token_list PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
# Link utils because token_list depends on utils
target_link_libraries(token_list PRIVATE utils)

# Print a status message during CMake configuration to confirm token_list is processed
message(STATUS "(${PROJECT_NAME}) token_list configured: Added as static library")
# Optionally, you can set properties or compile options specific to this module