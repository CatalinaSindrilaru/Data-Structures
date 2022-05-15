// Copyright Sindrilaru Catalina-Maria, 312CA, 2022

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "defines.h"
#include "split.h"
#include "add.h"
#include "delete.h"
#include "utilis.h"

/**
 * @brief Divides a deck into two decks based on a given split index
 * 
 * @param list_decks 
 * @param deck_index 
 * @param split_index 
 */
void split_deck(doubly_linked_list_t *list_decks, int deck_index,
				int split_index)
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

	if (split_index < 0 || split_index >= wanted_deck->size) {
		invalid_card_index(deck_index);
		return;
	}

	if (split_index == 0) {
		printf("The deck %d was successfully split by index %d.\n",
			   deck_index, split_index);
		return;
	}

	dll_node_t *node_split;
	node_split  = get_previous_node(wanted_deck, split_index);
	node_split = node_split->next;

	/* Creates two auxiliary lists */
	doubly_linked_list_t *aux1, *aux2;
	aux1 = dll_create(sizeof(card_t));
	aux2 = dll_create(sizeof(card_t));

	dll_node_t *node;
	node = wanted_deck->head;

	/* Adds the nodes before split index in aux1 list */
	while (node != node_split) {
		add_card_to_deck(aux1, node->data);
		node = node->next;
	}

	/* Adds the nodes starting with split index in aux2 list */
	while (node_split != NULL) {
		add_card_to_deck(aux2, node_split->data);
		node_split = node_split->next;
	}

	/* Adds the two auxilary lists to the "main" list */
	add_deck_after_curr(list_decks, curr, aux2);
	add_deck_after_curr(list_decks, curr, aux1);
	free(aux1);
	free(aux2);

	/* Removes the initial deck from the "main" list*/
	del_deck(list_decks, deck_index);

	printf("The deck %d was successfully split by index %d.\n",
		   deck_index, split_index);
}
