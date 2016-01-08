file(GLOB_RECURSE HEADERS *.h)
file(GLOB_RECURSE SOURCES *.c*)

#set(CMAKE_C_FLAGS "-nostdlib")
add_executable(vfs.elf ${SOURCES} ${HEADERS})
install(TARGETS vfs.elf DESTINATION ${CMAKE_INSTALL_PREFIX}/image)

target_link_libraries(vfs.elf dayos m)