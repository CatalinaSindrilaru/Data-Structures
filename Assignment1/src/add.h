// Copyright Sindrilaru Catalina-Maria, 312CA, 2022

#ifndef ADD_H_
#define ADD_H_

#include "defines.h"

doubly_linked_list_t* dll_create(int data_size);
void add_card_to_deck(doubly_linked_list_t *list, void *data);
void add_deck_to_main_list(doubly_linked_list_t *list_decks, void *data);
void add_deck(doubly_linked_list_t *list_decks, int number_of_cards);
void add_cards(doubly_linked_list_t *list_decks, int deck_index,
			   int number_of_cards);
void add_deck_after_curr(doubly_linked_list_t *list_decks, dll_node_t *curr,
						 doubly_linked_list_t *new_deck);

#endif  // ADD_H_
