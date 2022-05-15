// Copyright Sindrilaru Catalina-Maria, 312CA, 2022

#ifndef SORT_H_
#define SORT_H_

void assign_number(char symbol[], int *number);
int verif(card_t *card1, card_t *card2);
void insert_node(doubly_linked_list_t *list, void *data);
void sort_deck(doubly_linked_list_t *list_decks, int deck_index);

#endif  // SORT_H_
