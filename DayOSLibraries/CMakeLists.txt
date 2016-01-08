cmake_minimum_required(VERSION 2.8.0)
 
set(CMAKE_MODULE_PATH
  ${CMAKE_SOURCE_DIR}/CMake
  ${CMAKE_MODULE_PATH}
)

set(ARCH x86)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED on)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED on)

add_subdirectory(libmath)
add_subdirectory(libdayos)
add_subdirectory(crt0)
add_subdirectory(libcxxrt)
#add_subdirectory(libustl)