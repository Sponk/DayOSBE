file(GLOB_RECURSE SOURCES src/*.c*)
file(GLOB_RECURSE HEADERS src/*.h)

if(${ARCH} STREQUAL "x86")
	set(ARCHFLAGS "-melf_i386 -T kernel.ld")
	set(CMAKE_C_FLAGS "-m32 -Wall -g -fstack-protector-all -nostdinc")
	set(CMAKE_CXX_FLAGS "-m32 -Wall -g -fstack-protector-all -nostdinc -fno-builtin")
endif()

include_directories("include" "../libdayos/include" ${DAYOS_KERNEL_INCLUDE})
add_library(cxxrt STATIC ${SOURCES} ${HEADERS})

install(TARGETS cxxrt DESTINATION "${CMAKE_INSTALL_PREFIX}/usr/lib")