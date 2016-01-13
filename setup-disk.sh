#!/bin/sh

## Create new image!
dd if=/dev/zero of=disk.img bs=512 count=500000

/usr/sbin/fdisk disk.img << EOF
n
p
1
2048
499999
a
w
q
EOF

sudo losetup /dev/loop0 disk.img
sudo losetup /dev/loop1 disk.img -o 1048576

sudo mke2fs /dev/loop1
sudo mount /dev/loop1 /mnt

sudo grub2-install --target=i386-pc --root-directory=/mnt --no-floppy --modules="normal part_msdos ext2 multiboot" /dev/loop0

sync
sudo umount /mnt
sudo losetup -D
