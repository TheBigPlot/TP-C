#ifndef LIST_H
#define LIST_H

#include <stdlib.h>
#include <stdio.h>

#include "../structs.h"

// Initialize the sentinel of an empty list.
//sentinel value must be -42
void list_init(list* l);

//alloc a list and initialise the list value with nb
//its next pointer has to be NULL
//you have to handle allocation errors
//it is like creating an element with an ask value
list* create_list(int nb);

// Return true if the list is empty.
// Otherwise, return false.
// Do not forget that there is always a sentinel.
// So the list is empty if the sentinel does not point to a next element.
int list_is_empty(list *l);

// Return the length of the list (sentinel excluded).
size_t list_len(list *l);


// get the n-ieme elements of the linked-list l
list* list_get(list* l, size_t n);


// Insert 'elm' in front of the list, that is just after the sentinel.
// Note that 'elm' is already an existing element.
// You just have to insert it.
void list_push_front(list *l, list *elm);

// Insert 'elm' in the end of the list, that is just after the sentinel.
// Note that 'elm' is already an existing element.
// You just have to insert it.
void list_push_end(list *l, list *elm);

// Insert 'elm' at the n-ieme position.
// Note that 'elm' is already an existing element.
// You just have to insert it.
void list_insert(list *l, list *elm, size_t n);

//Insert 'elm' in the l in a way that l is still sorted after

void insert_in_sorted_list(list* l, list* elm);

// Extract the first element (not the sentinel) of the list.
// This operation removes the element from the list and returns it
// (the caller is responsible for freeing it).
// If the list is empty, the function returns NULL.
list *list_pop_front(list *l);

//Remove the n-ieme element of the list and return it
//if n > list length return NULL
list* list_remove(list* l, size_t n);


//use a naive search algorithm to search val in list
//return the first occurence of the element if found
//else return NULL
list* list_search(list* l, int val);


//Free all the elements of a List
void FreeList(list* l);

#endif
