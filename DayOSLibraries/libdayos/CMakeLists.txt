 

file(GLOB_RECURSE HEADERS *.h)
file(GLOB_RECURSE SOURCES *.c*)

set(CMAKE_C_FLAGS "-m32 -Wall -g -fstack-protector-all -nostdinc")

include_directories("include" ${DAYOS_KERNEL_INCLUDE})
add_library(dayos STATIC ${SOURCES} ${HEADERS})

install(TARGETS dayos DESTINATION "${CMAKE_INSTALL_PREFIX}/usr/lib")
install(DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/include" DESTINATION "${CMAKE_INSTALL_PREFIX}/usr")