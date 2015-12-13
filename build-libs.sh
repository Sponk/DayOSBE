#!/bin/sh

export TARGET=i686-pc-dayos
export PREFIX=$PWD/rootsys
export PATH=$PATH:$PREFIX
export DAYOS_DIR=$PWD/DayOS

## Bootstrap libdayos and crt0
if [ ! -d "dayoslibs-build" ]; then
	mkdir dayoslibs-build
fi

cd dayoslibs-build
cmake ../DayOSLibraries/ -DDAYOS_KERNEL_INCLUDE=$DAYOS_DIR/kernel/sys -DCMAKE_INSTALL_PREFIX=$PREFIX

make -j8
make install
cd ..
