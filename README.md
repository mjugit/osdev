## i686 OS
An operating system for the i686 architecture, developed from scratch. Use a cross-compiler for the target architecture to build the code. Instructions on how to obtain one can be found in the `toolchain` directory. The builds have only been done on Linux so far. Whether everything can be done smoothly under Windows as well, I don't know. It may be doable, but don't count on it.

Note that the default branch of this repository is `develop`. ~~Switch to `main` if you're looking for a more stable version.~~

## Building the project
As soon as you have the toolchain on your computer, you are ready for the build. 

1. Currently the builds are handled via the `makefile` in the `src` folder. Depending on where you installed the toolchain, you may need to adjust some of the variables at the beginning of the file. 
2. Call `make` when you are in the `src` folder to build everything an create an ISO file. You can then burn it to a USB stick or use it in a VM to boot the system.

The makefile will output the files in a directory structure like this:
```
├── boot
│   └── ...
├── iso
│   └── boot
│       ├── grub
│       │   └── grub.cfg
│       └── kernel.bin
├── kernel.bin
├── libc
│   └── ...
├── libk
│   └── ...
└── release.iso
```
The directories `boot`, `libk`and `libc`contain the object code of the source files from the directories of the same name in the `src` folder. `release.iso` is a bootable image of the last build.

I explicitly ask you to run `make clean` between two builds, otherwise GRUB will append the new build to the image instead of overwriting it. The image will grow to infinity and the changed code will never be executed. So if new code does not bring any change, you may be affected.
