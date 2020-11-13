
#include "hashtable.h"

typedef struct hashnode {
	int key;
} HashNode;

typedef struct hashtable {
	HashNode *table[HASH_TABLE_SIZE];
} HashTable;

/*
 *
 * Hash Table Functions
 * 
*/

int search_key(HashTable *hashtable, int key) {
	int index = hash_function(key);
	int i = 1;
	while (hashtable->table[index] != NULL && i != HASH_TABLE_SIZE) {
		if (hashtable->table[index]->key == key) { return key; }
		index = hash_function(key+(i++));
	}
	return -1;
}


int add_key(HashTable *hashtable, int key) {
	int index = hash_function(key);

	if (hashtable->table[index] != NULL) {
		int i = 1;
		while (hashtable->table[index] != NULL && i != HASH_TABLE_SIZE) {
			index = hash_function(key+(i++));
		}
		if (i == HASH_TABLE_SIZE) { return 0; }
	}

	HashNode *node = create_hashnode(key);
	hashtable->table[index] = node;
	return 1;
}

HashTable *create_table() {
	HashTable *new_table = (HashTable *) malloc(sizeof(HashTable));
	if (new_table != NULL) {
		for (int i=0; i<HASH_TABLE_SIZE; i++) {new_table->table[i] = NULL;}
	}
	return new_table;
}

void delete_table(HashTable *hashtable) {
	if (hashtable == NULL) { return; }
	for (int i=0; i<HASH_TABLE_SIZE;  i++) {
		HashNode *node = hashtable->table[i];
		delete_hashnode(node);
	}
	free(hashtable);
}

/*
 *
 * Hash Node Functions
 * 
*/

HashNode *create_hashnode(int key) {
	HashNode *node = (HashNode *)malloc(sizeof(HashNode));
	if (node != NULL) {
		node->key = key;
	}
	return node;
}

void delete_hashnode(HashNode *node) {
	if (node == NULL) {return;}
	free(node);
}

/*
 *
 * Hashing Functions 
 * 
*/ 

int hash_function(int x) {
	return x%HASH_TABLE_SIZE;
}