// Copyright Sindrilaru Catalina-Maria, 312CA, 2022

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include "defines.h"
#include "lists.h"
#include "hashtable.h"

/**
 * @param a 
 * @param b 
 * @return int 
 */
int compare_function(void *a, void *b)
{
	char *str_a = (char *)a;
	char *str_b = (char *)b;

	return !strcmp(str_a, str_b);
}

/**
 * @brief Returns an index calculated based on a received key
 * 
 * @param a 
 * @return unsigned int 
 */
unsigned int hash_function(void *a)
{
	unsigned char *puchar_a = (unsigned char *) a;
	uint64_t hash = 5381;
	int c;

	while ((c = *puchar_a++))
		hash = ((hash << 5u) + hash) + c;

	return hash;
}

/**
 * @brief Creates a hashtable 
 * 
 * @param hmax 
 * @return hashtable* 
 */
hashtable *create_ht(int hmax)
{
	hashtable *ht = calloc(1, sizeof(hashtable));
	DIE(!ht, "Calloc failed at ht\n");

	ht->buckets = calloc(hmax, sizeof(linked_list_t *));
	DIE(!ht->buckets, "Calloc failed at ht->buckets\n");

	for (int i = 0; i < hmax; i++) {
		ht->buckets[i] = ll_create(sizeof(info));
	}
	ht->hmax = hmax;
	return ht;
}

/**
 * @brief Frees a generic hashtable
 * 
 * @param ht 
 */
void free_old_ht(hashtable *ht)
{
	for (int i = 0; i < ht->hmax; i++) {
		linked_list_t *bucket = ht->buckets[i];

		while (bucket->head != NULL) {
			ll_node_t *removed = ll_remove_nth_node(ht->buckets[i], 0);
			free(((info *)removed->data)->value);
			free(((info *)removed->data)->key);
			free(removed->data);
			free(removed);
		}
		free(ht->buckets[i]);
	}

	free(ht->buckets);
}

/**
 * @brief Resize a hashtable when load factor > 1
 * 
 * @param ht 
 * @param key_size 
 * @param value_size 
 */
void resize_hashtable(hashtable *ht, int key_size, int value_size)
{
	int new_hmax = 2 * ht->hmax;
	/* Create a new hashtable */
	hashtable *new_ht = create_ht(new_hmax);

	/* Goes through the old hashtable and put all the elements in the correct
	 position in the new hashtable */
	for (int i = 0; i < ht->hmax; i++) {
		linked_list_t *bucket = ht->buckets[i];
		ll_node_t *curr = bucket->head;

		for (int j = 0; j < bucket->size; j++) {
			put(new_ht, ((info *)curr->data)->key, key_size,
			 	((info *)curr->data)->value, value_size);
			curr = curr->next;
		}
	}

	/* Frees the old hashtable*/
	free_old_ht(ht);

	ht->buckets = new_ht->buckets;
	ht->hmax = new_hmax;

	free(new_ht);
}

/**
 * @brief Puts an element in the hashtable
 * 
 * @param ht 
 * @param key 
 * @param key_size 
 * @param value 
 * @param value_size 
 */
void put(hashtable *ht, void *key, int key_size, void *value, int value_size)
{
	if (ht == NULL) {
		return;
	}

	unsigned int index;
	index = hash_function(key) % ht->hmax;

	linked_list_t *bucket;
	bucket = ht->buckets[index];
	ll_node_t *curr = bucket->head;

	info *aux;
	while (curr != NULL) {
		aux = (info *)curr->data;
		if (compare_function(aux->key, key)) {
			memcpy(aux->value, value, value_size);
			return;
		}
		curr = curr->next;
	}

	info *new = calloc(1, sizeof(info));
	DIE(!new, "Calloc failed at new\n");

	new->key = calloc(1, key_size);
	DIE(!new->key, "Calloc failed at new->key\n");
	memcpy(new->key, key, key_size);

	new->value = calloc(1, value_size);
	DIE(!new->value, "Calloc failed at new->value\n");
	memcpy(new->value, value, value_size);

	ll_add_nth_node(bucket, bucket->size, new);
	free(new);
	ht->size++;

	if (ht->size / ht->hmax > 1) {
		resize_hashtable(ht, key_size, value_size);
	}
}

/**
 * @brief Returns the value of the given key from the hashtable
 * 
 * @param ht 
 * @param key 
 * @return void* 
 */
void *get(hashtable *ht, void *key)
{
	if (ht == NULL) {
		return NULL;
	}

	unsigned int index = hash_function(key) % ht->hmax;
	linked_list_t *bucket = ht->buckets[index];
	ll_node_t *curr = bucket->head;

	info *aux;
	while (curr != NULL) {
		aux = (info *)curr->data;
		if (compare_function(aux->key, key)) {
			return aux->value;
		}
		curr = curr->next;
	}

	return NULL;
}

/**
 * @brief Returns 1 if the key exist in the hashtable, else returns 0 
 * 
 * @param ht 
 * @param key 
 * @return int 
 */
int has_key(hashtable *ht, void *key)
{
	if (ht == NULL) {
		return -1;
	}

	unsigned int index;
	index = hash_function(key) % ht->hmax;

	linked_list_t *bucket = ht->buckets[index];
	ll_node_t *curr = bucket->head;

	info *aux;
	while (curr != NULL) {
		aux = (info *)curr->data;
		if (compare_function(aux->key, key)) {
			return 1;
		}
		curr = curr->next;
	}

	return 0;
}

/**
 * @brief Removes the element with the given key from the hashtable 
 * 
 * @param ht 
 * @param key 
 */
void remove_from_ht(hashtable *ht, void *key)
{
	if (ht == NULL) {
		return;
	}

	unsigned int index;
	index = hash_function(key) % ht->hmax;

	linked_list_t *bucket = ht->buckets[index];
	ll_node_t *curr = bucket->head;

	int cnt = 0;
	info *aux;
	while (curr != NULL) {
		aux = (info *)curr->data;
		if (compare_function(aux->key, key)) {
			break;
		}
		cnt++;
		curr = curr->next;
	}

	if (curr != NULL) {
		curr = ll_remove_nth_node(bucket, cnt);
		info *aux;
		aux = (info *)curr->data;
		free(aux->value);
		free(aux->key);
		free(aux);
		free(curr);
		ht->size--;
	}
}

/**
 * @brief Frees the hashtable
 * 
 * @param ht 
 * @return void* 
 */
void *free_hashtable(hashtable *ht)
{
	if (ht == NULL) {
		return NULL;
	}

	linked_list_t *bucket;
	for (int i = 0; i < ht->hmax; i++) {
		bucket = ht->buckets[i];

		while (bucket->size > 0) {
			ll_node_t *curr = ll_remove_nth_node(bucket, 0);
			info *aux;
			aux = (info *)curr->data;
			free(aux->value);
			free(aux->key);
			free(aux);
			free(curr);
		}
		free(bucket);
	}

	free(ht->buckets);
	free(ht);
	return NULL;
}
