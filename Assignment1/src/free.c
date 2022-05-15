// Copyright Sindrilaru Catalina-Maria, 312CA, 2022

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "defines.h"
#include "free.h"

/**
 * @brief  Deletes all the cards from a deck and frees the allocated memory
 * 
 * @param list 
 */
void free_cards_from_deck(doubly_linked_list_t *list)
{
	dll_node_t *curr, *curr2;
	curr = list->head;
	curr2 = curr;

	while (curr->next != NULL) {
		curr = curr->next;
		free(curr2->data);
		free(curr2);
		curr2 = curr;
	}

	free(curr2->data);
	free(curr2);
	free(list);
}

/**
 * @brief  Deletes all the decks from the list and frees the allocated memory
 * 
 * @param list_decks 
 */
void free_list_decks(doubly_linked_list_t **list_decks)
{
	dll_node_t *curr;
	curr = (*list_decks)->head;

	while (curr != NULL) {
		dll_node_t *remove_deck = curr;
		doubly_linked_list_t *wanted_deck = remove_deck->data;
		dll_node_t *node_card;
		node_card = wanted_deck->head;
		/* Removes the cards from the current deck */
		while (node_card != NULL) {
			dll_node_t *remove_card = node_card;
			node_card = node_card->next;
			free(remove_card->data);
			free(remove_card);
		}
		curr = curr->next;
		free(remove_deck->data);
		free(remove_deck);
	}
	free((*list_decks));
}
