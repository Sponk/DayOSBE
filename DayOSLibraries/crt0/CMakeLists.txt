
set(CMAKE_C_FLAGS -m32 -Wall -g -fstack-protector-all -nostdinc -std=c11)
#add_library(crt0.o OBJECT crt0.c)
#add_library(crtbegin.o OBJECT cpp_crt.c)
#add_library(crtend.o OBJECT empty.c)

set(INCLUDES -I${DAYOS_KERNEL_INCLUDE} -I${CMAKE_CURRENT_SOURCE_DIR}/../libdayos/include -I${DAYOS_KERNEL_INCLUDE})

add_custom_target(crt0 ALL ${CMAKE_C_COMPILER} ${CMAKE_C_FLAGS} ${INCLUDES} -o "${CMAKE_BINARY_DIR}/crt0.o" -c "${CMAKE_CURRENT_SOURCE_DIR}/crt0.c")
add_custom_target(crtbegin ALL ${CMAKE_C_COMPILER} ${CMAKE_C_FLAGS} ${INCLUDES} -o "${CMAKE_BINARY_DIR}/crtbegin.o" -c "${CMAKE_CURRENT_SOURCE_DIR}/crtbegin.c")
add_custom_target(crtend ALL ${CMAKE_C_COMPILER} ${CMAKE_C_FLAGS} ${INCLUDES} -o "${CMAKE_BINARY_DIR}/crtend.o" -c "${CMAKE_CURRENT_SOURCE_DIR}/crtend.c")

install(FILES ${CMAKE_BINARY_DIR}/crt0.o ${CMAKE_BINARY_DIR}/crtbegin.o ${CMAKE_BINARY_DIR}/crtend.o DESTINATION "${CMAKE_INSTALL_PREFIX}/usr/lib")