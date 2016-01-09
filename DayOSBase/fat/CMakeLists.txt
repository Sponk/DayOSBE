file(GLOB_RECURSE HEADERS *.h)
file(GLOB_RECURSE SOURCES *.c*)

add_executable(fat.drv ${SOURCES} ${HEADERS} ${CRT0_SRC})
target_link_libraries(fat.drv dayos m)