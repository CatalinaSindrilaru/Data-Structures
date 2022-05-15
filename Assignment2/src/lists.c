// Copyright Sindrilaru Catalina-Maria, 312CA, 2022

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "defines.h"
#include "lists.h"

/**
 * @brief Creates a list 
 * 
 * @param data_size 
 * @return linked_list_t* 
 */
linked_list_t* ll_create(int data_size)
{
	linked_list_t  *list = calloc(1, sizeof(linked_list_t));
	DIE(!list, "Calloc failed at list\n");
	list->head = NULL;
	list->data_size = data_size;
	list->size = 0;
	return list;
}

/**
 * @brief Creates a node
 * 
 * @param new_data 
 * @param data_size 
 * @return ll_node_t* 
 */
ll_node_t* create_node(void* new_data, int data_size)
{
	ll_node_t* node = calloc(1, sizeof(ll_node_t));
	DIE(!node, "Calloc failed at node\n");

	node->data = calloc(1, data_size);
	DIE(!node->data, "Calloc failed at node->data\n");
	memcpy(node->data, new_data, data_size);
	return node;
}

/**
 * @brief Returns the desired node 
 * 
 * @param list 
 * @param n 
 * @return ll_node_t* 
 */
ll_node_t* get_nth_node(linked_list_t* list, int n)
{
	int len = list->size - 1;
	int i;
	ll_node_t* node = list->head;

	if (len < n) {
		n = len;
	}

	for (i = 0; i < n; ++i)
		node = node->next;

	return node;
}

/**
 * @brief Adds a node to the list 
 * 
 * @param list 
 * @param n 
 * @param new_data 
 */
void ll_add_nth_node(linked_list_t* list, int n, void* new_data)
{
	ll_node_t *new_node, *prev_node;

	if (!list)
		return;

	new_node = create_node(new_data, list->data_size);

	if (!n || !list->size) {
		new_node->next = list->head;
		list->head = new_node;
	} else {
		prev_node = get_nth_node(list, n - 1);
		new_node->next = prev_node->next;
		prev_node->next = new_node;
	}

	++list->size;
}

/**
 * @brief Returns the size of the list
 * 
 * @param list 
 * @return int 
 */
int ll_get_size(linked_list_t* list)
{
     if (!list) {
        return -1;
    }

    return list->size;
}

/**
 * @brief Deletes and frees memory for a list
 * 
 * @param pp_list 
 */
void ll_free(linked_list_t** pp_list)
{
    ll_node_t* currNode;

    if (!pp_list || !*pp_list) {
        return;
    }

    while (ll_get_size(*pp_list) > 0) {
        currNode = ll_remove_nth_node(*pp_list, 0);
        free(currNode->data);
        currNode->data = NULL;
        free(currNode);
        currNode = NULL;
    }

    free(*pp_list);
    *pp_list = NULL;
}

/**
 * @brief Removes a node from a list
 * 
 * @param list 
 * @param n 
 * @return ll_node_t* 
 */
ll_node_t* ll_remove_nth_node(linked_list_t* list, int n)
{
	ll_node_t *prev_node, *removed_node;

	if (!list || !list->size)
		return NULL;

	if (!n) {
		removed_node = list->head;
		list->head = removed_node->next;
		removed_node->next = NULL;
	} else {
		prev_node = get_nth_node(list, n - 1);
		removed_node = prev_node->next;
		prev_node->next = removed_node->next;
		removed_node->next = NULL;
	}

	--list->size;

	return removed_node;
}
