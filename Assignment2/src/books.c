// Copyright Sindrilaru Catalina-Maria, 312CA, 2022

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "defines.h"
#include "lists.h"
#include "hashtable.h"
#include "books.h"

/**
 * @brief Read the definitions for a book and add them to right hashtable
 * 
 * @param book_name 
 * @param number_def 
 * @param library 
 */
void read_definitions(char *book_name, int number_def, hashtable *library)
{
	/* If the book already exist, it will be deleted */
	if (has_key(library, book_name) == 1) {
		book_t *book = (book_t *)get(library, book_name);
		free_hashtable(book->ht);
		remove_from_ht(library, book_name);
	}

	char def_key[MAX];
	char def_val[MAX];

	/* Create a book with the hashtable for the definitions and the other
	 attributes */
	book_t *book = calloc(1, sizeof(book_t));
	DIE(!book, "Calloc failed at book\n");
	book->ht = create_ht(HMAX);
	book->reachable = 1; /* Initially the book is available */
	book->borrows = 0;
	book->total_points = 0;
	book->rating = 0;

	/* Reads the definitions and adds them to the hashtable inside the book */
	for (int i = 0; i < number_def; i++) {
		scanf("%s%s", def_key, def_val);
		put(book->ht, def_key, MAX, def_val, MAX);
	}

	/* Adds the book to the hlibrary*/
	put(library, book_name, BOOK_MAX, book, sizeof(book_t));
	free(book);
}

void extract_arg_for_books(char *line, char *name_book, int *number_def)
{
	char copy_line[MAX_LINE];
	strcpy(copy_line, line);
	char *p = strtok(line, "\"");
	p = strtok(NULL, "\"");
	strcpy(name_book, p);

	p = strtok(copy_line, " ");
	*number_def = 0;
	while (p) {
		if (atoi(p) != 0) {
			*number_def = atoi(p);
		}
		p = strtok(NULL, " ");
	}
}
/**
 * @brief Extracts the name of the book and its number of definitions and
      	  then adds the book in the library
 * 
 * @param line 
 * @param library 
 */
void add_book_to_library(char *line, hashtable *library)
{
	char name_book[BOOK_MAX];
	int number_def;

	extract_arg_for_books(line, name_book, &number_def);
	read_definitions(name_book, number_def, library);
}

/**
 * @brief Displays the characteristics of a searched book
 * 
 * @param line 
 * @param library 
 */
void get_book_from_library(char *line, hashtable *library)
{
	char name_book[BOOK_MAX];

	/* Extract the name of the book*/
	char *p = strtok(line, "\"");
	p = strtok(NULL, "\"");
	strcpy(name_book, p);

	if (has_key(library, name_book) == 0) {
		/* If the books does not exist in the library*/
		printf("The book is not in the library.\n");
	} else {
		char aux_name[BOOK_MAX];
		unsigned int index;
		/* Find the list in which the book is*/
		index = hash_function(name_book) % library->hmax;
		linked_list_t *bucket = library->buckets[index];
		ll_node_t *curr = bucket->head;

		info *aux;
		int borrows, total_points;
		/*  Scrolls through the list until I find the key to the book 
		I want and then saves its characteristics */
		while (curr != NULL) {
			aux = (info *)curr->data;
			if (compare_function(aux->key, name_book)) {
				strcpy(aux_name, aux->key);
				book_t *book = (book_t *)aux->value;
				borrows = book->borrows;
				total_points = book->total_points;
				break;
			}
			curr = curr->next;
		}

		/* Calculate the rating */
		float rating = 0;
		if (borrows != 0) {
			rating = (float)total_points / borrows;
		}
		printf("Name:%s Rating:%.3f Purchases:%d\n", aux_name, rating, borrows);
	}
}

/**
 * @brief Removes the book and all its definitions
 * 
 * @param line 
 * @param library 
 */
void remove_book_from_library(char *line, hashtable *library)
{
	char name_book[BOOK_MAX];

	char *p = strtok(line, "\"");
	p = strtok(NULL, "\"");
	strcpy(name_book, p);

	/* If the book does not exist in the library*/
	if (has_key(library, name_book) == 0) {
		printf("The book is not in the library.\n");
		return;
	}

	book_t *book = (book_t *)get(library, name_book);
	free_hashtable(book->ht);
	remove_from_ht(library, name_book);
}

/**
 * @brief Deletes all the books from the library 
 * 
 * @param library 
 */
void free_books(hashtable *library)
{
	for (int i = 0; i < library->hmax; i++) {
		linked_list_t *bucket;
		bucket = library->buckets[i];
		ll_node_t *curr = bucket->head;
		info *aux;
		while (curr != NULL) {
			aux = (info *)curr->data;
			book_t *book = (book_t *)aux->value;
			free_hashtable(book->ht);
			curr = curr->next;
		}
	}
}
