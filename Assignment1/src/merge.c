// Copyright Sindrilaru Catalina-Maria, 312CA, 2022
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "defines.h"
#include "merge.h"
#include "delete.h"
#include "add.h"
#include "utilis.h"

/**
 * @brief Go through the two given lists and form a new list (the merged one)
 * 
 * @param merged_deck 
 * @param deck1 
 * @param deck2 
 */
void merge_two_decks(doubly_linked_list_t *merged_deck, doubly_linked_list_t
					 *deck1, doubly_linked_list_t *deck2)
{
	dll_node_t *curr1, *curr2;
	curr1 = deck1->head;
	curr2 = deck2->head;

	/* Each time adds a card from each deck */
	while (curr1 != NULL && curr2 != NULL) {
		add_card_to_deck(merged_deck, (card_t *)curr1->data);
		add_card_to_deck(merged_deck, (card_t *)curr2->data);
		curr1 = curr1->next;
		curr2 = curr2->next;
	}

	/* Scrolls through the two decks to see what cards are left */
	while (curr1 != NULL) {
		add_card_to_deck(merged_deck, (card_t *)curr1->data);
		curr1 = curr1->next;
	}

	while (curr2 != NULL) {
		add_card_to_deck(merged_deck, (card_t *)curr2->data);
		curr2 = curr2->next;
	}
}

/**
 * @brief  Verifies the condition and eventually adds the merged deck on the list
 * 		   and then removes the two initial decks
 * 
 * @param list_decks 
 * @param index1 
 * @param index2 
 */
void merge_decks(doubly_linked_list_t *list_decks, int index1, int index2)
{
	if (index1 >= list_decks->size || index2 >=  list_decks->size) {
		invalid_deck_index();
		return;
	}

	if (index1 < 0 || index2 < 0) {
		invalid_deck_index();
		return;
	}

	dll_node_t *deck1, *deck2;

	/* Finds the decks with the given indexes */
	if (index1 == 0) {
		deck1 = list_decks->head;
	} else {
		deck1 = get_previous_node(list_decks, index1);
		deck1 = deck1->next;
	}

	if (index2 == 0) {
		deck2 = list_decks->head;
	} else {
		deck2 = get_previous_node(list_decks, index2);
		deck2 = deck2->next;
	}

	/* The lists are the data from the nodes */
	doubly_linked_list_t *wanted_deck1, *wanted_deck2;
	wanted_deck1 = deck1->data;
	wanted_deck2 = deck2->data;

	doubly_linked_list_t *merged_deck;
	merged_deck = dll_create(sizeof(card_t));

	/* Creates the new deck from the union of the two lists */
	merge_two_decks(merged_deck, wanted_deck1, wanted_deck2);

	add_deck_to_main_list(list_decks, merged_deck);

	/* Deletes the initial decks */
	if (index1 < index2) {
		del_deck(list_decks, index1);
		del_deck(list_decks, index2 - 1);
	} else {
		del_deck(list_decks, index2);
		del_deck(list_decks, index1 - 1);
	}

	free(merged_deck);
	printf("The deck %d and the deck %d were successfully merged.\n",
		   index1, index2);
}
