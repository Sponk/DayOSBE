file(GLOB_RECURSE HEADERS *.h)
file(GLOB_RECURSE SOURCES *.c*)

add_executable(ramdisk.drv ${SOURCES} ${HEADERS})
install(TARGETS ramdisk.drv DESTINATION ${CMAKE_INSTALL_PREFIX}/image/system)

target_link_libraries(ramdisk.drv dayos m)