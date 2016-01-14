cmake_minimum_required(VERSION 2.8.0)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED on)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED on)

project(DayOSBase)

set(CMAKE_MODULE_PATH
  ${CMAKE_SOURCE_DIR}/CMake
  ${CMAKE_MODULE_PATH}
)

set(ASM_EXTENSION *.S)
set(CMAKE_C_FLAGS "-Wall") # -pedantic-errors")
set(CMAKE_CXX_FLAGS "-fno-use-cxa-atexit -Wall -Wextra -pedantic-errors")
set(CRT0_SRC ${CMAKE_CURRENT_SOURCE_DIR}/../DayOSLibraries/crt0/crt0.c)

add_subdirectory(init)
add_subdirectory(shell)
add_subdirectory(tty)
add_subdirectory(vfs)
add_subdirectory(ramdisk)
add_subdirectory(uname)