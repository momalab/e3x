obj="../obj"

obj_unumber="$obj/unumber"

dir=`dirname $1`

echo -n "Compiling $1..."
or1k-elf-g++ -Wall -O2 -std=c++14 -fno-strict-aliasing  $1 \
$obj_unumber/unumberg_elf.o $obj_unumber/cunmber_4096_m_elf.o \
$obj_unumber/ma_invert_m_elf.o \
-o $dir/main.elf 
echo "done"

# or1k-musl-linux-g++ -Wall -O2 -std=c++11 -fno-strict-aliasing  $1 \
# $obj_unumber/unumberg_or1k.o $obj_unumber/cunmber_4096_m_or1k.o \
# $obj_unumber/ma_invert_m_or1k.o \
# -o $dir/main_or1k -ldl
