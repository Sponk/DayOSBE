project(DayOSFull)
cmake_minimum_required(VERSION 3.3)

set(DAYOS_KERNEL_INCLUDE ${CMAKE_SOURCE_DIR}/DayOSKernel/sys)
set(LIBRARY_OUTPUT_DIRECTORY ${CMAKE_INSTALL_PREFIX}/usr/lib)

add_subdirectory(DayOSLibraries)
add_subdirectory(DayOSBase)
add_subdirectory(DayOSKernel)