#ifndef CS165_HASH_TABLE
#define CS165_HASH_TABLE

#include <stdlib.h>
#include <stdio.h>

#define CUTOFF_RATIO 2

typedef int KeyType;
typedef int ValType;

typedef struct LinkedList {
    struct LinkedList* next;
    KeyType key;
    ValType value;
} LinkedList;

typedef struct Hashtable {
    LinkedList** buckets;
    int length;
} Hashtable;

int allocate(Hashtable** ht, int size);
int put(Hashtable* ht, KeyType key, ValType value);
int get(Hashtable* ht, KeyType key, ValType* values, int num_values, int* num_results);
int erase(Hashtable* ht, KeyType key);
int deallocate(Hashtable* ht);

#endif
