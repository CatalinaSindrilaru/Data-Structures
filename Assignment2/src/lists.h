// Copyright Sindrilaru Catalina-Maria, 312CA, 2022

#ifndef LISTS_H_
#define LISTS_H_

linked_list_t* ll_create(int data_size);
ll_node_t* create_node(void* new_data, int data_size);
ll_node_t* get_nth_node(linked_list_t* list, int n);
void ll_add_nth_node(linked_list_t* list, int n, void* new_data);
int ll_get_size(linked_list_t* list);
void ll_free(linked_list_t** pp_list);
ll_node_t* ll_remove_nth_node(linked_list_t* list, int n);

#endif  // LISTS_H_
