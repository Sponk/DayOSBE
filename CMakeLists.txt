project(DayOSFull)
cmake_minimum_required(VERSION 3.3)

set(DAYOS_KERNEL_INCLUDE ${CMAKE_SOURCE_DIR}/DayOSKernel/sys)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/image)

set(LIBDAYOS_INCLUDE "${CMAKE_SOURCE_DIR}/DayOSLibraries/libdayos/include")

set(DOXYGEN_SOURCEDIRS "${LIBDAYOS_INCLUDE} ${DAYOS_KERNEL_INCLUDE}")

find_package(Doxygen)
if(DOXYGEN_FOUND)
  configure_file(${CMAKE_CURRENT_SOURCE_DIR}/documentation/Doxyfile.in ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile @ONLY)
  add_custom_target(doc
	${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile
	WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
	COMMENT "Generating API documentation with Doxygen" VERBATIM
  )
endif(DOXYGEN_FOUND)

add_subdirectory(DayOSLibraries)
add_subdirectory(DayOSBase)
add_subdirectory(DayOSKernel)

add_custom_target(qemu-image COMMAND sh ${CMAKE_SOURCE_DIR}/test-stdio-hd.sh WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})
add_dependencies(qemu-image kernel graphicstest.elf tests.elf dayos uname init.elf shell.elf tty.drv vfs.elf ramdisk.drv)