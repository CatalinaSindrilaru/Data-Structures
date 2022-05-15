// Copyright Sindrilaru Catalina-Maria, 312CA, 2022

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "defines.h"
#include "lists.h"
#include "hashtable.h"
#include "definitions.h"
#include "books.h"
#include "users.h"

/**
 * @brief Creates a user and adds it to the database
 * 
 * @param line 
 * @param database_users 
 */
void add_user(char *line, hashtable *database_users)
{
	char name_user[MAX];

	char *p = strtok(line, " ");
	p = strtok(NULL, " ");
	strcpy(name_user, p);

	if (has_key(database_users, name_user) == 1) {
		printf("User is already registered.\n");
		return;
	}

	user_t *user;
	user = calloc(1, sizeof(user_t));
	DIE(!user, "Calloc failed at user\n");
	/* Initally */
	user->banned = 0; /* The user is eligible */
	user->borrowed = 0; /* He has no borrowed books */
	user->days_available = 0;
	user->points = 100;
	memset(user->borrowed_book, 0, 	BOOK_MAX);

	put(database_users, name_user, MAX, user, sizeof(user_t));
	free(user);
}

/**
 * @brief Extract the name of the user, the name of the book and how
		  many days he wants to borrow the book
 * 
 * @param line 
 * @param name_user 
 * @param name_book 
 * @param days 
 */
void extract_arg_for_borrow(char *line, char *name_user, char *name_book,
							int *days)
{
	char copy_line1[MAX_LINE];
	char copy_line2[MAX_LINE];
	strcpy(copy_line1, line);
	strcpy(copy_line2, line);

	char *p = strtok(line, " ");
	p = strtok(NULL, " ");
	strcpy(name_user, p);

	p = strtok(copy_line1, "\"");
	p = strtok(NULL, "\"");
	strcpy(name_book, p);

	p = strtok(copy_line2, " ");
	*days = 0;
	while (p) {
		if (atoi(p) != 0) {
			*days = atoi(p);
		}
		p = strtok(NULL, " ");
	}
}
/**
 * @brief Updates both the database and the library when a user borrows a book
 * 
 * @param line 
 * @param database_users 
 * @param library 
 */
void borrow_book(char *line, hashtable *database_users, hashtable *library)
{
	char name_book[BOOK_MAX];
	char name_user[MAX];
	int days_available;

	extract_arg_for_borrow(line, name_user, name_book, &days_available);

	user_t *user;
	user = (user_t *)get(database_users, name_user);

	book_t *book;
	book = (book_t *)get(library, name_book);

	/* verify if the user is registered */
	if (has_key(database_users, name_user) == 0) {
		printf("You are not registered yet.\n");
		return;
	}

	/* Verify if the user is banned */
	if (user->banned == 1) {
		printf("You are banned from this library.\n");
		return;
	}

	/* check if the user already has a borrowed book */
	if (user->borrowed == 1) {
		printf("You have already borrowed a book.\n");
		return;
	}

	/* Verify if the book exist in the library*/
	if (has_key(library, name_book) == 0) {
		printf("The book is not in the library.\n");
		return;
	}

	/* Verify if the book is already borrowed*/
	if (book->reachable == 0) {
		printf("The book is borrowed.\n");
		return;
	}

	/* Updates the book and user features */
	memset(user->borrowed_book, 0, BOOK_MAX);
	memcpy(user->borrowed_book, name_book, strlen(name_book));
	user->banned = 0;
	user->borrowed = 1;
	user->days_available = days_available;
	book->reachable = 0;
}

/**
 * @brief Extract the name of the user, the name of the book, how many 
		  days he kept the book and what grade did he give to the book
 * 
 * @param line 
 * @param name_user 
 * @param name_book 
 * @param days 
 * @param rating 
 */
void extract_arg_for_return(char *line, char *name_user, char *name_book,
						    int *days, int *rating)
{
	char copy_line1[MAX_LINE];
	char copy_line2[MAX_LINE];
	strcpy(copy_line1, line);
	strcpy(copy_line2, line);

	char *p = strtok(line, " ");
	p = strtok(NULL, " ");
	strcpy(name_user, p);

	p = strtok(copy_line1, "\"");
	p = strtok(NULL, "\"");
	strcpy(name_book, p);

	p = strtok(copy_line2, " ");

	//char number1[MAX];
	//char number2[MAX];
	//strcpy(number1, p);
	//p = strtok(NULL, " ");
	//strcpy(number2, p);
	*days = 0;
	*rating = 0;
	while (p != NULL) {
			if (atoi(p) != 0 || strncmp(p, "0", 1) == 0) {
				*days = atoi(p);
				p = strtok(NULL, " ");
				*rating = atoi(p);
				p = strtok(NULL, " ");
			} else {
				p = strtok(NULL, " ");
			}

			
	}

	//*days = 0;
	//*rating = 0;
	//*days = atoi(number1);
	//*rating = atoi(number2);
}
/**
 * @brief Updates both the database and the library when a user returns a book 
 * 
 * @param line 
 * @param database_users 
 * @param library 
 */
void return_book(char *line, hashtable *database_users, hashtable *library)
{
	char name_book[BOOK_MAX];
	char name_user[MAX];
	int days_since_borrow, rating;

	extract_arg_for_return(line, name_user, name_book, &days_since_borrow,
						   &rating);

	user_t *user = (user_t *)get(database_users, name_user);

	if (user->banned == 1) {
		printf("You are banned from this library.\n");
		return;
	}
	if (user->borrowed == 0) {
		printf("You didn't borrow this book.\n");
		return;
	}

	if (strcmp(name_book, user->borrowed_book) != 0) {
		printf("You didn't borrow this book.\n");
		return;
	}

	int score;
	/* Calculates the score if the book was returned sooner or later */
	if (user->days_available < days_since_borrow) {
		score = 2 * (days_since_borrow - user->days_available);
		if (user->points - score < 0) {
			user->banned = 1;
			printf("The user %s has been banned from this library.\n",
					name_user);
		}
		score = -score;
	}

	if (user->days_available >= days_since_borrow) {
		score =  user->days_available - days_since_borrow;
	}

	/* Updates the book and user data */
	memset(user->borrowed_book, 0, 	BOOK_MAX);
	user->points = user->points + score;
	user->borrowed = 0;
	user->days_available = 0;

	book_t *book = (book_t *)get(library, name_book);
	book->reachable = 1;
	book->borrows += 1;
	book->total_points += rating;
	book->rating = (float)book->total_points / book->borrows;
}

/**
 * @brief Extract the name of the user and the name of the book he lost.
 * 
 * @param line 
 * @param name_user 
 * @param name_book 
 */
void extract_arg_for_lost(char *line, char *name_user, char *name_book)
{
	char copy_line1[MAX_LINE];
	char copy_line2[MAX_LINE];

	strcpy(copy_line1, line);
	strcpy(copy_line2, line);

	char *p = strtok(line, " ");
	p = strtok(NULL, " ");
	strcpy(name_user, p);

	p = strtok(copy_line1, "\"");
	p = strtok(NULL, "\"");
	strcpy(name_book, p);
}
/**
 * @brief Updates both the database and the library when a user losts a book 
 * 
 * @param line 
 * @param database_users 
 * @param library 
 */
void lost_book(char *line, hashtable *database_users, hashtable *library)
{
	char name_book[BOOK_MAX];
	char name_user[MAX];
	char copy_line[MAX_LINE];
	strcpy(copy_line, line);

	extract_arg_for_lost(line, name_user, name_book);

	if (has_key(database_users, name_user) == 0) {
		printf("You are not registered yet.\n");
		return;
	}

	user_t *user;
	user = (user_t *)get(database_users, name_user);

	if (user->banned == 1) {
		printf("You are banned from this library.\n");
		return;
	}

	/* The points of the user must be decreased with 50 and the user
	should be banned if the scores becomes a negative number */
	if (user->points - 50 < 0) {
		user->banned = 1;
		printf("The user %s has been banned from this library.\n", name_user);
	}

	user->points -= 50;
	user->borrowed = 0;
	user->days_available = 0;

	remove_book_from_library(copy_line, library);
}
