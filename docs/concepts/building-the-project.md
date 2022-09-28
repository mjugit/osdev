# Building the project

## Whats the thing with the cross-compiler?
A cross compiler is able to translate the code on the development computer into machine language for another architecture. Here's an example: I assume that almost everyone uses a 64 bit machine these days. What you actually want to do then, is building an image for 32 bits on a 64 bit machine. We could pass a hell of command line switches to the compiler for each build, for achieving this, but that would make the whole configuration pretty nasting opening another possible source of error. What we instead intent to do is building a toolchain for the target architecture.

- How you can compile the cross-compiler from source is explained [here](../../toolchain/README.md).

## How the build process works
Creating a bootable disk from all those source files may seem chaotic at first, but it is not as hard as it seems. You may have noticed a file named `makefile` in several project directories. These contain the build configuration for all code underneath the directory they're in, as long as it doesn't have a `makefile` on its own. Inside the makefile you usually have some variables at the top containing switches or program names, followed by directory definitions. Since `make` builds the first target, if no other target name is passed, the most complete one is always the first. Behind it you'll find rules for the separate components.

- The documentation for `make` can be found on GNU's official servers [here](https://www.gnu.org/software/make/).

### What does actually happen during the build? 
Well, roughly said, object code is created from each source file, which is lateron linked into a binary, that can be loaded by the bootloader (in our case GRUB). This binary is then written to a bootable disk image.

1. The two main libraries `libc` and `libk` contain the essentials of the whole system. Many other libraries use their functions, so it feels natural to start with them. Two directories will be creatted under source, having the name of the respective library. All object code is placed there.
2. The contents of the `boot` directory is assembled and placed in a directory `build/boot`.
3. The main kernel code in `kmain.c` is build. Its object code also resides in `libk`.
4. The kernel links all the previously created object code to a executable, according to the specified options in `linker.ld`. The binary can be found under `build/kernel.bin`.
5. The directory `build/iso` is created to prepare the structure of the ISO-image. The kernel executable and the GRUB configuration is placed there respectively.
6. Finally `grub-mkrescue` creates the ISO-file `build/release.iso` that you can boot.
