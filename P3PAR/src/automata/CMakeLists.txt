# -----------------------------------------------------
# src/automata/CMakeLists.txt
# CMakeLists.txt for automata 
#
# This file defines the automata static library. It is compiled independently
# and can be tested separately.
# It is included from the top-level CMakeLists.txt via `add_subdirectory(src/automata)`.
# The module is compiled as a static library and can be linked by main programs or tests.
# -----------------------------------------------------

# Create the static library from the automata source file
add_library(automata automata.c)

# Include the current source directory for header file access
# Since it is PRIVATE, the includes must include the path to the headers
target_include_directories(automata PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
# Link utils because automata depends on utils
target_link_libraries(automata PRIVATE utils error_handler counter token_handler language)

# Print a status message during CMake configuration to confirm automata is processed
message(STATUS "(${PROJECT_NAME}) automata configured: Added as static library")
# Optionally, you can set properties or compile options specific to this module