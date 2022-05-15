Name: Sindrilaru Catalina-Maria

Group: 312CA
***
# Now You See Me - First Homework


This homework aims to store multiple decks of cards using a double 
linked list. The deck themselves will contain a list to hold the cards. For
implementation, I used 3 structures, one for the list (which ontains the head,
the tail, the size and the data size for the list),  one for the node in the
list(which contains the data, the previous and next node relative to the 
current one) and one for the card (contains the value and the symbol for a card).

Initially, I made functions	for creating a double linked list and for 
adding elements in a list.

I read cards and I added the valid ones to a list that represents a deck.
Then I added the deck as a node in the list of decks.

I made two diferent functions for deleting, one to delete a card from a deck
and another to delete all the elements from a deck. For that, I chose to treat 3
cases for: deleting the first node from a list, the last node and a node from 
the inside.

I also implemented various functions to reverse, split, shuffle or merge the
decks.
* THE SHUFFLE FUNCTION reverses the first and the last half of a list. I made
this by adding the first half at the end of the list and then removing the first 
part that remains at the beggining.
* THE MERGE FUNCTION combines two decks and adds the result at the end of the
list of decks. It also removes initial lists.
* THE SPLIT FUNCTION divides a deck into two decks, considering the split 
index. The nodes before split index are added into an auxiliary list and the nodes
after that into another auxiliary list. These two lists are added at the list of 
decks and the initial list is removed.
* THE REVERSE FUNCTION changes the order of connections between nodes, but 
also updates the head and tail of the list.

I created functions to display the decks and all the cards inside them. The decks
can be displayed one by one, as well as all at once.
The memory is freed via the functions of deleting the cards from a deck but also
the decks from the "main" list.

---
This topic made me understand how to use lists correctly and what their usage is.