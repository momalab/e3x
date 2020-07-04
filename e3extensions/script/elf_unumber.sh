obj="../obj"
src="../src"

obj_unumber="$obj/unumber"
src_unumber="$src/unumber"

if ! [ -d "$obj_unumber" ]; then
	mkdir $obj_unumber
fi

echo -n "Compiling Unumber..."
or1k-elf-g++ -c -Wall -O2 -std=c++14 -fno-strict-aliasing -fPIC $src_unumber/unumberg.cpp -o $obj_unumber/unumberg_elf.o
or1k-elf-gcc -c -Wall -O2 -fPIC $src_unumber/cunmber_4096_m.c -o $obj_unumber/cunmber_4096_m_elf.o
or1k-elf-g++ -c -Wall -O2 -std=c++14 -fno-strict-aliasing  -fPIC $src_unumber/ma_invert_m.cpp -o $obj_unumber/ma_invert_m_elf.o
echo "done"

# or1k-musl-linux-g++ -c -Wall -O2 -std=c++11 -fno-strict-aliasing -fPIC $src_unumber/unumberg.cpp -o $obj_unumber/unumberg_or1k.o
# or1k-musl-linux-gcc -c -Wall -O2 -fPIC $src_unumber/cunmber_4096_m.c -o $obj_unumber/cunmber_4096_m_or1k.o
# or1k-musl-linux-g++ -c -Wall -O2 -std=c++11 -fno-strict-aliasing  -fPIC $src_unumber/ma_invert_m.cpp -o $obj_unumber ma_invert_m_or1k.o

# original
# g++ -c -Wall -O2 -std=c++14 -fno-strict-aliasing   ./unumber/unumberg.cpp -o _bin_unx/unumberg.o
# gcc -c -Wall -O2   ./unumber/cunmber_4096_m.c -o _bin_unx/cunmber_4096_m.o
# g++ -c -Wall -O2 -std=c++14 -fno-strict-aliasing   ./unumber/ma_invert_m.cpp -o _bin_unx/ma_invert_m.o
