// Copyright Sindrilaru Catalina-Maria, 312CA, 2022

#ifndef HASHTABLE_H_
#define HASHTABLE_H_

int compare_function(void *a, void *b);
unsigned int hash_function(void *a);
hashtable *create_ht(int hmax);
void resize_hashtable(hashtable *ht, int key_size, int value_size);
void put(hashtable *ht, void *key, int key_size, void *value, int value_size);
void *get(hashtable *ht, void *key);
int has_key(hashtable *ht, void *key);
void remove_from_ht(hashtable *ht, void *key);
void *free_hashtable(hashtable *ht);

#endif  // HASHTABLE_H_
