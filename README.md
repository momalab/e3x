**E3X: Encrypt-Everything-Everywhere ISA eXtensions for private computation**

**OR1K-GCC**

1. Clone or1k-gcc from https://github.com/openrisc/or1k-gcc
2. Unzip our modified or1k-src with added assembly instructions (forked from https://github.com/openrisc/or1k-src)
3. Install or1k-gcc (our script 'compileGCC.sh' may help you, but it is not necessary)

**OR1KSIM**

1. Unzip the modified or1ksim with support to E3X (forked from https://github.com/openrisc/or1ksim)
2. Install it (our script 'remake_or1ksim.sh' may help you, but it is not necessary)

**Checking installation**

Check if the compiler and simulator have been correctly installed by compiling and running the test program under the directory 'test'.

Now you can start using E3X. You can find the framework in the directory 'e3extensions'.
