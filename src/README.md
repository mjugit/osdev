# Source arangement
The source code is organized thematically. Inside the libc folder no code should end up that is only interesting for the kernel. Conversely, generally useful things should not be available exclusively to the kernel.

```
├── boot         // things related to the early boot stage
├── libc         // libc implementation
├── libk         // kernel library
├── linker.ld    // linker script
├── kmain.c      // kernel entry code
├── makefile     // build configuration
└── README.md
```

Before you try to start the build, make sure the variables in the `makefile` are set correcty. Also pay attention to the comments:
```makefile
# Assembler options
#   Get by absolute path
# AS = $$HOME/tools/crc/bin/i686-elf-as
#   or - if you have it in your PATH -
AS = i686-elf-as
...
```

# Untangling the build process

Since the build process may seem quite complex, here is a brief list of what happens.

1. At the beginning the object code of the libraries `libc` and `libk` is generated. The structure of the `src` folder is mirrored in `build` and the object files are inserted respectively.
2. The code in `boot` is assembled almost simultaneously to object code. Regarding the destination folders, the same applies like mentioned above.
3. The startup code for the kernel from `kmain.c` is converted to object code. The compilation resides in `build/libk` after that.
4. The compiler is now used as a linker. The finished executable `kernel.bin` is located under `build`. It contains the complete kernel.
5. The directory structure for the `*.iso` image is created under `build/iso`. Important contents for the bootable image are copied there, namely `src/boot/grub.cfg` (the configuration of the bootloader) and `build/kernel.bin`.
6. Using `grub-mkrescue` the bootable image `build/release.iso` is created from the directory `build/iso/*`.

