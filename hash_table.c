#include "hash_table.h"

/////////////
// HELPERS //
/////////////

inline int hash(KeyType key, int length) {
    return ((unsigned int) key) % length;
}

inline int is_prime(int x) {
    if (x < 2) {
        return 0;
    }
    for (int i = 2; x >= i * i; i++) {
        if (x % i == 0) {
            return 0;
        }
    }
    return 1;
}

inline int get_prime(int minimum) {
    int current = minimum;
    while (!is_prime(current)) {
        current += 1;
    }
    return current;
}

void free_bucket(LinkedList* bucket) {
    if (!bucket) {
        return;
    }
    free_bucket(bucket->next);
    free(bucket);
}

////////////////////
// MAIN FUNCTIONS //
////////////////////

/**
 * allocate(ht, size)
 *
 * Initialize the components of a hashtable.
 * The size parameter is the expected number of elements to be inserted.
 * This method returns an error code, 0 for success and -1 otherwise.
 **/
int allocate(Hashtable** ht, int size) {
    if (!ht || *ht || size < 0) {
        return -1;
    }

    *ht = (Hashtable*) malloc(sizeof(Hashtable));

    int length = get_prime(CUTOFF_RATIO * size);
    (*ht)->buckets = (LinkedList**) calloc(length, sizeof(LinkedList*));
    (*ht)->length = length;
    return 0;
}

/**
 * put(ht, key, value)
 *
 * Insert a key-value pair into the hash table.
 * It returns an error code, 0 for success and -1 otherwise.
 **/
int put(Hashtable* ht, KeyType key, ValType value) {
    if (!ht) {
        return -1;
    }

    int hash_index = hash(key, ht->length);
    LinkedList* first_node = malloc(sizeof(LinkedList));
    first_node->next = ht->buckets[hash_index];
    first_node->key = key;
    first_node->value = value;
    ht->buckets[hash_index] = first_node;
    return 0;
}

/**
 * get(ht, key, values, num_values, num_results)
 *
 * Retrieve entries with a matching key and store the corresponding values
 * in the values array.
 * The size of the values array is given by the parameter num_values. If
 * there are more matching entries than num_values, they are not stored in
 * the values array to avoid a buffer overflow. The function returns the
 * number of matching entries using the num_results pointer. If the value
 * of num_results is greater than num_values, the caller can invoke this
 * function again (with a larger buffer) to get values that it missed during
 * the first call. 
 * This method returns an error code, 0 for success and -1 otherwise.
 **/
int get(Hashtable* ht, KeyType key, ValType* values, int num_values, int* num_results) {
    if (!ht || !values) {
        return -1;
    }

    *num_results = 0;
    int hash_index = hash(key, ht->length);
    LinkedList* node = ht->buckets[hash_index];
    while (node) {
        if (node->key == key) {
            if (*num_results < num_values) {
                values[*num_results] = node->value;
            }
            *num_results += 1;
        }
        node = node->next;
    }
    return 0;
}

/**
 * erase(ht, key)
 *
 * Erase all key-value pairs with a given key from the hash table.
 * It returns an error code, 0 for success and -1 otherwise (e.g., if the
 * hashtable is not allocated).
 **/
int erase(Hashtable* ht, KeyType key) {
    if (!ht) {
        return -1;
    }

    int hash_index = hash(key, ht->length);
    if (ht->buckets[hash_index]) {
        LinkedList* node = ht->buckets[hash_index];
        while (node->next) {
            if ((node->next)->key == key) {
                LinkedList* to_delete = node->next;
                node->next = (node->next)->next;
                free(to_delete);
            } else {
                node = node->next;
            }
        }
        node = ht->buckets[hash_index];
        if (node->key == key) {
            LinkedList* to_delete = node;
            ht->buckets[hash_index] = node->next;
            free(to_delete);
        }
    }
    return 0;
}

/**
 * deallocate(ht)
 *
 * Free all memory occupied by the hash table.
 * It returns an error code, 0 for success and -1 otherwise.
 **/
int deallocate(Hashtable* ht) {
    if (!ht) {
        return 0;
    }
    LinkedList** buckets = ht->buckets;
    for (int i = 0; i < ht->length; i++) {
        free_bucket(buckets[i]);
    }
    free(ht->buckets);
    free(ht);
    return 0;
}
