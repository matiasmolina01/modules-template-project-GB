# -----------------------------------------------------
# src/init/CMakeLists.txt
# CMakeLists.txt for init 
#
# This file defines the init static library. It is compiled independently
# and can be tested separately.
# It is included from the top-level CMakeLists.txt via `add_subdirectory(src/init)`.
# The module is compiled as a static library and can be linked by main programs or tests.
# -----------------------------------------------------

# Create the static library from the init source file
add_library(init init.c)

# Include the current source directory for header file access
# Since it is PRIVATE, the includes must include the path to the headers
target_include_directories(init PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
# Link utils because init depends on utils
target_link_libraries(init PRIVATE utils)

# Print a status message during CMake configuration to confirm init is processed
message(STATUS "(${PROJECT_NAME}) init configured: Added as static library")
# Optionally, you can set properties or compile options specific to this module