#----------------------------------------------------------------
# Generated CMake target import file for configuration "Debug".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "SFML::System" for configuration "Debug"
set_property(TARGET SFML::System APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(SFML::System PROPERTIES
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/lib/libsfml-system-d.3.0.0.dylib"
  IMPORTED_SONAME_DEBUG "@rpath/libsfml-system-d.3.0.dylib"
  )

list(APPEND _IMPORT_CHECK_TARGETS SFML::System )
list(APPEND _IMPORT_CHECK_FILES_FOR_SFML::System "${_IMPORT_PREFIX}/lib/libsfml-system-d.3.0.0.dylib" )

# Import target "SFML::Window" for configuration "Debug"
set_property(TARGET SFML::Window APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(SFML::Window PROPERTIES
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/lib/libsfml-window-d.3.0.0.dylib"
  IMPORTED_SONAME_DEBUG "@rpath/libsfml-window-d.3.0.dylib"
  )

list(APPEND _IMPORT_CHECK_TARGETS SFML::Window )
list(APPEND _IMPORT_CHECK_FILES_FOR_SFML::Window "${_IMPORT_PREFIX}/lib/libsfml-window-d.3.0.0.dylib" )

# Import target "SFML::Network" for configuration "Debug"
set_property(TARGET SFML::Network APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(SFML::Network PROPERTIES
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/lib/libsfml-network-d.3.0.0.dylib"
  IMPORTED_SONAME_DEBUG "@rpath/libsfml-network-d.3.0.dylib"
  )

list(APPEND _IMPORT_CHECK_TARGETS SFML::Network )
list(APPEND _IMPORT_CHECK_FILES_FOR_SFML::Network "${_IMPORT_PREFIX}/lib/libsfml-network-d.3.0.0.dylib" )

# Import target "SFML::Graphics" for configuration "Debug"
set_property(TARGET SFML::Graphics APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(SFML::Graphics PROPERTIES
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/lib/libsfml-graphics-d.3.0.0.dylib"
  IMPORTED_SONAME_DEBUG "@rpath/libsfml-graphics-d.3.0.dylib"
  )

list(APPEND _IMPORT_CHECK_TARGETS SFML::Graphics )
list(APPEND _IMPORT_CHECK_FILES_FOR_SFML::Graphics "${_IMPORT_PREFIX}/lib/libsfml-graphics-d.3.0.0.dylib" )

# Import target "SFML::Audio" for configuration "Debug"
set_property(TARGET SFML::Audio APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(SFML::Audio PROPERTIES
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/lib/libsfml-audio-d.3.0.0.dylib"
  IMPORTED_SONAME_DEBUG "@rpath/libsfml-audio-d.3.0.dylib"
  )

list(APPEND _IMPORT_CHECK_TARGETS SFML::Audio )
list(APPEND _IMPORT_CHECK_FILES_FOR_SFML::Audio "${_IMPORT_PREFIX}/lib/libsfml-audio-d.3.0.0.dylib" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
