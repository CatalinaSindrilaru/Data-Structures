// Copyright Sindrilaru Catalina-Maria, 312CA, 2022

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "defines.h"
#include "lists.h"
#include "hashtable.h"
#include "definitions.h"

/**
 * @brief Extract the name of the book, the definition key and
		  the definition value
 * 
 * @param line 
 * @param name_book 
 * @param key 
 * @param val 
 */
void extract_arg_for_add_def(char *line, char *name_book, char *key, char *val)
{
	char copy_line[MAX_LINE];
	strcpy(copy_line, line);

	char *p = strtok(line, "\"");
	p = strtok(NULL, "\"");
	strcpy(name_book, p);

	p = strtok(copy_line, " ");

	//strcpy(key, p);
	//p = strtok(NULL, " ");
	//strcpy(val, p);

	while (p != NULL) {
		//p = strtok(NULL, " ");
		// if (p != NULL) {
		// 	strcpy(key, val);
		// 	strcpy(val, p);

		// }
		if (p[strlen(p) - 1] == '\"') {
			p = strtok(NULL, " ");
			strcpy(key, p);
			p = strtok(NULL, " ");
			strcpy(val, p);
			//val[strlen(val) - 1] = '\0';
			p = strtok(NULL, " ");
		} else {
			p = strtok(NULL, " ");
		}

	}
}
/**
 * @brief Adds a definition to the hashtable of the given book
 * 
 * @param line 
 * @param library 
 */
void add_def_to_book(char *line, hashtable *library)
{
	char name_book[BOOK_MAX];
	char def_key[MAX];
	char def_val[MAX];

	extract_arg_for_add_def(line, name_book, def_key, def_val);

	/* Verify if the book exists in the library*/
	if (has_key(library, name_book) == 0) {
		printf("The book is not in the library.\n");
		return;
	}

	/* Adds the new definition to the book hashtable */
	book_t *book;
	book = (book_t *)get(library, name_book);
	put(book->ht, def_key, MAX, def_val, MAX);
}

/**
 * @brief Extract the name of the book and the definition key
 * 
 * @param line 
 * @param name_book 
 * @param key 
 */
void extract_arg_for_def(char *line, char *name_book, char *key)
{
	char copy_line[MAX_LINE];
	strcpy(copy_line, line);

	char *p = strtok(line, "\"");
	p = strtok(NULL, "\"");
	strcpy(name_book, p);

	p = strtok(copy_line, " ");
	while (p) {
		strcpy(key, p);
		p = strtok(NULL, " ");
	}
}
/**
 * @brief Displays the value corresponding to a key in a given book
 * 
 * @param line 
 * @param library 
 */
void get_def_from_book(char *line, hashtable *library)
{
	char name_book[BOOK_MAX];
	char def_key[MAX];

	extract_arg_for_def(line, name_book, def_key);
	/* Check if the book exists in the library */
	if (has_key(library, name_book) == 0) {
		printf("The book is not in the library.\n");
		return;
	}

	/* Check if the definition exists in the book */
	book_t *book;
	book = (book_t *)get(library, name_book);
	if (has_key(book->ht, def_key) == 0) {
		printf("The definition is not in the book.\n");
		return;
	}

	/* Finds the value and displays it */
	char *def_val;
	def_val = (char *)get(book->ht, def_key);
	printf("%s\n", def_val);
}

/**
 * @brief Removes a definition from a given book 
 * 
 * @param line 
 * @param library 
 */
void remove_def_from_book(char *line, hashtable *library)
{
	char name_book[BOOK_MAX];
	char def_key[MAX];

	extract_arg_for_def(line, name_book, def_key);

	/* Check if the book exists in the library */
	if (has_key(library, name_book) == 0) {
		printf("The book is not in the library.\n");
		return;
	}

	/* Check if the definition exists in the book */
	book_t *book;
	book = (book_t *)get(library, name_book);
	if (has_key(book->ht, def_key) == 0) {
		printf("The definition is not in the book.\n");
		return;
	}

	/* Delete the definition from the book */
	remove_from_ht(book->ht, def_key);
}
