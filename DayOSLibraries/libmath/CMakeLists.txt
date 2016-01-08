 

file(GLOB_RECURSE HEADERS *.h)
file(GLOB_RECURSE SOURCES *.c*)

set(CMAKE_C_FLAGS "-m32 -Wall -g -fstack-protector-all -nostdinc")

include_directories("include" ${DAYOS_KERNEL_INCLUDE})
add_library(m STATIC ${SOURCES} ${HEADERS})

install(TARGETS m DESTINATION "${CMAKE_INSTALL_PREFIX}/usr/lib")
install(FILES ${HEADERS} DESTINATION "${CMAKE_INSTALL_PREFIX}/usr/include")