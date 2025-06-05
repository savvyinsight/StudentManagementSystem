# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\StudentManagementSystem_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\StudentManagementSystem_autogen.dir\\ParseCache.txt"
  "StudentManagementSystem_autogen"
  )
endif()
