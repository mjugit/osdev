# Source arangement
This directory contains the complete code of the operating system. The following tree provides a detailed overview.

```
├── boot              ← things related to the early boot stage
│   ├── boot.s
│   └── grub.cfg      ← GRUB configuration
├── kmain.c
├── libc              ← c library
│   ├── include
│   │   └── *.h
│   └── *.c
├── libk              ← kernel library
│   ├── include
│   │   └── *.h
│   └── *.c
├── linker.ld         ← linker script
├── makefile          ← build configuration
├── README.md
└── testing           ← unit tests
    ├── example.c
    └── include
        └── utest.h   ← testing library
```

Before you try to start the build, make sure the variables in the `makefile` are set correcty. Read the comments, as they provide valuable information of what you can do. For example:
```
...
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

