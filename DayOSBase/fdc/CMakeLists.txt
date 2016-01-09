file(GLOB_RECURSE HEADERS *.h)
file(GLOB_RECURSE SOURCES *.c*)

add_executable(fdc.drv ${SOURCES} ${HEADERS} ${CRT0_SRC})
target_link_libraries(fdc.drv dayos m)