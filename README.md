# Hash Table

(Note: `main.c`, `test.c`, and `benchmark.c` are taken from the class 
assignment that the hash table was for.)

This repository contains a simple hash table implementation.

The interface is defined in `hash_table.h`. See `hash_table.c` for the
expected behavior and descriptions of the parameters.

`main.c` is meant for playing around with the implementation. Compile and
run the code in `main.c` by running `make main; ./main` in the command line.

`test.c` is meant for testing the correctness of the put, get, and erase
functions. Compile and run it through the commands `make test; ./test`.

To benchmark the code and determine how efficient the implementation is,
run `make benchmark; ./benchmark`.

To build everything, simply run `make`.
