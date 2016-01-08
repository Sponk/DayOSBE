file(GLOB_RECURSE HEADERS *.h)
file(GLOB_RECURSE SOURCES *.c*)

add_executable(tty.drv ${SOURCES} ${HEADERS})
install(TARGETS tty.drv DESTINATION ${CMAKE_INSTALL_PREFIX}/image/system)

target_link_libraries(tty.drv dayos m)