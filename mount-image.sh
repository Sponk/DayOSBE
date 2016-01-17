#!/bin/sh

if [ ! -d img ]; then
	echo "Mounting image..."
	mkdir -p img/
	sudo losetup /dev/loop1 disk.img -o 1048576
	sudo mount /dev/loop1 ./img/
	echo "Done."
fi
