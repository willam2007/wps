# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\wps_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\wps_autogen.dir\\ParseCache.txt"
  "wps_autogen"
  )
endif()
