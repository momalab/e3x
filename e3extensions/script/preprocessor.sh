bin="../bin"
obj="../obj"
src="../src"

obj_unumber="$obj/unumber"
src_preprocessor="$src/preprocessor"

./unumber.sh
# ./sensitive_information.sh

echo -n "Compiling Preprocessor..."
g++ -Wall -O2 -std=c++14 -fno-strict-aliasing  $src_preprocessor/preprocessor.cpp \
$obj_unumber/unumberg.o $obj_unumber/cunmber_4096_m.o \
$obj_unumber/ma_invert_m.o \
-o $bin/preprocessor
echo "done"
