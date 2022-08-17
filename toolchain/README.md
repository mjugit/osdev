# Toolchain

To ease development, we will build a separate toolchain for the new operating system.

## Building a cross-compiler
- __PURPOSE__ The cross-compiler will be able to turn source code on the current system into object code for the target system.
- __REQUIRED TOOLS__ Make, [Bison](https://www.gnu.org/software/bison/), [Flex](https://github.com/westes/flex), [GMP](https://gmplib.org/), MPC, [MPFR](https://www.mpfr.org/), [Texinfo](https://www.gnu.org/software/texinfo/)
- __SOURCES__ [binutils](https://ftp.gnu.org/gnu/binutils/), [gcc](https://ftp.gnu.org/gnu/gcc/)

To build the cross-compiler, use the `build-crc.sh` script. In the top section you can specify where the toolchain should be installed. It is strongly recommended not to install it to system directories unless you know what you're doing.

