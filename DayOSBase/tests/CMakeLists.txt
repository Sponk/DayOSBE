
add_executable(tests.elf TestLibDayOS.cpp)
install(TARGETS tests.elf DESTINATION ${CMAKE_INSTALL_PREFIX}/image)
target_link_libraries(tests.elf stdc++ gcc dayos m)

include_directories(${LIBDAYOS_INCLUDE})
