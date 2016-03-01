file(GLOB_RECURSE HEADERS *.h)
file(GLOB_RECURSE SOURCES *.c*)

add_executable(writefile.elf ${SOURCES} ${HEADERS})
target_link_libraries(writefile.elf dayos m)

install(TARGETS writefile.elf DESTINATION ${CMAKE_INSTALL_PREFIX}/image)
include_directories(${LIBDAYOS_INCLUDE})
