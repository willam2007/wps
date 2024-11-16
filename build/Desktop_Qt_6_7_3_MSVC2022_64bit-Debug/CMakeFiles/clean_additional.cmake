# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\qqeeeee_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\qqeeeee_autogen.dir\\ParseCache.txt"
  "qqeeeee_autogen"
  )
endif()
