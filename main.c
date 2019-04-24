#include <stdlib.h>
#include <stdio.h>

#include "hash_table.h"

// This is where you can write personal tests for the hash table.
int main(void) {
    Hashtable* ht = NULL;
    int size = 10;
    allocate(&ht, size);

    int key = 0;
    int value = -1;

    put(ht, key, value);

    int num_values = 1;

    ValType* values = malloc(sizeof(ValType));

    int num_results = 0;

    get(ht, key, values, num_values, &num_results);
    if (num_results > num_values) {
        values = realloc(values, num_results * sizeof(ValType));
        get(ht, 0, values, num_values, &num_results);
    }

    for (int i = 0; i < num_results; i++) {
        printf("value %d is %d \n", i, values[i]);
    }
    free(values);

    erase(ht, 0);

    deallocate(ht);
    return 0;
}
