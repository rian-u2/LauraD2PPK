#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "Laura::Laura++" for configuration "Release"
set_property(TARGET Laura::Laura++ APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(Laura::Laura++ PROPERTIES
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/libLaura++.so.3.6.0"
  IMPORTED_SONAME_RELEASE "libLaura++.so.3"
  )

list(APPEND _IMPORT_CHECK_TARGETS Laura::Laura++ )
list(APPEND _IMPORT_CHECK_FILES_FOR_Laura::Laura++ "${_IMPORT_PREFIX}/lib/libLaura++.so.3.6.0" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
