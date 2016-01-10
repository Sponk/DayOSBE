file(GLOB_RECURSE HEADERS *.h)
file(GLOB_RECURSE SOURCES *.c*)

add_executable(uname ${SOURCES} ${HEADERS} ${CRT0_SRC})
target_link_libraries(uname dayos m)

install(TARGETS uname DESTINATION ${CMAKE_INSTALL_PREFIX}/image)
include_directories(${LIBDAYOS_INCLUDE})