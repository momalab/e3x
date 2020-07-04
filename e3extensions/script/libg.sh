lib="../lib"
obj="../obj"
src="../src"

obj_ligc="$obj/ligb"
obj_unumber="$obj/unumber"
src_libg="$src/libg"

if [ -d "$obj_ligc" ]; then
	rm -rf $obj_ligc
fi
mkdir $obj_ligc

# ./sensitive_information.sh
./unumber.sh # if not using sensitive_information for libG

echo -n "Compiling libG..."
g++ -Wall -O2 -std=c++14 -fno-strict-aliasing -fPIC -c $src_libg/libg.cpp -o $obj_ligc/libg.o -ldl
# g++ -Wall -O2 -std=c++14 -fno-strict-aliasing -fPIC -c $src_libg/libg.cpp \
# $bin_unumber/unumberg.o $bin_unumber/cunmber_4096_m.o \
# $bin_unumber/ma_invert_m.o \
# -o $bin_ligc/libg.o -ldl

g++ -Wall -O2 -std=c++14 -fno-strict-aliasing -shared $obj_ligc/libg.o \
$obj_unumber/unumberg.o $obj_unumber/cunmber_4096_m.o \
$obj_unumber/ma_invert_m.o \
-o $lib/libg.so -ldl
echo "done"
