// Copyright Sindrilaru Catalina-Maria, 312CA, 2022

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "add.h"
#include "defines.h"
#include "utilis.h"

/**
 * @brief Creates and initializes a double linked list
 * 
 * @param data_size 
 * @return doubly_linked_list_t* 
 */
doubly_linked_list_t* dll_create(int data_size)
{
    doubly_linked_list_t  *list = malloc(sizeof(doubly_linked_list_t));
	DIE(!list, "Malloc failed at list\n");

	list->head = NULL;
	list->tail = NULL;
	list->data_size = data_size;
	list->size = 0;
	return list;
}

/**
 * @brief Adds a card on the last position of the deck list
 * 
 * @param list 
 * @param data 
 */
void add_card_to_deck(doubly_linked_list_t *list, void *data)
{
	dll_node_t *new = malloc(sizeof(dll_node_t));
	DIE(!new, "Malloc failed\n");

	new->next = NULL;
	new->prev = NULL;
	new->data = malloc(sizeof(card_t));
	DIE(!(new->data), "Malloc failed at new->data\n");
	memcpy(new->data, data, sizeof(card_t));


	if (list->head == NULL) {  /* If the list is empty */
		list->head = new;
		list->tail = new;
	} else {
		list->tail->next = new;
		new->prev = list->tail;
		list->tail = new;
	}

	list->size++;
}

/**
 * @brief Receives a list with cards and adds it as data inside a node 
 * 		  in the "main" list
 * 
 * @param list_decks 
 * @param data 
 */
void add_deck_to_main_list(doubly_linked_list_t *list_decks, void *data)
{
	dll_node_t *new = malloc(sizeof(dll_node_t));
	DIE(!new, "Malloc failed at new\n");

	new->next = NULL;
	new->prev = NULL;

	new->data = malloc(sizeof(doubly_linked_list_t));
	DIE(!(new->data), "Malloc failed at new->data\n");
	memcpy(new->data, data, sizeof(doubly_linked_list_t));

	if (list_decks->head == NULL) {
		list_decks->head = new;
		list_decks->tail = new;
	} else {
		list_decks->tail->next = new;
		new->prev = list_decks->tail;
		list_decks->tail = new;
	}

	list_decks->size++;
}

/**
 * @brief Adds a deck of cards to the "main" list
 * 
 * @param list_decks 
 * @param number_of_cards 
 */
void add_deck(doubly_linked_list_t *list_decks, int number_of_cards)
{
	/* Creates the list for a deck of cards */
	doubly_linked_list_t *deck;
	deck = dll_create(sizeof(card_t));

	card_t *card;
	card = malloc(sizeof(card_t));
	DIE(!card, "Malloc failed at card\n");

	int i = 0;
	char line[MAX_LINE];

	/* Reads the cards to fill a deck */
	while (i < number_of_cards) {
		int ok = 0;
		while (ok == 0) {
			memset(line, 0, MAX_LINE);
			fgets(line, MAX_LINE, stdin);
			line[strlen(line) - 1] = '\0';
			int number = 0;

			extract_good_cards(line, &card->value, card->symbol, &number);

			if (check_invalid_card(card, number) == 0) {
				printf("The provided card is not a valid one.\n");
			} else {
				ok = 1;
			}
		}
		/* When the card is a good one, I add it to the deck */
		add_card_to_deck(deck, card);
		i++;
	}

	/* The filled deck is added at the end of the list */
	add_deck_to_main_list(list_decks, deck);
	free(card);
	free(deck);
	printf("The deck was successfully created with %d cards.\n", number_of_cards);
}

/**
 * @brief Reads a number of cards and adds them to the end
 * 		  of a certain deck
 * 
 * @param list_decks 
 * @param deck_index 
 * @param number_of_cards 
 */
void add_cards(doubly_linked_list_t *list_decks, int deck_index,
			   int number_of_cards)
{
	if (deck_index < 0 || deck_index >= list_decks->size) {
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

	/* The list is the data from the found node */
	doubly_linked_list_t *wanted_deck;
	wanted_deck = curr->data;

	card_t *card;
	card = malloc(sizeof(card_t));
	DIE(!card, "Malloc failed at card\n");

	char line[MAX_LINE];
	int i = 0;
	/* Reads the cards to fill a deck */
	while (i < number_of_cards) {
		int ok = 0;
		while (ok == 0) {
			memset(line, 0, MAX_LINE);
			fgets(line, MAX_LINE, stdin);
			line[strlen(line) - 1] = '\0';
			int number = 0;

			extract_good_cards(line, &card->value, card->symbol, &number);

			if (check_invalid_card(card, number) == 0) {
				printf("The provided card is not a valid one.\n");
			} else {
				ok = 1;
			}
		}
		/* When the card is a good one, I add it to the deck */
		add_card_to_deck(wanted_deck, card);
		i++;
	}

	free(card);
	printf("The cards were successfully added to deck %d.\n", deck_index);
}

/**
 * @brief Adds a deck after a given deck from the list
 * 
 * @param list_decks 
 * @param curr 
 * @param new_deck 
 */
void add_deck_after_curr(doubly_linked_list_t *list_decks, dll_node_t *curr,
						 doubly_linked_list_t *new_deck)
{
	dll_node_t *new = malloc(sizeof(dll_node_t));
	DIE(!new, "Malloc failed at new\n");

	new->next = NULL;
	new->prev = NULL;

	new->data = malloc(sizeof(doubly_linked_list_t));
	DIE(!(new->data), "Malloc failed at new->data\n");
	memcpy(new->data, new_deck, sizeof(doubly_linked_list_t));

	if (curr->next == NULL) {
		curr->next = new;
		new->prev = curr;
		list_decks->tail = new;

	} else {
		new->prev = curr;
		new->next = curr->next;
		curr->next->prev = new;
		curr->next = new;
	}

	list_decks->size++;
}
