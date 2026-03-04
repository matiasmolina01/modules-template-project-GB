# -----------------------------------------------------
# src/sra/CMakeLists.txt
# CMakeLists.txt for sra 
#
# This file defines the sra static library. It is compiled independently
# and can be tested separately.
# It is included from the top-level CMakeLists.txt via `add_subdirectory(src/sra)`.
# The module is compiled as a static library and can be linked by main programs or tests.
# -----------------------------------------------------

# Create the static library from the sra source file
add_library(sra sra.c)

# Include the current source directory for header file access
# Since it is PRIVATE, the includes must include the path to the headers
target_include_directories(sra PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
# Link utils because sra depends on utils
target_link_libraries(sra PRIVATE utils)

# Print a status message during CMake configuration to confirm sra is processed
message(STATUS "(${PROJECT_NAME}) sra configured: Added as static library")
# Optionally, you can set properties or compile options specific to this module