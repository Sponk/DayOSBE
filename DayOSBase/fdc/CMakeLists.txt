file(GLOB_RECURSE HEADERS *.h)
file(GLOB_RECURSE SOURCES *.c*)

add_executable(fdc.drv ${SOURCES} ${HEADERS})
target_link_libraries(fdc.drv dayos m)