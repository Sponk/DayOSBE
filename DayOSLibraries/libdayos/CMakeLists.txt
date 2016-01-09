 

file(GLOB_RECURSE HEADERS *.h)
file(GLOB_RECURSE SOURCES *.c*)
file(GLOB_RECURSE ASM_SOURCES *.S)

enable_language(C ASM)

set(CMAKE_C_FLAGS "-Wall -g -fstack-protector-all -nostdinc") # -pedantic-errors")

include_directories("include" ${DAYOS_KERNEL_INCLUDE})
add_library(dayos STATIC ${SOURCES} ${ASM_SOURCES} ${HEADERS})

install(TARGETS dayos DESTINATION "${CMAKE_INSTALL_PREFIX}/usr/lib")
install(DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/include" DESTINATION "${CMAKE_INSTALL_PREFIX}/usr")