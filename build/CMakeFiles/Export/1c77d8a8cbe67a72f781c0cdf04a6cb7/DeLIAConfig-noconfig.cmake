#----------------------------------------------------------------
# Generated CMake target import file.
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "DeLIA" for configuration ""
set_property(TARGET DeLIA APPEND PROPERTY IMPORTED_CONFIGURATIONS NOCONFIG)
set_target_properties(DeLIA PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_NOCONFIG "CXX"
  IMPORTED_LOCATION_NOCONFIG "${_IMPORT_PREFIX}/DeLIA_lib/libDeLIA.a"
  )

list(APPEND _cmake_import_check_targets DeLIA )
list(APPEND _cmake_import_check_files_for_DeLIA "${_IMPORT_PREFIX}/DeLIA_lib/libDeLIA.a" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
