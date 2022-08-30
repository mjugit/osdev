## i686 OS
An operating system for the i686 architecture, developed from scratch. Use a cross-compiler for the target architecture to build the code. Instructions on how to obtain one can be found in the `Toolchain` directory. The builds have only been done on Linux so far. Whether everything can be done smoothly under Windows as well, I don't know. It may be doable, but don't count on it.

## Getting started
As soon as you have the toolchain on your computer, you are ready for the build. 

1. Currently the builds are handled via the `makefile` in the `src` folder. Depending on where you installed the toolchain, you may need to adjust some of the variables at the beginning of the file. 
2. Call `make` when you are in the `src` folder to create an ISO file. You can then burn it to a USB stick or use it in a VM to boot the system. The ISO file can be found under `build/iso/` if everything worked.
