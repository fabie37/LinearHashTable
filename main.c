#include "hashtable.h"
#include <stdio.h>
#include <assert.h>

void add_key_test(HashTable *table);

int main() {
    HashTable *table = create_table();
    add_key_test(table);
    delete_table(table);
}

void add_key_test(HashTable *table) {
    for (int i=0; i<20; i++) {
        add_key(table, (i*4)+1);
        printf("Is %d in table? %d\n", (i*4)+1, search_key(table, (i*4)+1));
        assert((i*4)+1 == search_key(table,(i*4)+1));
    }
}