#!/bin/bash
time_start=`date +%s`

# Variables
owner=user
prefix=/opt/or1k-toolchain
build_src=build-or1k-src
build_gcc=build-or1k-gcc

# First add the tool chain path to the shell's PATH variable (it's likely this directory won't exist yet but it will be created during the course of the install process)

# export PATH=$PATH:/opt/or1k-toolchain/bin
export PATH=$PATH:$prefix/bin

# Build the first set of tools, binutils etc.

# NOTE: on 32-bit machines --disable-werror is needed due to an enum acting as bit mask is considered signed

# if [ -d "$build_src" ]; then
# 	rm -rf $build_src
# fi

# if [ -d "$build_gcc" ]; then
# 	rm -rf $build_gcc
# fi

# if [ -d "$prefix" ]; then
# 	rm -rf $prefix
# fi

# mkdir $build_src $build_gcc
if [ -d "$build_src" ]; then
	mkdir $build_src
fi

if [ -d "$build_gcc" ]; then
	 mkdir $build_gcc
fi

cd $build_src

# ../or1k-src/configure --target=or1k-elf --prefix=$prefix --enable-shared --disable-itcl --disable-tk --disable-tcl --disable-winsup --disable-libgui --disable-rda --disable-sid --disable-sim --disable-gdb --with-sysroot --disable-newlib --disable-libgloss --disable-werror

# make

# make install

# Build gcc

# cd ../$build_gcc

# ../or1k-gcc/configure --target=or1k-elf --prefix=$prefix --enable-languages=c --disable-shared --disable-libssp

# make

# make install

# build newlib and gdb (without or1ksim in this case)

# cd ../$build_src

../or1k-src/configure --target=or1k-elf --prefix=$prefix --enable-shared --disable-itcl --disable-tk --disable-tcl --disable-winsup --disable-libgui --disable-rda --disable-sid --enable-sim --disable-or1ksim --enable-gdb --with-sysroot --enable-newlib --enable-libgloss --disable-werror

make -j3

make install

# build gcc again, this time with newlib

# cd ../-$build_gcc

# ../or1k-gcc/configure --target=or1k-elf --prefix=$prefix --enable-languages=c,c++ --disable-shared --disable-libssp --with-newlib

# make

# make install

chown -R $owner $prefix

time_end=`date +%s`
runtime=$((time_end-time_start))

echo Elapsed time: $runtime s
