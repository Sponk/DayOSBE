#!/bin/sh -e
#./build-complete.sh

if [ ! -d "build" ]; then
	mkdir build
fi


if [ ! -d "build-libs" ]; then
	mkdir build-libs
fi

#cd build-libs
#cmake ../DayOSLibraries -DCMAKE_INSTALL_PREFIX=$PREFIX -DCMAKE_TOOLCHAIN_FILE=$PWD/../CMake/DayOS.cmake -DDAYOS_KERNEL_INCLUDE=$PWD/../DayOSKernel/sys
#make -j8 install
#cd ..

#cd build
#cmake ../ -DCMAKE_INSTALL_PREFIX=$PREFIX -DCMAKE_TOOLCHAIN_FILE=$PWD/../CMake/DayOS.cmake
#make -j8 install
#cd ..

./build-image.sh
qemu-system-i386 -m 512 -hda disk.img -name "DayOS" -serial stdio