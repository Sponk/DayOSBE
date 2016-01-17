#!/bin/sh

#if [ ! -d "disk.img" ]; then
#	sh -e ./setup-disk.sh
#fi

rm ./ramdisk.tar

mkdir -p rootsys/image/system
cp build/image/kernel rootsys/
cp build/image/uname rootsys/image
cp build/image/*.elf rootsys/image
cp build/image/*.drv rootsys/image/system

cp -r DayOSBase/shell/lisp/ rootsys/image

# Ramdisk bauen
cp init.cfg rootsys/image
cd rootsys/image
tar -cvf ../../ramdisk.tar .
cd ../..

# Image einhängen.
sh ./mount-image.sh

# Ordner erstellen
mkdir -p img/dayos/bin
mkdir -p img/boot/grub2

# Den DayOS-Kernel auf das Image kopieren.
cp rootsys/kernel img/dayos/bin
# Die RAM-Disk kopieren
cp ramdisk.tar img/dayos
# Die menu.lst auf das Image kopieren.
cp scripts/grub/grub.cfg img/boot/grub2/grub.cfg
# sudo cp scripts/grub/splash.xpm.gz img/boot/grub/splash.xpm.gz

# einen Moment warten
sleep 1

# Image aushängen.
#sudo umount img/
#sudo losetup -D

#rmdir img/
sync
