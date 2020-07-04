obj="../obj"
src="../src"

obj_e3extensions="$obj/e3extensions"
src_e3extensions="$src/e3extensions"

if [ -d "$obj_e3extensions" ]; then
	rm -rf $obj_e3extensions
fi
mkdir $obj_e3extensions

./unumber.sh

echo -n "Compiling Cryptosystem..."
g++ -c -Wall -O2 -std=c++14 -fno-strict-aliasing  -fPIC $src_e3extensions/cryptosystem.h -o $obj_e3extensions/cryptosystem.o
echo "done"

echo -n "Compiling SecureInt..."
g++ -c -Wall -O2 -std=c++14 -fno-strict-aliasing  -fPIC $src_e3extensions/secureint.h -o $obj_e3extensions/secureint.o
echo "done"
