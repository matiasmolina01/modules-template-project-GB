# -----------------------------------------------------
# src/token/CMakeLists.txt
# CMakeLists.txt for token 
#
# This file defines the token static library. It is compiled independently
# and can be tested separately.
# It is included from the top-level CMakeLists.txt via `add_subdirectory(src/token)`.
# The module is compiled as a static library and can be linked by main programs or tests.
# -----------------------------------------------------

# Create the static library from the token source file
add_library(token token.c)

# Include the current source directory for header file access
# Since it is PRIVATE, the includes must include the path to the headers
target_include_directories(token PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
# Link utils because token depends on utils
target_link_libraries(token PRIVATE utils)

# Print a status message during CMake configuration to confirm token is processed
message(STATUS "(${PROJECT_NAME}) token configured: Added as static library")
# Optionally, you can set properties or compile options specific to this module