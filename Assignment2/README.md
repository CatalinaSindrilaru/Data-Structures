NAME: Sindrilaru Catalina-Maria

GROUP: 312CA
***

# Homework 2 - The Library of HashBabel

## Description
***
### Organisation
***
I implemented a hashtable for the books where the key is the name of the 
book and the value is a struct where I retained another hashtable with the
definitions of the book and also another characteristics like if it is in the
library or borrowed from someone, how many times has it been borrowed, the 
number of points accumulated from users and also the current rating.
The hashtable of definitions inside the previous struct has both the key and
the value a string.

I also implemented a hashtable for the users (like a database) where the key
is the name of the user and the value is a struct that contains the book 
that the user has already borrowed (if he has), the status of the user 
(banned or not), if the user already has a book at home, the number of days he
said he would return the book and also his points.
***
### Implementation
***
I made functions for each command received from the keyboard about books or users.
(The specific arguments for each command are extracted with separate functions).
* To resize a hashtable I verified in the `put()` function if the load
  factor is > 1 and if it is i called the function `resize_hashtable()` where i create
  a new hashtable with double the size of the original one. I went through the initial
  hashtable and recalculated the hash for each element and then put it in the new hashtable.
  Then I free the old hashtable.
* In order to display all the books or users in the desired order, I created for each one 
  a linked list in which I put the elements. This made it easier to sort with the Bubble 
  Sort Algorithm in the desired order. The i used the sorted lists to show all the books
  and users.
## Comments and resources
* I learned how to implement and use a hashtable and how important and
  efficient it is. 
* In the implementation of this homework i used the functions for the
  linked list and hashtable from the data structure laboratory. Also
  I reinterpreted the well-known algorithm of Bubble sort applied and
  applied it to a linked list.
