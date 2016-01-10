file(GLOB_RECURSE HEADERS *.h)
file(GLOB_RECURSE SOURCES *.c*)

add_executable(ext2.drv ${SOURCES} ${HEADERS} ${CRT0_SRC})
target_link_libraries(ext2.drv dayos m)
include_directories(${LIBDAYOS_INCLUDE})