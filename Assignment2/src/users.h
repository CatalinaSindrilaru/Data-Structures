// Copyright Sindrilaru Catalina-Maria, 312CA, 2022

#ifndef USERS_H_
#define USERS_H_

void add_user(char *line, hashtable *database_users);
void borrow_book(char *line, hashtable *database_users, hashtable *library);
void return_book(char *line, hashtable *database_users, hashtable *library);
void lost_book(char *line, hashtable *database_users, hashtable *library);

#endif  // USERS_H_
