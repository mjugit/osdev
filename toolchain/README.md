# Toolchain

To ease development, we will build a separate toolchain for the new operating system. The project targets the i686 architecture. 

## Building a cross-compiler

- __PURPOSE__ The cross-compiler will be able to turn source code on the current system into object code for the target system.
- __REQUIRED TOOLS__ Make, [Bison](https://www.gnu.org/software/bison/), [Flex](https://github.com/westes/flex), [GMP](https://gmplib.org/), MPC, [MPFR](https://www.mpfr.org/), [Texinfo](https://www.gnu.org/software/texinfo/)
- __SOURCES__ [binutils](https://ftp.gnu.org/gnu/binutils/), [gcc](https://ftp.gnu.org/gnu/gcc/)

To build the cross-compiler, use the `build-crc.sh` script. In the top section you can specify where the toolchain should be installed. It is strongly recommended not to install it to system directories unless you know what you're doing.

However, before you execute the script, download the sources and put them into the `toolchain` directory. You will end up with two directories in there: `binutils-x-y-z` and  `gcc-x-y-z`. Now run the `build-crc.sh` (for 'build __cr__oss __c__ompiler') script.
After the script finished running, verify that everythings fine with the installation. If you used the default settings, call the gcc cross-compiler like this:

```sh
$ $HOME/opt/crc/bin/i686-elf-gcc --version
```
```
# Expect some output like this
i686-elf-gcc (GCC) x.y.z
Copyright (C) 20xx Free Software Foundation, Inc.
This is free software; see the source for copying conditions.  There is NO
warranty; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
```
