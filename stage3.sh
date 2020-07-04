owner=user
prefix=/opt/or1k-toolchain
build_src=build-or1k-src
build_gcc=build-or1k-gcc

# First add the tool chain path to the shell's PATH variable (it's likely this directory won't exist yet but it will be created during the course of the install process)

# export PATH=$PATH:/opt/or1k-toolchain/bin
export PATH=$PATH:$prefix/bin

# build newlib and gdb (without or1ksim in this case)

cd $build_src

../or1k-src/configure --target=or1k-elf --prefix=$prefix --enable-shared --disable-itcl --disable-tk --disable-tcl --disable-winsup --disable-libgui --disable-rda --disable-sid --enable-sim --disable-or1ksim --enable-gdb --with-sysroot --enable-newlib --enable-libgloss --disable-werror

make

make install
