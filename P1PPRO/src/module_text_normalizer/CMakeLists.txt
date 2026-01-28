# -----------------------------------------------------
# src/module_text_normalizer/CMakeLists.txt
# CMakeLists.txt for Module_text_normalizer 
#
# This file defines the module_text_normalizer static library. It is compiled independently
# and can be tested separately.
# It is included from the top-level CMakeLists.txt via `add_subdirectory(src/module_text_normalizer)`.
# The module is compiled as a static library and can be linked by main programs or tests.
# -----------------------------------------------------

# Create the static library from the module_text_normalizer source file
add_library(module_text_normalizer module_text_normalizer.c)

# Include the current source directory for header file access
# Since it is PRIVATE, the includes must include the path to the headers
target_include_directories(module_text_normalizer PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
# Link utils because module_text_normalizer depends on utils
target_link_libraries(module_text_normalizer PRIVATE utils)

# Print a status message during CMake configuration to confirm module_text_normalizer is processed
message(STATUS "(${PROJECT_NAME}) Module_text_normalizer configured: Added as static library")
# Optionally, you can set properties or compile options specific to this module