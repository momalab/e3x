obj="../obj"

obj_unumber="$obj/unumber"

dir=`dirname $1`

echo -n "Compiling $1..."
g++ -Wall -O2 -std=c++14 -fno-strict-aliasing $1 \
$obj_unumber/unumberg.o $obj_unumber/cunmber_4096_m.o \
$obj_unumber/ma_invert_m.o \
-o $dir/main
# -ldl
echo "done"

# -static-libgcc -static-libstdc++
