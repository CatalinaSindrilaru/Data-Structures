// Copyright Sindrilaru Catalina-Maria, 312CA, 2022

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "defines.h"
#include "lists.h"
#include "hashtable.h"
#include "books.h"
#include "definitions.h"
#include "users.h"
#include "show.h"


void swap(ll_node_t *a, ll_node_t *b)
{
	info  *aux = a->data;
	a->data = b->data;
	b->data = aux;
}

/**
 * @brief Applies the Bubble-Sort algorithm to the linked list that contains
		  all the books in the library 
 * 
 * @param list 
 */
void bubble_sort_library(linked_list_t *list)
{
	int swapped;
	ll_node_t *curr;
	ll_node_t *ptr = NULL;

	ll_node_t *start = list->head;
	if (start == NULL) {
		return;
	}

	do {
		swapped = 0;
		curr = start;
		/* Sort the books from the list by rating, then by number of loans, 
		and then by lexicographic order */
		while (curr->next != ptr) {
			/* Extract two succesive books */
			info *data1 = (info *)curr->data;
			book_t *book1 = (book_t *)data1->value;

			info *data2 = (info *)curr->next->data;
			book_t *book2 = (book_t *)data2->value;

			if (book1->rating < book2->rating) {
				swap(curr, curr->next);
				swapped = 1;

			} else if (book1->rating == book2->rating
					   && book1->borrows < book2->borrows) {
				swap(curr, curr->next);
				swapped = 1;

			} else if (book1->rating == book2->rating
					   && book1->borrows == book2->borrows) {
				if (strcmp((char *)data1->key, (char *)data2->key) > 0) {
					swap(curr, curr->next);
					swapped = 1;
				}
			}
			curr = curr->next;
		}
		ptr = curr;
	} while (swapped);
}

/**
 * @brief Display all the books from the library with their characteristics
		  in the desired order
 * 
 * @param library 
 */
void display_top_books(hashtable *library)
{
	/* Create a list of all the books in the library */
	linked_list_t *list;
	list = ll_create(sizeof(info));

	for (int i = 0; i < library->hmax; i++) {
		linked_list_t *bucket;
		bucket = library->buckets[i];
		ll_node_t *curr = bucket->head;

		info *aux;
		while (curr != NULL) {
			aux = (info *)curr->data;
			ll_add_nth_node(list, list->size, aux);
			curr = curr->next;
		}
	}

	/* Sort the list */
	bubble_sort_library(list);

	ll_node_t *curr;
	curr = list->head;

	printf("Books ranking:\n");
	int cnt = 1;

	while (curr != NULL) {
		info *data = (info *)curr->data;
		book_t *book = (book_t *)data->value;
		printf("%d. Name:%s Rating:%.3f Purchases:%d\n", cnt,
		       (char *)data->key, book->rating, book->borrows);
		curr = curr->next;
		cnt++;
	}

	ll_free(&list);
}

/**
 * @brief Applies the Bubble-Sort algorithm to the linked list that contains
		  all the users in the database
 * 
 * @param list 
 */
void bubble_sort_users(linked_list_t *list)
{
	int swapped;
	ll_node_t *curr;
	ll_node_t *ptr = NULL;

	ll_node_t *start = list->head;
	if (start == NULL) {
		return;
	}

	do {
		swapped = 0;
		curr = start;
		/* Sort the users from the list by points and then
		 by lexicographic order */
		while (curr->next != ptr) {
			info *data1 = (info *)curr->data;
			user_t *user1 = (user_t *)data1->value;

			info *data2 = (info *)curr->next->data;
			user_t *user2 = (user_t *)data2->value;

			if (user1->points < user2->points) {
				swap(curr, curr->next);
				swapped = 1;

			} else if (user1->points == user2->points) {
				if (strcmp((char *)data1->key, (char *)data2->key) > 0) {
					swap(curr, curr->next);
					swapped = 1;
				}
			}
			curr = curr->next;
		}
		ptr = curr;
	} while (swapped);
}

/**
 * @brief Display all the eligible users from the database with their names and
		  points in the desired order
 * 
 * @param database_users 
 */
void display_top_users(hashtable *database_users)
{
	/* Create a list of all the users in the database */
	linked_list_t *list;
	list = ll_create(sizeof(info));

	for (int i = 0; i < database_users->hmax; i++) {
		linked_list_t *bucket;
		bucket = database_users->buckets[i];
		ll_node_t *curr = bucket->head;

		info *aux;
		while (curr != NULL) {
			aux = (info *)curr->data;
			ll_add_nth_node(list, list->size, aux);
			curr = curr->next;
		}
	}

	/* Sort the list */
	bubble_sort_users(list);

	ll_node_t *curr;
	curr = list->head;

	printf("Users ranking:\n");
	int cnt = 1;

	while (curr != NULL) {
		info *data = (info *)curr->data;
		user_t *user = (user_t *)data->value;
		if (user->banned == 0) {
			printf("%d. Name:%s Points:%d\n", cnt, (char *)data->key, user->points);
			cnt++;
		}
		curr = curr->next;
	}

	ll_free(&list);
}
