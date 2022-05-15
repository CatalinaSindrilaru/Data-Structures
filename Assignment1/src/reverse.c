// Copyright Sindrilaru Catalina-Maria, 312CA, 2022

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "defines.h"
#include "reverse.h"
#include "utilis.h"


/**
 * @brief Reverses the order of the nodes from a list
 * 
 * @param list 
 */
void reverse_wanted_deck(doubly_linked_list_t *list)
{
	if (list->head == NULL || list->head->next == NULL) {
		return;
	}

	dll_node_t *curr, *aux;
	curr = list->head;

	while (curr != NULL) {
		aux = curr->next;
		curr->next = curr->prev;
		curr->prev = aux;
		curr = aux;
	}

	aux = list->head;
	list->head = list->tail;
	list->tail = aux;
}

/**
 * @brief Find the deck with the given index and reverses their cards
 * 
 * @param list_decks 
 * @param deck_index 
 */
void reverse_deck(doubly_linked_list_t *list_decks, int deck_index)
{
	if (deck_index < 0 || deck_index >= list_decks->size) {
		invalid_deck_index();
		return;
	}

	dll_node_t *curr;
	if (deck_index == 0) {
		curr = list_decks->head;
	} else {
		curr = get_previous_node(list_decks, deck_index);
		curr = curr->next;
	}

	doubly_linked_list_t *wanted_deck;
	wanted_deck = curr->data;

	reverse_wanted_deck(wanted_deck);
	printf("The deck %d was successfully reversed.\n", deck_index);
}
