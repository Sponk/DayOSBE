
set(CMAKE_C_FLAGS "-m32 -Wall -g -fstack-protector-all -nostdinc -std=c11")
add_library(crt0 STATIC crt0.c)

include_directories(
${DAYOS_KERNEL_INCLUDE}
"${CMAKE_CURRENT_SOURCE_DIR}/../libdayos/include" 
${DAYOS_KERNEL_INCLUDE})

#add_library(crtbegin.o OBJECT cpp_crt.c)
#add_library(crtend.o OBJECT empty.c)

#set(INCLUDES -I${DAYOS_KERNEL_INCLUDE} -I${CMAKE_CURRENT_SOURCE_DIR}/../libdayos/include -I${DAYOS_KERNEL_INCLUDE})

#add_custom_target(crt0 ALL ${CMAKE_C_COMPILER} ${CMAKE_C_FLAGS} ${INCLUDES} -o "${CMAKE_BINARY_DIR}/crt0.o" -c "${CMAKE_CURRENT_SOURCE_DIR}/crt0.c")
add_custom_target(crti ALL ${CMAKE_C_COMPILER} -m32 -o "${CMAKE_BINARY_DIR}/crti.o" -c "${CMAKE_CURRENT_SOURCE_DIR}/crti.S")
add_custom_target(crtn ALL ${CMAKE_C_COMPILER} -m32 -o "${CMAKE_BINARY_DIR}/crtn.o" -c "${CMAKE_CURRENT_SOURCE_DIR}/crtn.S")

install(TARGETS crt0 DESTINATION ${CMAKE_INSTALL_PREFIX}/usr/lib)
install(FILES ${CMAKE_BINARY_DIR}/crti.o ${CMAKE_BINARY_DIR}/crtn.o DESTINATION "${CMAKE_INSTALL_PREFIX}/usr/lib")