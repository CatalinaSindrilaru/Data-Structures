// Copyright Sindrilaru Catalina-Maria, 312CA, 2022

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "defines.h"
#include "delete.h"
#include "free.h"
#include "utilis.h"

/**
 * @brief  Deletes a node (a deck of cards) from the list of decks
 * 
 * @param list_decks 
 * @param deck_index 
 */
void del_deck(doubly_linked_list_t *list_decks, int deck_index)
{
	dll_node_t *curr, *curr2;
	if (deck_index < 0 || deck_index >= list_decks->size) {
		invalid_deck_index();
		return;

	} else if (deck_index == 0) {  /* deletes the first deck */
		curr = list_decks->head;

		if (list_decks->size != 1) {
			list_decks->head = list_decks->head->next;
			list_decks->head->prev = NULL;
		}

		doubly_linked_list_t *aux;
		aux = curr->data;
		free_cards_from_deck(aux);
		free(curr);

	} else if (deck_index == list_decks->size - 1) {  /* deletes the last deck */
		curr = list_decks->tail;
		list_decks->tail->prev->next = NULL;
		list_decks->tail = list_decks->tail->prev;
		doubly_linked_list_t *aux;
		aux = curr->data;
		free_cards_from_deck(aux);
		free(curr);

	} else if (deck_index > 0 && deck_index < list_decks->size - 1) {
		/* if the deck is neither the first nor last in the list */
		curr = get_previous_node(list_decks, deck_index);
		curr2 = curr->next;
		curr->next = curr2->next;
		curr2->next->prev = curr;
		doubly_linked_list_t *aux;
		aux = curr2->data;
		free_cards_from_deck(aux);
		free(curr2);
	}

	list_decks->size--;
	/* if the list remains empty */
	if (list_decks->size == 0) {
		list_decks->head = NULL;
		list_decks->tail = NULL;
	}
}

/**
 * @brief Deletes one specific card from a certain deck
 * 
 * @param list_decks 
 * @param deck_index 
 * @param card_index 
 */
void del_card(doubly_linked_list_t *list_decks, int deck_index, int card_index)
{
	dll_node_t *curr;
	if (deck_index < 0 || deck_index >= list_decks->size) {
		invalid_deck_index();
		return;
	}

	/* finds the deck with given index */
	if (deck_index == 0) {
		curr = list_decks->head;
	} else {
		curr = get_previous_node(list_decks, deck_index);
		curr = curr->next;
	}

	doubly_linked_list_t *wanted_deck;
	wanted_deck = curr->data;

	if (card_index == 0 && wanted_deck->size == 1) {
		/* the deck has only one card so it must be completely erased */
		del_deck(list_decks, deck_index);

	} else if (card_index == 0) {  /* deletes the first card */
		dll_node_t *curr;
		curr = wanted_deck->head;
		curr->next->prev = NULL;
		wanted_deck->head = wanted_deck->head->next;
		free(curr->data);
		free(curr);
		wanted_deck->size--;

	} else if (card_index == wanted_deck->size - 1) {  /* deletes the last card */
		dll_node_t *curr;
		curr = wanted_deck->tail;
		curr->prev->next = NULL;
		wanted_deck->tail = wanted_deck->tail->prev;
		free(curr->data);
		free(curr);
		wanted_deck->size--;

	} else if (card_index > 0 && card_index < wanted_deck->size - 1) {
		/* if the card is neither the first nor last in the deck */
		dll_node_t *wanted_card_previous, *wanted_card;
		wanted_card_previous = get_previous_node(wanted_deck, card_index);
		wanted_card = wanted_card_previous->next;
		wanted_card_previous->next = wanted_card->next;
		wanted_card->next->prev = wanted_card_previous;
		free(wanted_card->data);
		free(wanted_card);
		wanted_deck->size--;

	} else {
		invalid_card_index(deck_index);
		return;
	}

	printf("The card was successfully deleted from deck %d.\n", deck_index);
}

