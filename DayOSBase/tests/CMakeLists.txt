
add_executable(TestLibDayOS.elf TestLibDayOS.cpp ${CRT0_SRC})
install(TARGETS TestLibDayOS.elf DESTINATION ${CMAKE_INSTALL_PREFIX}/image)
target_link_libraries(TestLibDayOS.elf stdc++ gcc dayos m)

include_directories(${LIBDAYOS_INCLUDE})
