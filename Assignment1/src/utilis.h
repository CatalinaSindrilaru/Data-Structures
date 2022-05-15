// Copyright Sindrilaru Catalina-Maria, 312CA, 2022

#ifndef UTILIS_H_
#define UTILIS_H_

#include "defines.h"

void invalid_card_index(int index);
void invalid_deck_index(void);
void extract_good_cards(char line[], int *value, char *symbol, int *number);
int check_invalid_card(card_t *card, int number);
dll_node_t* get_previous_node(doubly_linked_list_t *list, int number);
void extract_arguments(char line[], char command[], int *index1, int *index2,
					   int *number);

#endif  // UTILIS_H_
