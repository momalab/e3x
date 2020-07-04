owner=$USER
prefix=/opt/or1k-toolchain
build_gcc=build-or1k-gcc
build_src=build-or1k-src
build_sim=build_or1ksim
PATH=$PATH:$prefix/bin

all: install

dependencies:
	sudo apt -y install autoconf autotools-dev bison build-essential flex gawk libgmp-dev libmpc-dev libmpfr-dev libncurses5-dev libncursesw5-dev libtool libzip-dev m4 texinfo zlib1g-dev

install: dependencies install-or1k-gcc install-or1k-sim

install-or1k-gcc:
	$(shell ./compileGCC.sh)

install-or1ksim:
	$(shell remake_or1ksim.sh)

quick:
	$(shell ./compileGCC-quick.sh)

clean:
	if [ -d ${build_gcc} ]; then rm -rf ${build_gcc}; fi
	if [ -d ${build_src} ]; then rm -rf ${build_src}; fi
	if [ -d ${build_sim} ]; then rm -rf ${build_sim}; fi
