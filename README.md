# An operating system from scratch

This is an operating system for the i686 architecture, programmed from scratch. It requires a BIOS environment to run, as it does not have UEFI support at this time. We are still at a very early stage of development and do not have a stable version. If you want to try out the system, you have to build the code yourself (see the information under 'Getting started' or in the `toolchain` directory).

## About the project

This is not a professionally developed operating system, but more of a hobby project. Whoever is interested in participating is always welcome. I am also always grateful for tips and questions, since they make me rethink specific details.

## Getting started

What you can download here is only source code, but the compilation is fully automated. Afterwards, a bootable `*.iso` file will be created under `build`.  

### Prerequisites

For the build a cross compiler is necessary. With its help, the image for the target architecture can be created, independent of the build system. A detailed description of how to obtain one can be found in the `toolchain` directory. 

### Building the image

Using the terminal, change to the `src` folder and run `make` to create an image. Make sure you have set up your cross compiler properly! Depending on where you've installed it and wheter or not you have it in your `PATH`, you might have to adjust some paths at the top of the `src/makefile`.

Note: During development, you typically create an image more than once. Be sure to run `make clean` between builds to remove the legacy of the last one. After that `make` will run in a clean environment.

## Roadmap

At the moment, the focus is on developing an MVP:

- [x] Boot the computer
- [x] Simple functions for graphics output
- [x] Unit testing mechanism
- [ ] Fundamentals of the libc
- [ ] Interrupt handling
- [ ] Keyboard input
- [ ] Dynamic memory management
- [ ] Simple shell

## License

The project is distributed under the 'BSD 3-Clause License'. Have a look into the LICENSE file for more information.

## Acknowledgements

- The [OSdev Wiki](https://wiki.osdev.org/Main_Page) for providing the probably most valuable collection of resources on operating system development out there.
- The contributors and maintainers of the [minunit project](https://github.com/siu/minunit) for their ingeniously simple unit testing techniques. Our own testing solution is heavily inspired from them.
- The many people on [Stack Overflow](https://stackoverflow.com/) who answered my questions.

