# Source arangement
This directory contains the complete code of the operating system. The following tree provides a detailed overview.

```
├── boot              ← things related to the early boot stage
│   ├── boot.s
│   └── grub.cfg      ← GRUB configuration
├── docs              ← documentation stuff
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
