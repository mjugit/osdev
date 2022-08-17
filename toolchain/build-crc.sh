#!/bin/bash

# Where to install
export PREFIX="$HOME/opt/crc"
# Target architecture
export TARGET=i686-elf
# Add tools to PATH (required for the gcc build)
export PATH="$PREFIX/bin:$PATH"


if [ -d binutils-* ]
then
    echo ":: Start building binutils..."

    BINUTILS_BUILD_DIR="build-binutils"
    BINUTILS_SRC_DIR=$(ls | grep binutils- | awk '{print $1;}')

    if [ -d $BINUTILS_BUILD_DIR ]
    then
	echo "binutils build directory already exists. Skipping."
    else
	mkdir -p $BINUTILS_BUILD_DIR
	cd $BINUTILS_BUILD_DIR
	../${BINUTILS_SRC_DIR}/configure \
	  --target=$TARGET \
	  --prefix="$PREFIX" \
	  --with-sysroot \
	  --disable-nls \
	  --disable-werror

	make && \
	make install && \
	echo ":: Finished building binutils!"
	cd ..
    fi
fi

if [ -d gcc-* ]
then
    echo ":: Start building gcc..."

    GCC_BUILD_DIR="build-gcc"
    GCC_SRC_DIR=$(ls | grep gcc- | awk '{print $1;}')

    if [ -d $GCC_BUILD_DIR ]
    then
	echo "gcc build directory already exists. Skipping."
    else
	# The $PREFIX/bin must be in the PATH
	which -- $TARGET-as || echo "$TARGET-as is not in the PATH!"
	
	mkdir -p $GCC_BUILD_DIR
	cd $GCC_BUILD_DIR
	../${GCC_SRC_DIR}/configure \
	  --target=$TARGET \
	  --prefix="$PREFIX" \
	  --disable-nls \
	  --enable-languages=c,c++ \
	  --without-headers

	make all-gcc && \
	make all-target-libgcc && \
	make install-gcc && \
	make install-target-libgcc &&
	echo ":: Finished building gcc!"
	cd ..
    fi
fi
