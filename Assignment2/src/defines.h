// Copyright Sindrilaru Catalina-Maria, 312CA, 2022

#ifndef DEFINES_H_
#define DEFINES_H_

#define HMAX 10
#define MAX_LINE 256
#define MAX 20
#define BOOK_MAX 40

/* Useful macro for handling error codes */
#define DIE(assertion, call_description)                    \
    do {                                    				\
        if (assertion) {                       			    \
            fprintf(stderr, "(%s, %s, %d): ",               \
                    __FILE__, __FUNCTION__, __LINE__);      \
            perror(call_description);                       \
            exit(EXIT_FAILURE);                             \
        }                                                   \
    } while (0)

typedef struct ll_node_t
{	void* data;
	struct ll_node_t *next;
} ll_node_t;

typedef struct linked_list_t
{	ll_node_t *head;
    int data_size;
    int size;
} linked_list_t;

typedef struct info info;
struct info {
	void *key;
	void *value;
};

typedef struct hashtable hashtable;
struct hashtable {
	linked_list_t **buckets;
	int size;
	int hmax;
};

typedef struct book_t book_t;
struct book_t {
	hashtable *ht;
	int reachable;
	int borrows;
	int total_points;
	float rating;
};

typedef struct user_t user_t;
struct user_t {
	char borrowed_book[BOOK_MAX];
	int banned;
	int borrowed;
	int points;
	int days_available;
};

#endif  // DEFINES_H_
