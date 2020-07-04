# GCC/G++ defined as the standard compiler
AR=ar
CC=gcc
CXX=g++

#Compiler flags
ARFLAGS=-cvq
CFLAGS=-Wall -O2 -fPIC
CXXFLAGS=-Wall -O2 -std=c++14 -fPIC -fno-strict-aliasing

# To cross compile, set COMPILER accordingly
ifdef COMPILER
AR := $(COMPILER)$(AR)
CC := $(COMPILER)$(CC)
CXX := $(COMPILER)$(CXX)
endif


# E3EXTENSIONS directories
BIN=bin
LIB=lib
OBJ=obj
SRC=src
TMP=tmp

SRC_E3EXTENSIONS=$(SRC)/e3extensions
OBJ_E3EXTENSIONS=$(OBJ)/e3extensions

SRC_LIBG=$(SRC)/libg
OBJ_LIBG=$(OBJ)/libg

SRC_PREPROCESSOR=$(SRC)/preprocessor
OBJ_PREPROCESSOR=$(OBJ)/preprocessor

OBJ_UNUMBER=$(OBJ)/unumber
SRC_UNUMBER=$(SRC)/unumber

LD_LIBRARY_PATH=./lib

LOCAL_DIR=$(abspath .)
FILE_DIR=$(dir $(IN))
FILENAME=$(notdir $(IN))
BASENAME=$(basename $(IN))
SUFFIX=$(suffix $(IN))

## MAGIC
PREPROC_FILE=$(BASENAME)-K$(KEY_SIZE)-B$(BETA)$(SUFFIX)
BINARY_FILE=$(BASENAME)-K$(KEY_SIZE)-B$(BETA).elf
CS_FILE=$(FILE_DIR)CS.txt
CS_FILE_BACKUP=$(basename $(CS_FILE))-K$(KEY_SIZE)-B$(BETA)$(suffix $(CS_FILE))
OUTPUT_ENC=$(FILE_DIR)output_enc-K$(KEY_SIZE)-B$(BETA).txt
OUTPUT_DEC=$(FILE_DIR)output_dec-K$(KEY_SIZE)-B$(BETA).txt

ifdef OUT
RUN_OUT := > $(notdir $(OUT))
endif

ifeq ($(SAVE_TIME),1)
TIME_OUT := 2> TIME-K$(KEY_SIZE)-B$(BETA).txt
endif

ifeq ($(STATIC),1)
OPT := -static $(OPT)
endif

ifeq ($(STATIC_LIBGCC),1)
LDF := -static-libgcc $(LDF)
endif

ifeq ($(STATIC_LIBSTDCPP),1)
LDF := -static-libstdc++ $(LDF)
endif

# E3EXTENSIONS' FLAGS #

# if ARCH=64, the random number generator will work on a base of 64 bits. Only use it in a 64-bit processor. The standard is 32.
ifeq ($(ARCH),64)
OPT := -DARCH64 $(OPT)
endif

# Compile using GMP
ifeq ($(GMP),1)
OPT := -DGMP=1 $(OPT)
LDF := -lgmpxx -lgmp $(LDF)
endif

# Hardware Acceleration
ifdef HWACC
OPT := -DHWACC=$(HWACC) $(OPT)
endif

# Fast Random
ifeq ($(FAST_RANDOM),1)
OPT := -DFAST_RANDOM $(OPT)
endif

# Define if libg is static or dynamic
ifdef STATIC_LIBG
CSFLAGS := $(OBJ_LIBG)/libg.o $(CSFLAGS)
LIBGFLAGS := -DSTATIC_LIBG $(LIBGFLAGS)
else
CSFLAGS := -L./lib -lg $(CSFLAGS)
# LIBGFLAGS := $(LIBGFLAGS)
# -ldl
endif

# libg speed (0, 1, or 2). The greater, the fastest.
ifdef LIBG_SPEED
LIBGFLAGS := -DLIBG_SPEED=$(LIBG_SPEED) $(LIBGFLAGS)
endif

ifdef BIGINT
SECUREINT := bigint
else
SECUREINT := secureint
endif

# GMP CROSS COMPILATION #

# GMP CROSS COMPILATION FLAGS
GMP_INSTALL_DIR=$(LOCAL_DIR)/build-gmp
GMP_HOST=or1k-linux-musl

# If GMP_ASSEMBLY=0, GMP is configured with the flag --disable-assembly when installing GMP for a cross compiler
ifeq ($(GMP_ASSEMBLY),0)
GMP_PARAMS := --disable-assembly $(GMP_PARAMS)
endif

# If GMP_SHARED=0, GMP is configured with the flag --disable-shared when installing GMP for a cross compiler
ifeq ($(GMP_SHARED),0)
GMP_PARAMS := --disable-shared $(GMP_PARAMS)
endif


help:
	@grep -E '^[a-zA-Z_-]+:.*?## .*$$' $(MAKEFILE_LIST) | sort | awk 'BEGIN {FS = ":.*?## "}; {printf "\033[36m%-22s\033[0m %s\n", $$1, $$2}'


clean:
	rm -f $(BIN)/*
	rm -f $(LIB)/*
	rm -f $(OBJ_E3EXTENSIONS)/*
	rm -f $(OBJ_LIBG)/*
	rm -f $(OBJ_PREPROCESSOR)/*
	rm -f $(OBJ_UNUMBER)/*


compile: ## Compile code. Usage: make compile IN=path/to/code OUT=path/to/output [ARCH=64] [COMPILER=or1k-linux-musl-] [GMP=1] [STATIC_LIBG=1]
	$(CXX) $(CXXFLAGS) $(IN) $(CSFLAGS) \
	$(OBJ_E3EXTENSIONS)/$(SECUREINT).o \
	$(OBJ_PREPROCESSOR)/big_random.o \
	$(OBJ_UNUMBER)/unumberg.o $(OBJ_UNUMBER)/cunmber_4096_m.o $(OBJ_UNUMBER)/ma_invert_m.o \
	-o $(OUT) $(OPT) $(LDF) $(LIBGFLAGS)
#	$(OBJ_E3EXTENSIONS)/securering.o \
#$(OBJ_E3EXTENSIONS)/cryptosystem.o

compile-all: compile-unumber compile-sensitive-information compile-e3extensions compile ## Recompile all dependencies and compile code. Usage: make compile-all IN=path/to/code OUT=path/to/output [ARCH=64] [COMPILER=or1k-linux-musl-] [GMP=1] [STATIC_LIBG=1]

compile-e3: compile-unumber compile-e3extensions compile ## Recompile all dependencies and compile code. Usage: make compile-all IN=path/to/code OUT=path/to/output [ARCH=64] [COMPILER=or1k-linux-musl-] [GMP=1] [STATIC_LIBG=1]

compile-e3x:
	make compile-e3 IN=$(IN) OUT=$(OUT) FAST_RANDOM=1 GMP=1 STATIC_LIBGCC=1 STATIC_LIBSTDCPP=1 STATIC=1 HWACC=4096 CC=or1k-elf-gcc CXX=or1k-elf-g++ BIGINT=1

compile-e3x-gmp:
	make compile-all IN=$(IN) OUT=$(OUT) FAST_RANDOM=1 GMP=1 STATIC_LIBGCC=1 STATIC_LIBSTDCPP=1 STATIC=1 CC=or1k-elf-gcc CXX=or1k-elf-g++ BIGINT=1

compile-debug:
	$(CXX) $(CXXFLAGS) $(IN) $(CSFLAGS) \
	$(OBJ_PREPROCESSOR)/big_random.o $(OBJ_PREPROCESSOR)/sensitive_information.o $(OBJ_PREPROCESSOR)/util.o \
	$(OBJ_E3EXTENSIONS)/cryptosystem.o $(OBJ_E3EXTENSIONS)/secureint.o \
	$(OBJ_UNUMBER)/unumberg.o $(OBJ_UNUMBER)/cunmber_4096_m.o $(OBJ_UNUMBER)/ma_invert_m.o \
	-o $(OUT) $(OPT) $(LDF) $(LIBGFLAGS)

compile-debug-all: compile-unumber compile-libg compile-sensitive-information compile-e3extensions compile-debug

compile-decrypt: ## Compile Decrypt. Usage: make compile-decrypt [ARCH=64] [GMP=1]
#	check dir
	[ -s "$(BIN)" ] || mkdir -p $(BIN)
#	compile
	$(CXX) -c $(CXXFLAGS) $(SRC_PREPROCESSOR)/decrypt.cpp -o $(OBJ_PREPROCESSOR)/decrypt.o $(OPT) $(LDF)
#	link
	$(CXX) $(CXXFLAGS) \
	$(OBJ_PREPROCESSOR)/decrypt.o $(OBJ_PREPROCESSOR)/big_random.o $(OBJ_PREPROCESSOR)/sensitive_information.o $(OBJ_PREPROCESSOR)/util.o \
	$(OBJ_UNUMBER)/unumberg.o $(OBJ_UNUMBER)/cunmber_4096_m.o $(OBJ_UNUMBER)/ma_invert_m.o \
	-o $(BIN)/decrypt $(OPT) $(LDF)


compile-decrypt-all: compile-unumber compile-sensitive-information compile-decrypt ## Recompile all dependencies and compile Decrypt. Usage: make compile-decrypt-all [ARCH=64] [GMP=1]


compile-e3extensions: ## Compile e3extensions. Usage: make compile-e3extensions [STATIC_LIBG=path/to/libg] [ARCH=64] [GMP=1]
#	check dir
	[ -s "$(OBJ_E3EXTENSIONS)" ] || mkdir -p $(OBJ_E3EXTENSIONS)
#	compile Cryptosystem
#	$(CXX) -c $(CXXFLAGS) $(SRC_E3EXTENSIONS)/cryptosystem.cpp -o $(OBJ_E3EXTENSIONS)/cryptosystem.o $(OPT) $(LDF) $(LIBGFLAGS)
#	compile SecureInt
	$(CXX) -c $(CXXFLAGS) $(SRC_E3EXTENSIONS)/$(SECUREINT).cpp -o $(OBJ_E3EXTENSIONS)/$(SECUREINT).o $(OPT) $(LDF) $(LIBGFLAGS)
#	$(CXX) -c $(CXXFLAGS) $(SRC_E3EXTENSIONS)/securering.cpp -o $(OBJ_E3EXTENSIONS)/securering.o $(OPT) $(LDF) $(LIBGFLAGS)


compile-libg: ## Usage: make compile-shared-libg [ARCH=64] [GMP=1] [STATIC_LIBG=1]
#	check dir
	[ -s "$(OBJ_LIBG)" ] || mkdir -p $(OBJ_LIBG)
	[ -s "$(LIB)" ] || mkdir -p $(LIB)
ifdef STATIC_LIBG # static libg
#	compile
	$(CXX) -c $(CXXFLAGS) $(SRC_LIBG)/libg.cpp -o $(OBJ_LIBG)/libg.o $(OPT) $(LDF) $(LIBGFLAGS)
#	create static library
	$(AR) $(ARFLAGS) $(LIB)/libg.a $(OBJ_LIBG)/libg.o $(OBJ_PREPROCESSOR)/big_random.o
else # shared libg
#	compile
	$(CXX) $(CXXFLAGS) -c $(SRC_LIBG)/libg.cpp -o $(OBJ_LIBG)/libg.o $(OPT) $(LDF)
#	create shared library
	$(CXX) $(CXXFLAGS) -shared $(OBJ_LIBG)/libg.o \
	$(OBJ_PREPROCESSOR)/big_random.o \
	$(OBJ_UNUMBER)/unumberg.o $(OBJ_UNUMBER)/cunmber_4096_m.o $(OBJ_UNUMBER)/ma_invert_m.o \
	-o $(LIB)/libg.so $(OPT) $(LDF)
endif

compile-preprocessor: ## Compile Preprocessor. Usage: make compile-preprocessor [ARCH=64] [GMP=1]
#	check dir
	[ -s "$(BIN)" ] || mkdir -p $(BIN)
#	compile
	$(CXX) -c $(CXXFLAGS) $(SRC_PREPROCESSOR)/preprocessor.cpp -o $(OBJ_PREPROCESSOR)/preprocessor.o $(OPT) $(LDF)
#	link
	$(CXX) $(CXXFLAGS) \
	$(OBJ_PREPROCESSOR)/preprocessor.o $(OBJ_PREPROCESSOR)/big_random.o $(OBJ_PREPROCESSOR)/sensitive_information.o $(OBJ_PREPROCESSOR)/util.o \
	$(OBJ_UNUMBER)/unumberg.o $(OBJ_UNUMBER)/cunmber_4096_m.o $(OBJ_UNUMBER)/ma_invert_m.o \
	-o $(BIN)/preprocessor $(OPT) $(LDF)


compile-preprocessor-all: compile-unumber compile-sensitive-information compile-preprocessor ## Recompile all dependencies and compile Preprocessor. Usage: make compile-preprocessor [ARCH=64] [GMP=1]


compile-sensitive-information: ## Compile Sensitive Information class and auxiliary libraries. Usage: make compile-sensitive-information [ARCH=64] [GMP=1]
#	check dir
#	[ -s "$(OBJ_PREPROCESSOR)" ] || mkdir -p $(OBJ_PREPROCESSOR)
#	compile big_random
	$(CXX) -c $(CXXFLAGS) $(SRC_PREPROCESSOR)/big_random.cpp -o $(OBJ_PREPROCESSOR)/big_random.o $(OPT) $(LDF)
#	compile SensitiveInformation
	$(CXX) -c $(CXXFLAGS) $(SRC_PREPROCESSOR)/sensitive_information.cpp -o $(OBJ_PREPROCESSOR)/sensitive_information.o $(OPT) $(LDF)
#	compile big_random
	$(CXX) -c $(CXXFLAGS) $(SRC_PREPROCESSOR)/util.cpp -o $(OBJ_PREPROCESSOR)/util.o $(OPT) $(LDF)


compile-unumber: ## Compile Unumber library. Usage: make compile-unumber [GMP=1]
#	check dir
	[ -s "$(OBJ_UNUMBER)" ] || mkdir -p $(OBJ_UNUMBER)
#	compile unumberg
	$(CXX) -c $(CXXFLAGS) $(SRC_UNUMBER)/unumberg.cpp -o $(OBJ_UNUMBER)/unumberg.o  $(OPT) $(LDF)
#	compile cunmber_4096
	$(CC) -c $(CFLAGS) $(SRC_UNUMBER)/cunmber_4096_m.c -o $(OBJ_UNUMBER)/cunmber_4096_m.o $(OPT) $(LDF)
#	compile ma_invert_m
	$(CXX) -c $(CXXFLAGS) $(SRC_UNUMBER)/ma_invert_m.cpp -o $(OBJ_UNUMBER)/ma_invert_m.o $(OPT) $(LDF)


cross-compile-gmp: ## Download and install GMP. Usage: make cross-compile-gmp [GMP_HOST=or1k-linux-musl] [GMP_INSTALL_DIR=/home/user/e3extensions/build-gmp] [GMP_ASSEMBLY=0] [GMP_SHARED=0]
	[ -s "gmp-6.1.2.tar.xz" ] || wget https://gmplib.org/download/gmp/gmp-6.1.2.tar.xz
	[ -s "gmp-6.1.2" ] || tar xf gmp-6.1.2.tar.xz
	test -s $(GMP_INSTALL_DIR) || mkdir $(GMP_INSTALL_DIR)
	cd gmp-6.1.2 ; ./configure --host=$(GMP_HOST) --enable-cxx --prefix=$(GMP_INSTALL_DIR) $(GMP_PARAMS) ; make ; make install


decrypt: ## Decrypt file. Usage: make decrypt IN=path/to/inputfile OUT=path/to/outputfile CS=path/to/cryptosystem
	$(BIN)/decrypt $(IN) $(OUT) $(CS)


# install: clean compile-unumber compile-sensitive-information compile-preprocessor compile-decrypt compile-shared-libg compile-static-libg compile-e3extensions ## Install all basic components. Usage: make install [ARCH=64] [GMP=1]
install: clean compile-unumber compile-sensitive-information compile-preprocessor compile-decrypt compile-libg compile-e3extensions ## Install all basic components. Usage: make install [ARCH=64] [GMP=1]

magic:
	# make preprocess IN=$(IN) OUT=$(PREPROC_FILE) KEY_SIZE=$(KEY_SIZE) BETA=$(BETA)
	make compile-all IN=$(PREPROC_FILE) OUT=$(basename $(BINARY_FILE))-GMP$(suffix $(BINARY_FILE)) FAST_RANDOM=1 GMP=1 STATIC_LIBG=1 STATIC_LIBGCC=1 STATIC_LIBSTDCPP=1 STATIC=1
	make compile-all IN=$(PREPROC_FILE) OUT=$(basename $(BINARY_FILE))-H512$(suffix $(BINARY_FILE)) FAST_RANDOM=1 GMP=1 STATIC_LIBG=1 STATIC_LIBGCC=1 STATIC_LIBSTDCPP=1 STATIC=1 HWACC=512
	make compile-all IN=$(PREPROC_FILE) OUT=$(basename $(BINARY_FILE))-H1024$(suffix $(BINARY_FILE)) FAST_RANDOM=1 GMP=1 STATIC_LIBG=1 STATIC_LIBGCC=1 STATIC_LIBSTDCPP=1 STATIC=1 HWACC=1024
	make compile-all IN=$(PREPROC_FILE) OUT=$(basename $(BINARY_FILE))-H2048$(suffix $(BINARY_FILE)) FAST_RANDOM=1 GMP=1 STATIC_LIBG=1 STATIC_LIBGCC=1 STATIC_LIBSTDCPP=1 STATIC=1 HWACC=2048
	make compile-all IN=$(PREPROC_FILE) OUT=$(basename $(BINARY_FILE))-H4096$(suffix $(BINARY_FILE)) FAST_RANDOM=1 GMP=1 STATIC_LIBG=1 STATIC_LIBGCC=1 STATIC_LIBSTDCPP=1 STATIC=1 HWACC=4096
	cp $(CS_FILE) $(CS_FILE_BACKUP)
#	make run IN=$(BINARY_FILE) OUT=$(OUTPUT_ENC) SAVE_TIME=1
#	make decrypt IN=$(OUTPUT_ENC) OUT=$(OUTPUT_DEC) CS=$(CS_FILE_BACKUP)

magic-all:
	make magic IN=$(IN) KEY_SIZE=16 BETA=$(BETA)
	make magic IN=$(IN) KEY_SIZE=32 BETA=$(BETA)
	make magic IN=$(IN) KEY_SIZE=64 BETA=$(BETA)
	make magic IN=$(IN) KEY_SIZE=128 BETA=$(BETA)
	make magic IN=$(IN) KEY_SIZE=256 BETA=$(BETA)
	make magic IN=$(IN) KEY_SIZE=512 BETA=$(BETA)
	make magic IN=$(IN) KEY_SIZE=1024 BETA=$(BETA)
	make magic IN=$(IN) KEY_SIZE=2048 BETA=$(BETA)

magic-all-all:
	make magic-all IN=$(IN) BETA=8
	make magic-all IN=$(IN) BETA=16
	make magic-all IN=$(IN) BETA=32

preprocess: ## Preprocess code. Usage: make preprocessor IN=path/to/code OUT=path/to/output [KEY_SIZE=1024] [BETA=16]
	$(BIN)/preprocessor $(IN) $(OUT) $(KEY_SIZE) $(BETA)


run: ## Run program. Usage: make run IN=path/to/file [OUT=output.txt] [SAVE_TIME=1]
	cp -f $(LIB)/libg.so $(FILE_DIR)
	cd $(FILE_DIR); time ./$(FILENAME) $(RUN_OUT) $(TIME_OUT)
