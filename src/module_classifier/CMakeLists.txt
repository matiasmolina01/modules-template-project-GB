# -----------------------------------------------------
# src/module_classifier/CMakeLists.txt
# CMakeLists.txt for Module_classifier 
#
# This file defines the module_classifier static library. It is compiled independently
# and can be tested separately.
# It is included from the top-level CMakeLists.txt via `add_subdirectory(src/module_classifier)`.
# The module is compiled as a static library and can be linked by main programs or tests.
# -----------------------------------------------------

# Create the static library from the module_classifier source file
add_library(module_classifier module_classifier.c)

# Include the current source directory for header file access
# Since it is PRIVATE, the includes must include the path to the headers
target_include_directories(module_classifier PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
# Link utils because module_classifier depends on utils
target_link_libraries(module_classifier PRIVATE utils)

# Print a status message during CMake configuration to confirm module_classifier is processed
message(STATUS "(${PROJECT_NAME}) Module_classifier configured: Added as static library")

# Optionally, you can set properties or compile options specific to this module