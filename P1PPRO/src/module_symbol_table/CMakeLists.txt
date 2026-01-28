# -----------------------------------------------------
# src/module_symbol_table/CMakeLists.txt
# CMakeLists.txt for Module_symbol_table 
#
# This file defines the module_symbol_table static library. It is compiled independently
# and can be tested separately.
# It is included from the top-level CMakeLists.txt via `add_subdirectory(src/module_symbol_table)`.
# The module is compiled as a static library and can be linked by main programs or tests.
# -----------------------------------------------------

# Create the static library from the module_symbol_table source file
add_library(module_symbol_table module_symbol_table.c)

# Include the current source directory for header file access
# Since it is PRIVATE, the includes must include the path to the headers
target_include_directories(module_symbol_table PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
# Link utils because module_symbol_table depends on utils
target_link_libraries(module_symbol_table PRIVATE utils)

# Print a status message during CMake configuration to confirm module_symbol_table is processed
message(STATUS "(${PROJECT_NAME}) Module_symbol_table configured: Added as static library")
# Optionally, you can set properties or compile options specific to this module