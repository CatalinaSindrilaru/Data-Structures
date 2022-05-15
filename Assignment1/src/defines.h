// Copyright Sindrilaru Catalina-Maria, 312CA, 2022

#ifndef DEFINES_H_
#define DEFINES_H_

#define MAX_LEN_STRING 20
#define MAX_LINE 30

// Useful macro for handling error codes
#define DIE(assertion, call_description)                    \
    do {                                    				\
        if (assertion) {                       			    \
            fprintf(stderr, "(%s, %s, %d): ",               \
                    __FILE__, __FUNCTION__, __LINE__);      \
            perror(call_description);                       \
            exit(EXIT_FAILURE);                             \
        }                                                   \
    } while (0)

typedef struct card_t{
	int value;
	char symbol[10];
} card_t;

typedef struct dll_node_t
{	void* data;
    struct dll_node_t *prev;
	struct dll_node_t *next;
} dll_node_t;

typedef struct doubly_linked_list_t
{	dll_node_t *head;
	dll_node_t *tail;
    int data_size;
    int size;
} doubly_linked_list_t;

#endif  // DEFINES_H_
