# -----------------------------------------------------
# src/scanner/CMakeLists.txt
# CMakeLists.txt for scanner 
#
# This file defines the scanner static library. It is compiled independently
# and can be tested separately.
# It is included from the top-level CMakeLists.txt via `add_subdirectory(src/scanner)`.
# The module is compiled as a static library and can be linked by main programs or tests.
# -----------------------------------------------------

# Create the static library from the scanner source file
add_library(scanner scanner.c)

# Include the current source directory for header file access
# Since it is PRIVATE, the includes must include the path to the headers
target_include_directories(scanner PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
# Link utils because scanner depends on utils
target_link_libraries(scanner PRIVATE utils error_handler counter)

# Print a status message during CMake configuration to confirm scanner is processed
message(STATUS "(${PROJECT_NAME}) scanner configured: Added as static library")
# Optionally, you can set properties or compile options specific to this module