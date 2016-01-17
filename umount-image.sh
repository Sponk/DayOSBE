#!/bin/sh

if [ -d img ]; then
	sudo umount img/
	sudo losetup -D
fi
