# -----------------------------------------------------
# src/alphabet/CMakeLists.txt
# CMakeLists.txt for alphabet 
#
# This file defines the alphabet static library. It is compiled independently
# and can be tested separately.
# It is included from the top-level CMakeLists.txt via `add_subdirectory(src/alphabet)`.
# The module is compiled as a static library and can be linked by main programs or tests.
# -----------------------------------------------------

# Create the static library from the alphabet source file
add_library(alphabet alphabet.c)

# Include the current source directory for header file access
# Since it is PRIVATE, the includes must include the path to the headers
target_include_directories(alphabet PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
# Link utils because alphabet depends on utils
target_link_libraries(alphabet PRIVATE utils error_handler counter)

# Print a status message during CMake configuration to confirm alphabet is processed
message(STATUS "(${PROJECT_NAME}) alphabet configured: Added as static library")
# Optionally, you can set properties or compile options specific to this module