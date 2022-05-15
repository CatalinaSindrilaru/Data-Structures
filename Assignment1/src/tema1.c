// Copyright Sindrilaru Catalina-Maria, 312CA, 2022

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "defines.h"
#include "add.h"
#include "delete.h"
#include "free.h"
#include "show.h"
#include "reverse.h"
#include "merge.h"
#include "split.h"
#include "shuffle.h"
#include "sort.h"
#include "utilis.h"

int main(void)
{
	doubly_linked_list_t *list_decks;
	list_decks = dll_create(sizeof(doubly_linked_list_t));

	char line[MAX_LINE], command[MAX_LEN_STRING];

	int index1 = 0, index2 = 0, number = 0;
	while(1) {
		memset(line, 0, MAX_LINE);
		memset(command, 0, MAX_LEN_STRING);
		fgets(line, MAX_LINE, stdin);
		line[strlen(line) - 1] = '\0';
		extract_arguments(line, command, &index1, &index2, &number);

		if (strcmp(command, "ADD_DECK") == 0 && number == 2) {
			add_deck(list_decks, index1);

		} else if (strcmp(command, "DEL_DECK") == 0 && number == 2) {
			int ok = 0;
			if (index1 >= 0 && index1 < list_decks->size) {
				ok = 1;
			}
			del_deck(list_decks, index1);
			if (ok == 1) {
				printf("The deck %d was successfully deleted.\n", index1);
			}

		} else if (strcmp(command, "DEL_CARD") == 0 && number == 3) {
			del_card(list_decks, index1, index2);

		} else if (strcmp(command, "ADD_CARDS") == 0 && number == 3) {
			add_cards(list_decks, index1, index2);

		} else if (strcmp(command, "DECK_NUMBER") == 0 && number == 1) {
			show_deck_number(list_decks);

		} else if (strcmp(command, "DECK_LEN") == 0 && number == 2) {
			show_deck_len(list_decks, index1);

		} else if (strcmp(command, "SHUFFLE_DECK") == 0 && number == 2) {
			shuffle_deck(list_decks, index1);

		} else if (strcmp(command, "MERGE_DECKS") == 0 && number == 3) {
			merge_decks(list_decks, index1, index2);

		} else if (strcmp(command, "SPLIT_DECK") == 0 && number == 3) {
			split_deck(list_decks, index1, index2);

		} else if (strcmp(command, "REVERSE_DECK") == 0 && number == 2) {
			reverse_deck(list_decks, index1);

		} else if (strcmp(command, "SHOW_DECK") == 0 && number == 2) {
			show_deck(list_decks, index1);

		} else if (strcmp(command, "SHOW_ALL") == 0 && number == 1) {
			show_all_decks(list_decks);

		} else if (strcmp(command, "EXIT") == 0 && number == 1) {
			free_list_decks(&list_decks);
			break;

		} else if (strcmp(command, "SORT_DECK") == 0 && number == 2) {
			sort_deck(list_decks, index1);

		} else {
			printf("Invalid command. Please try again.\n");
		}
	}

	return 0;
}
