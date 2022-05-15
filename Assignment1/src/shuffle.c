// Copyright Sindrilaru Catalina-Maria, 312CA, 2022
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "defines.h"
#include "shuffle.h"
#include "add.h"
#include "utilis.h"

/**
 * @brief Reverses the first and second halves of the deck with the given index
 * 
 * @param list_decks 
 * @param deck_index 
 */
void shuffle_deck(doubly_linked_list_t *list_decks, int deck_index)
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

	/* Reverses the deck only if it has more than one card */
	if (wanted_deck->size > 1) {
		dll_node_t *middle, *curr1;
		/* Finds the card from the middle of the deck */
		middle = get_previous_node(wanted_deck, wanted_deck->size / 2);
		middle = middle->next;

		curr1 = wanted_deck->head;

		/* Adds the cards from the first half at the end of the deck */
		while (curr1 != middle) {
			add_card_to_deck(wanted_deck, curr1->data);
			curr1 = curr1->next;
		}

		dll_node_t *node_card;
		node_card = wanted_deck->head;
		/* Deletes the cards from the first half of the deck */
		while (node_card != middle) {
			dll_node_t *remove_card = node_card;
			node_card = node_card->next;
			free(remove_card->data);
			free(remove_card);
			node_card->prev = NULL;
			wanted_deck->size--;
		}
		wanted_deck->head = middle;
	}

	printf("The deck %d was successfully shuffled.\n", deck_index);
}
