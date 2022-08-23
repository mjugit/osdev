# Toolchain

Preparing a separate toolchain for the new operating system will ease the development process. Imagine it as a toolbox, we prepare for the later work. For the start, we begin by preparing a cross-compiler as well as some binary tools.

- The __purpose__ of the cross-compiler is to enable us building software for a different machine, than we are developing on. In our case it targets the generic i686-elf architecture. Using a designated compiler instead of providing a hell of command line switches for each build, can take away some traps and pitfalls in advance. On top of that it minimizes the risk of messing something up because of a typo.

- Building a compiler __requires__ a set of tools and libraries beeing installed on the development machine. If you have ever built some development tools on your own, you might recognize some of them. Make sure you have these installed! The build process takes some time and it would be frustrating to find out you missed something towards the end. 
These are the required tools: _Make, [Bison](https://www.gnu.org/software/bison/), [Flex](https://github.com/westes/flex), [GMP](https://gmplib.org/), MPC, [MPFR](https://www.mpfr.org/), [Texinfo](https://www.gnu.org/software/texinfo/)_

- Finally we need the __source code__ that is to build. Download the [binutils](https://ftp.gnu.org/gnu/binutils/) and [gcc](https://ftp.gnu.org/gnu/gcc/) source code from the public GNU repository. Even though many different versions are offered there, experience has shown that the newer ones are usually the better choice. You can find them on the bottom of their respective page.

## Building the toolchain

Before you start, make sure you meet the requirements described above. Then decide where your new compiler should be installed. Although it sounds tempting, it should not end up in any system directory, rather somewhere in your home folder.

```sh
# This is where the tools will end up
export PREFIX="$HOME/tools/crc"
export TARGET=i686-elf
# Add the new installation to the PATH variable
# since it is required for the gcc build
export PATH="$PREFIX/bin:$PATH"
```

__As a reminder:__ Building a compiler is a complicated process, if not for the developer, then for the compiler. It is essential that each step is completed correctly. Do not skip any, do not omit any option. Even if the build passes, there may be problems later.

### Building binutils

Before you start issuing the following commands, extract the binutils source directory. If you put it into the `toolchain` folder, you should end up with something like `toolchain/binutils-x.y.z`.

```sh
# Enter the directory where you put the sources
cd $HOME/code/osdev/toolchain
 
mkdir build-binutils
cd build-binutils

../binutils-x.y.z/configure \
  --target=$TARGET \
  --prefix="$PREFIX" \
  --with-sysroot \
  --disable-nls \
  --disable-werror

make
make install
```

### Building gcc

After finishing the binutils build, we can continue with gcc. Since gcc relies on the just built assembler, let's check if it was installed properly:

```sh
which -- $TARGET-as
```

If the installation is found, we can safely continue with the build of the gcc.

```sh
# Enter the directory where you put the sources
cd $HOME/code/osdev/toolchain
 
mkdir build-gcc
cd build-gcc

../gcc-x.y.z/configure 
  --target=$TARGET \
  --prefix="$PREFIX" \
  --disable-nls \
  --enable-languages=c,c++ \
  --without-headers

make all-gcc
make all-target-libgcc
make install-gcc
make install-target-libgcc
```

### Verifying the installation

After completing the previous steps you should have you own compiler. Remember that you cannot use it, to build normal C programs. There are no standard headers available (with a few exceptions) and no C runtime (we need to provide these on our own later). 

Let's verify whether the installation was successfull by querying gcc's version.

```sh
# The compiler's filename is i686-elf-gcc
$HOME/tools/crc/bin/$TARGET-gcc --version
```
You have everything you need to get started now.