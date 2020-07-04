build_or1ksim=build-or1ksim
target=or1k
prefix=/opt/or1ksim
configure=1

if [ -d "$build_or1ksim" ]; then
	configure=0
else
	mkdir $build_or1ksim
fi

cd $build_or1ksim

if [ $configure = 1 ]; then
	../or1ksim/configure --target=$target --prefix=$prefix
fi

make
make install
cd ..
