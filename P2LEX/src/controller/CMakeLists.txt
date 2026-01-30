# -----------------------------------------------------
# src/controller/CMakeLists.txt
# CMakeLists.txt for controller 
#
# This file defines the controller static library. It is compiled independently
# and can be tested separately.
# It is included from the top-level CMakeLists.txt via `add_subdirectory(src/controller)`.
# The module is compiled as a static library and can be linked by main programs or tests.
# -----------------------------------------------------

# Create the static library from the controller source file
add_library(controller controller.c)

# Include the current source directory for header file access
# Since it is PRIVATE, the includes must include the path to the headers
target_include_directories(controller PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
# Link utils because controller depends on utils
target_link_libraries(controller PRIVATE utils)

# Print a status message during CMake configuration to confirm controller is processed
message(STATUS "(${PROJECT_NAME}) controller configured: Added as static library")
# Optionally, you can set properties or compile options specific to this module