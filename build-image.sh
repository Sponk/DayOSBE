#!/bin/sh
rm ./ramdisk.tar

# Ramdisk bauen
cp init.cfg rootsys/image
cd rootsys/image
tar -cvf ../../ramdisk.tar .
cd ../..

# Image einhängen.
mkdir -p img/
sudo losetup /dev/loop1 disk.img -o 1048576
#sudo mount -o loop disk.img.bck img/
sudo mount /dev/loop1 ./img/

# Ordner erstellen
sudo mkdir -p img/dayos/bin
sudo mkdir -p img/boot/grub2

# Den DayOS-Kernel auf das Image kopieren.
sudo cp rootsys/kernel img/dayos/bin
# Die RAM-Disk kopieren
sudo cp ramdisk.tar img/dayos
# Die menu.lst auf das Image kopieren.
sudo cp scripts/grub/grub.cfg img/boot/grub2/grub.cfg
# sudo cp scripts/grub/splash.xpm.gz img/boot/grub/splash.xpm.gz

# einen Moment warten
sleep 1
# Image aushängen.
sudo umount img/

rmdir img/
sync
