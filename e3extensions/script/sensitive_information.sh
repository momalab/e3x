obj="../obj"
src="../src"

obj_preprocessor="$obj/preprocessor"
src_preprocessor="$src/preprocessor"

if ! [ -d "$obj_preprocessor" ]; then
	mkdir $obj_preprocessor
fi

./unumber.sh
echo -n "Compiling SensitiveInformation..."
g++ -c -Wall -O2 -std=c++14 -fno-strict-aliasing  -fPIC $src_preprocessor/sensitive_information.h -o $obj_preprocessor/sensitive_information.o
echo "done"
