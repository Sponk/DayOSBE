project(DayOSFull)
cmake_minimum_required(VERSION 3.3)

set(DAYOS_KERNEL_INCLUDE ${CMAKE_SOURCE_DIR}/DayOSKernel/sys)
set(LIBRARY_OUTPUT_DIRECTORY ${CMAKE_INSTALL_PREFIX}/usr/lib)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/image)

add_subdirectory(DayOSLibraries)
add_subdirectory(DayOSBase)
add_subdirectory(DayOSKernel)

add_custom_target(qemu-image COMMAND sh ${CMAKE_SOURCE_DIR}/test-stdio-hd.sh WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})
add_dependencies(qemu-image kernel dayos init.elf shell.elf tty.drv vfs.elf ramdisk.drv)