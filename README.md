# Hash Table

This repository contains my (simple) hash table implementation.

The interface is defined in the `hash_table.h` file. See the `hash_table.c`
file for expected behavior and parameter descriptions.

`main.c` is meant for playing around with the implementation. Compile and
run the code in `main.c` by running `make main; ./main` in the command line.

`test.c` is meant for testing the correctness of the put, get, and erase
functions. Compile and run it through the commands `make test; ./test`.

To benchmark the code and determine how efficient the implementation is,
run `make benchmark; ./benchmark`.

To build everything, simply run `make`.
