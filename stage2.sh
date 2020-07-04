owner=user
prefix=/opt/or1k-toolchain
build_src=build-or1k-src
build_gcc=build-or1k-gcc

# First add the tool chain path to the shell's PATH variable (it's likely this directory won't exist yet but it will be created during the course of the install process)

# export PATH=$PATH:/opt/or1k-toolchain/bin
export PATH=$PATH:$prefix/bin

# Build gcc

cd $build_gcc

../or1k-gcc/configure --target=or1k-elf --prefix=$prefix --enable-languages=c --disable-shared --disable-libssp

make

make install
