# -----------------------------------------------------
# src/global_context/CMakeLists.txt
# CMakeLists.txt for global_context 
#
# This file defines the global_context static library. It is compiled independently
# and can be tested separately.
# It is included from the top-level CMakeLists.txt via `add_subdirectory(src/global_context)`.
# The module is compiled as a static library and can be linked by main programs or tests.
# -----------------------------------------------------

# Create the static library from the global_context source file
add_library(global_context global_context.c)

# Include the current source directory for header file access
# Since it is PRIVATE, the includes must include the path to the headers
target_include_directories(global_context PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
# Link utils because global_context depends on utils
target_link_libraries(global_context PRIVATE utils error_handler counter)

# Print a status message during CMake configuration to confirm global_context is processed
message(STATUS "(${PROJECT_NAME}) global_context configured: Added as static library")
# Optionally, you can set properties or compile options specific to this module