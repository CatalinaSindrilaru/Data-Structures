// Copyright Sindrilaru Catalina-Maria, 312CA, 2022

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "defines.h"
#include "utilis.h"

/**
 * @brief Display a message for the invalid card index
 * 
 * @param index 
 */
void invalid_card_index(int index)
{
	printf("The provided index is out of bounds for deck %d.\n", index);
}

/**
 * @brief Display a message for the invalid deck index
 * 
 */
void invalid_deck_index(void)
{
	printf("The provided index is out of bounds for the deck list.\n");
}

// Saves the value, the symbol and the number of arguments on a line
/**
 * @brief 
 * 
 * @param line 
 * @param value 
 * @param symbol 
 * @param number 
 */
void extract_good_cards(char line[], int *value, char *symbol, int *number)
{
	char *word;
	word = strtok(line, " ");
	*number = 0;
	while (word != NULL) {
		if (*number == 0) {
			*value = atoi(word);
		} else if (*number == 1){
			strcpy(symbol, word);
		}
		*number += 1;
		word = strtok(NULL, " ");
	}
}

/**
 * @brief Verifies if a card has a value between 1 and 14 and a valid symbol
 * 
 * @param card 
 * @param number 
 * @return int 
 */
int check_invalid_card(card_t *card, int number)
{
	if (number != 2) {
		return 0;
	}
	char s[4][8] = {"HEART", "CLUB", "DIAMOND", "SPADE"};
	if (card->value < 1 || card->value > 14) {
		return 0;
	}
	if (strcmp(card->symbol, s[0]) != 0 && strcmp(card->symbol, s[1]) != 0
		&& strcmp(card->symbol, s[2]) != 0 && strcmp(card->symbol, s[3]) != 0) {
			return 0;
	}
	return 1;
}

/**
 * @brief Returns the node before the node with the given number
 * 
 * @param list 
 * @param number 
 * @return dll_node_t* 
 */
dll_node_t* get_previous_node(doubly_linked_list_t *list, int number)
{
	int  i  = 0;

	if (number == i) {
		return list->head;
	}

	dll_node_t *curr;
	curr = list->head;
	i++;

	while (i < number) {
		curr = curr->next;
		i++;
	}

	return curr;
}

/**
 * @brief Saves the command and maximum two indexes and also the total number of
 * 		  the arguments on the line
 * 
 * @param line 
 * @param command 
 * @param index1 
 * @param index2 
 * @param number 
 */
void extract_arguments(char line[], char command[], int *index1, int *index2,
					   int *number)
{
	char *word;
	word = strtok(line, " ");
	*index1 = 0;
	*index2 = 0;
	*number = 0;
	while (word != NULL) {
		if (*number == 0) {
			strcpy(command, word);
		} else if (*number == 1){
			*index1 = atoi(word);
		} else if (*number == 2) {
			*index2 = atoi(word);
		}
		*number += 1;
		word = strtok(NULL, " ");
	}
}
