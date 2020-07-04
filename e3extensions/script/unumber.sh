obj="../obj"
src="../src"

obj_unumber="$obj/unumber"
src_unumber="$src/unumber"

if ! [ -d "$obj_unumber" ]; then
	mkdir $obj_unumber
fi

echo -n "Compiling Unumber..."
g++ -c -Wall -O2 -std=c++14 -fno-strict-aliasing -fPIC $src_unumber/unumberg.cpp -o $obj_unumber/unumberg.o
gcc -c -Wall -O2 -fPIC $src_unumber/cunmber_4096_m.c -o $obj_unumber/cunmber_4096_m.o
g++ -c -Wall -O2 -std=c++14 -fno-strict-aliasing -fPIC $src_unumber/ma_invert_m.cpp -o $obj_unumber/ma_invert_m.o
echo "done"

# -static-libgcc -static-libstdc++ 
# original
# g++ -c -Wall -O2 -std=c++14 -fno-strict-aliasing   ./unumber/unumberg.cpp -o _bin_unx/unumberg.o
# gcc -c -Wall -O2   ./unumber/cunmber_4096_m.c -o _bin_unx/cunmber_4096_m.o
# g++ -c -Wall -O2 -std=c++14 -fno-strict-aliasing   ./unumber/ma_invert_m.cpp -o _bin_unx/ma_invert_m.o
