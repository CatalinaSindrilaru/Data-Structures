// Copyright Sindrilaru Catalina-Maria, 312CA, 2022

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include  "defines.h"
#include "lists.h"
#include "hashtable.h"
#include "books.h"
#include "definitions.h"
#include "users.h"
#include "show.h"

int main()
{
	char line[MAX_LINE];
	/* Create the hashtables for library and users database*/
	hashtable *library = create_ht(HMAX);
	hashtable *database_users = create_ht(HMAX);

	/* Read each command and call the right function*/
	while (1) {
		memset(line, 0, MAX_LINE);
		fgets(line, MAX_LINE, stdin);
		if (strcmp(line, "EXIT") != 0) {
			line[strlen(line) - 1] = '\0';
		}

		if (strncmp(line, "ADD_BOOK", 8) == 0) {
			add_book_to_library(line, library);

		} else if (strncmp(line, "GET_BOOK", 8) == 0) {
			get_book_from_library(line, library);

		} else if (strncmp(line, "RMV_BOOK", 8) == 0) {
			remove_book_from_library(line, library);

		} else if (strncmp(line, "ADD_DEF", 7) == 0) {
			add_def_to_book(line, library);

		} else if (strncmp(line, "GET_DEF", 7) == 0) {
			get_def_from_book(line, library);

		} else if (strncmp(line, "RMV_DEF", 7) == 0) {
			remove_def_from_book(line, library);

		} else if (strncmp(line, "ADD_USER", 8) == 0) {
			add_user(line, database_users);

		} else if (strncmp(line, "BORROW", 6) == 0) {
			borrow_book(line, database_users, library);

		} else if (strncmp(line, "RETURN", 6) == 0) {
			return_book(line, database_users, library);

		} else if (strncmp(line, "LOST", 4) == 0) {
			lost_book(line, database_users, library);

		} else if (strncmp(line, "EXIT", 4) == 0) {
			display_top_books(library);
			display_top_users(database_users);
			free_books(library);
			free_hashtable(library);
			free_hashtable(database_users);
			break;
		}
	}

	return 0;
}
