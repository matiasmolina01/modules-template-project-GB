# -----------------------------------------------------
# src/parser/CMakeLists.txt
# CMakeLists.txt for parser 
#
# This file defines the parser static library. It is compiled independently
# and can be tested separately.
# It is included from the top-level CMakeLists.txt via `add_subdirectory(src/parser)`.
# The module is compiled as a static library and can be linked by main programs or tests.
# -----------------------------------------------------

# Create the static library from the parser source file
add_library(parser parser.c)

# Include the current source directory for header file access
# Since it is PRIVATE, the includes must include the path to the headers
target_include_directories(parser PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
# Link utils because parser depends on utils
target_link_libraries(parser PRIVATE utils)

# Print a status message during CMake configuration to confirm parser is processed
message(STATUS "(${PROJECT_NAME}) parser configured: Added as static library")
# Optionally, you can set properties or compile options specific to this module