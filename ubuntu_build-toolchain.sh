#!/bin/bash

function build_binutils {
    CURRENT_DIR=$(pwd)
    BINUTILS_PACKET="binutils-2.39.tar.xz"
    BINUTILS_SRC_DIR="${BINUTILS_PACKET%.tar.xz}"
    cd build/toolchain

    if [ ! -f $BINUTILS_PACKET ]
       then
	   curl -X GET https://ftp.gnu.org/gnu/binutils/$BINUTILS_PACKET > $BINUTILS_PACKET
    fi
    tar -axf $BINUTILS_PACKET
    cd $BINUTILS_SRC_DIR
    
    ./configure \
	--target=$1 \
	--prefix="$2" \
	--with-sysroot \
	--disable-nls \
	--disable-werror

    make
    make install
    cd $CURRENT_DIR
}

function build_gcc {
    CURRENT_DIR=$(pwd)
    GCC_PACKET="gcc-12.2.0.tar.xz"
    GCC_SRC_DIR="${GCC_PACKET%.tar.xz}"
    cd build/toolchain
    if [ ! -f $GCC_PACKET ]
    then
	curl -X GET https://ftp.gnu.org/gnu/gcc/gcc-12.2.0/$GCC_PACKET > $GCC_PACKET
    fi
    tar -axf $GCC_PACKET
    cd $GCC_SRC_DIR
    
    ./configure \
	--target=$1 \
	--prefix="$2" \
	--disable-nls \
	--enable-languages=c,c++ \
	--without-headers


    make all-gcc
    make all-target-libgcc
    make install-gcc
    make install-target-libgcc
    
    cd $CURRENT_DIR
}


export PREFIX="$1/toolchain"
export TARGET=i686-elf
export PATH="$PREFIX/bin:$PATH"

build_binutils $TARGET "$PREFIX"
build_gcc $TARGET "$PREFIX"

