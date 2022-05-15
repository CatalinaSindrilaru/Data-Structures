// Copyright Sindrilaru Catalina-Maria, 312CA, 2022
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "defines.h"
#include "sort.h"
#include "add.h"
#include "delete.h"
#include "utilis.h"

/**
 * @brief Assigns a specific number for each symbol
 * 
 * @param symbol 
 * @param number 
 */
void assign_number(char symbol[], int *number)
{
	char s[4][8] = {"HEART", "SPADE", "DIAMOND", "CLUB"};
	for (int i = 0; i < 4; i++) {
		if (strcmp(symbol, s[i]) == 0) {
			*number = i;
			return;
		}
	}
}

/**
 * @brief Compares two cards according to priority of the values and symbols
 * 
 * @param card1 
 * @param card2 
 * @return int 
 */
int verif(card_t *card1, card_t *card2)
{
	int number1, number2;
	assign_number(card1->symbol, &number1);
	assign_number(card2->symbol, &number2);

	// Returns -1 if the card1 must be place before card2
	if (card1->value < card2->value) {
		return -1;
	} else if (card1->value == card2->value) {
		if (number1 < number2) {
			return -1;
		}
	}
	return 1;
}

/**
 * @brief Insert a card in the list according to its priority
 * 
 * @param list 
 * @param data 
 */
void insert_node(doubly_linked_list_t *list, void *data)
{
	/* Creates a new node with the given data */
	dll_node_t *new = malloc(sizeof(dll_node_t));
	DIE(!new, "Malloc failed at new\n");

	new->next = NULL;
	new->prev = NULL;

	new->data = malloc(sizeof(card_t));
	DIE(!(new->data), "Malloc failed at new->data\n");
	memcpy(new->data, data, sizeof(card_t));

	card_t *card_new = malloc(sizeof(card_t));
	DIE(!card_new, "Malloc failed at card_new\n");
	memcpy(card_new, data, sizeof(card_t));

	dll_node_t *curr;
	curr = list->head;

	card_t *card_curr = malloc(sizeof(card_t));
	DIE(!card_curr, "Malloc failed at card_curr\n");

	/* If the list is empty just adds the new node */
	if (list->size == 0) {
		list->head = new;
		list->tail = new;
	}

	/* If the list has one node, compares the new node just with it */
	if (list->size == 1) {
		memcpy(card_curr, curr->data, sizeof(card_t));
		if (verif(card_new, card_curr) < 0) {
			new->next = curr;
			curr->prev = new;
			list->head = new;
			list->tail = curr;
		} else {
			new->prev = curr;
			curr->next = new;
			list->tail = new;
		}
	}

	/* Compares the new node data with all the nodes until it finds the
	right place */
	if (list->size > 1) {
		int ok = 0;
		while (curr != NULL && ok == 0) {
			memcpy(card_curr, curr->data, sizeof(card_t));
			if (verif(card_new, card_curr) < 0) {
				if (curr == list->head) {
					new->next = curr;
					curr->prev = new;
					list->head = new;
					ok = 1;
				} else {
					new->next = curr;
					new->prev = curr->prev;
					curr->prev->next = new;
					curr->prev = new;
					ok = 1;
				}
			}
			curr = curr->next;
		}

		if (ok == 0) {
			new->prev = list->tail;
			list->tail->next = new;
			list->tail = new;
		}
	}
	list->size++;
	free(card_curr);
	free(card_new);
}

/**
 * @brief Go throught the initial deck and create the sorted deck, with
 * 		  which then replace it
 * 
 * @param list_decks 
 * @param deck_index 
 */
void sort_deck(doubly_linked_list_t *list_decks, int deck_index)
{
	if(deck_index < 0 || deck_index >= list_decks->size) {
		invalid_deck_index();
		return;
	}

	dll_node_t *curr;

	/* Finds the deck with given index */
	if (deck_index == 0) {
		curr = list_decks->head;
	} else {
		curr = get_previous_node(list_decks, deck_index);
		curr = curr->next;
	}

	doubly_linked_list_t *wanted_deck;
	wanted_deck = curr->data;

	doubly_linked_list_t *sorted_deck;
	sorted_deck = dll_create(sizeof(card_t));

	dll_node_t *node;
	node = wanted_deck->head;
	/* Fill in the new deck with sorted items */
	while (node != NULL) {
		insert_node(sorted_deck, node->data);
		node = node->next;
	}

	/* Adds the sorted deck after the initial deck in the list */
	add_deck_after_curr(list_decks, curr, sorted_deck);
	free(sorted_deck);
	/* Removes the initial deck */
	del_deck(list_decks, deck_index);

	printf("The deck %d was successfully sorted.\n", deck_index);
}
