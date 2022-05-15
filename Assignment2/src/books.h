// Copyright Sindrilaru Catalina-Maria, 312CA, 2022

#ifndef BOOKS_H_
#define BOOKS_H_

void read_definitions(char *book_name, int number_def, hashtable *library);
void add_book_to_library(char *line, hashtable *library);
void get_book_from_library(char *line, hashtable *library);
void remove_book_from_library(char *line, hashtable *library);
void free_books(hashtable *library);



#endif  // BOOKS_H_
