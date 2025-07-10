# TrycatchOS
This Linux distribution is a developer-focused, solution-oriented platform that simplifies setup by automating dependencies and packaging, providing a stable and efficient environment for coding and development.

```bash
sudo apt update && sudo apt upgrade
sudo apt install build-essential libncurses-dev bison flex libssl-dev libelf-dev bc
cd ~/
git clone https://github.com/trycatchh/trycatch-os.git
cd trycatch-os
wget https://cdn.kernel.org/pub/linux/kernel/v6.x/linux-6.1.21.tar.xz
tar -xf linux-6.1.21.tar.xz
rm -rf linux-6.1.21.tar.xz
cd linux-6.1.21
make mrproper
make defconfig
mkdir ../kernel-modules
make modules_install INSTALL_MOD_PATH=../kernel-modules
make KCFLAGS=-Wno-error -j$(nproc)
make modules_install INSTALL_MOD_PATH=../kernel-modules
cd ..
mkdir -p initramfs/{bin,sbin,etc,proc,sys,usr/bin,dev}
chmod +x initramfs/init
sudo mknod -m 622 initramfs/dev/console
sudo mknod -m 666 initramfs/dev/null c 1 3
cd initramfs
find . | cpio -H newc -o > ../initramfs.cpio
cd ..
gzip initramfs.cpio
grub-mkrescue -o custom_linux.iso iso
```
