# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\wps_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\wps_autogen.dir\\AutogenUsed_Debug.txt"
  "CMakeFiles\\wps_autogen.dir\\AutogenUsed_RelWithDebInfo.txt"
  "CMakeFiles\\wps_autogen.dir\\AutogenUsed_Release.txt"
  "CMakeFiles\\wps_autogen.dir\\ParseCache.txt"
  "CMakeFiles\\wps_autogen.dir\\ParseCache_Debug.txt"
  "CMakeFiles\\wps_autogen.dir\\ParseCache_RelWithDebInfo.txt"
  "CMakeFiles\\wps_autogen.dir\\ParseCache_Release.txt"
  "wps_autogen"
  )
endif()

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Release")
  file(REMOVE_RECURSE
  "CMakeFiles\\wps_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\wps_autogen.dir\\AutogenUsed_Debug.txt"
  "CMakeFiles\\wps_autogen.dir\\AutogenUsed_RelWithDebInfo.txt"
  "CMakeFiles\\wps_autogen.dir\\AutogenUsed_Release.txt"
  "CMakeFiles\\wps_autogen.dir\\ParseCache.txt"
  "CMakeFiles\\wps_autogen.dir\\ParseCache_Debug.txt"
  "CMakeFiles\\wps_autogen.dir\\ParseCache_RelWithDebInfo.txt"
  "CMakeFiles\\wps_autogen.dir\\ParseCache_Release.txt"
  "wps_autogen"
  )
endif()

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "RelWithDebInfo")
  file(REMOVE_RECURSE
  "CMakeFiles\\wps_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\wps_autogen.dir\\AutogenUsed_Debug.txt"
  "CMakeFiles\\wps_autogen.dir\\AutogenUsed_RelWithDebInfo.txt"
  "CMakeFiles\\wps_autogen.dir\\AutogenUsed_Release.txt"
  "CMakeFiles\\wps_autogen.dir\\ParseCache.txt"
  "CMakeFiles\\wps_autogen.dir\\ParseCache_Debug.txt"
  "CMakeFiles\\wps_autogen.dir\\ParseCache_RelWithDebInfo.txt"
  "CMakeFiles\\wps_autogen.dir\\ParseCache_Release.txt"
  "wps_autogen"
  )
endif()
