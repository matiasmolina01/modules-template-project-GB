# -----------------------------------------------------
# src/language/CMakeLists.txt
# CMakeLists.txt for language 
#
# This file defines the language static library. It is compiled independently
# and can be tested separately.
# It is included from the top-level CMakeLists.txt via `add_subdirectory(src/language)`.
# The module is compiled as a static library and can be linked by main programs or tests.
# -----------------------------------------------------

# Create the static library from the language source file
add_library(language language.c)

# Include the current source directory for header file access
# Since it is PRIVATE, the includes must include the path to the headers
target_include_directories(language PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
# Link utils because language depends on utils
target_link_libraries(language PRIVATE utils error_handler counter automata)

# Print a status message during CMake configuration to confirm language is processed
message(STATUS "(${PROJECT_NAME}) language configured: Added as static library")
# Optionally, you can set properties or compile options specific to this module