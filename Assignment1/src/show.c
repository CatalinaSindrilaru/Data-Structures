// Copyright Sindrilaru Catalina-Maria, 312CA, 2022

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "defines.h"
#include "show.h"
#include "utilis.h"

/**
 * @brief Display how many decks are in the "main" list
 * 
 * @param list_decks 
 */
void show_deck_number(doubly_linked_list_t *list_decks)
{
	printf("The number of decks is %d.\n", list_decks->size);
}

/**
 * @brief Display how many cards are in the deck with the given index
 * 
 * @param list_decks 
 * @param deck_index 
 */
void show_deck_len(doubly_linked_list_t *list_decks, int deck_index)
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

	printf("The length of deck %d is %d.\n", deck_index, wanted_deck->size);
}

/**
 * @brief Display all the cards from the deck with the given index
 * 
 * @param list_decks 
 * @param deck_index 
 */
void show_deck(doubly_linked_list_t *list_decks, int deck_index)
{
	if(deck_index < 0 || deck_index >= list_decks->size) {
		invalid_deck_index();
		return;
	}

	dll_node_t *curr;

	/* Finds the deck with given index */
	if (deck_index > 0) {
		curr = get_previous_node(list_decks, deck_index);
		curr = curr->next;
	} else {
		curr = list_decks->head;
	}

	doubly_linked_list_t *wanted_deck;
	wanted_deck = curr->data;

	dll_node_t *aux;
	aux = wanted_deck->head;
	card_t *contain;

	printf("Deck %d:\n", deck_index);
	/* Scroll through the entire deck and display the data from each node */
	for (int i = 0; i < wanted_deck->size; i++) {
		contain = aux->data;
		printf("\t%d %s\n", contain->value, contain->symbol);
		aux = aux->next;
	}
}

/**
 * @brief Display all the decks from the "main" list
 * 
 * @param list_decks 
 */
void show_all_decks(doubly_linked_list_t *list_decks)
{
	int i = 0;

	while (i < list_decks->size){
		show_deck(list_decks, i);
		i++;
	}
}
