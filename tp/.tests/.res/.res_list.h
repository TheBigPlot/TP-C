#ifndef R_LIST_H
#define R_LIST_H

#include <stdlib.h>
#include <stdio.h>

#include "../../structs.h"

// Initialize the sentinel of an empty list.
//sentinel value must be -42
void r_list_init(list* l);

//alloc a list and initialise the list value with nb
//its next pointer has to be NULL
//you have to handle allocation errors
//it is like creating an element with an ask value
list* r_create_list(int nb);

// Return true if the list is empty.
// Otherwise, return false.
// Do not forget that there is always a sentinel.
// So the list is empty if the sentinel does not point to a next element.
int r_list_is_empty(list *l);

// Return the length of the list (sentinel excluded).
size_t r_list_len(list *l);


// get the n-ieme elements of the linked-list l
list* r_list_get(list* l, size_t n);


// Insert 'elm' in front of the list, that is just after the sentinel.
// Note that 'elm' is already an existing element.
// You just have to insert it.
void r_list_push_front(list *l, list *elm);

// Insert 'elm' in the end of the list, that is just after the sentinel.
// Note that 'elm' is already an existing element.
// You just have to insert it.
void r_list_push_end(list *l, list *elm);

// Insert 'elm' at the n-ieme position.
// Note that 'elm' is already an existing element.
// You just have to insert it.
void r_list_insert(list *l, list *elm, size_t n);

//Insert 'elm' in the l in a way that l is still sorted after

void r_insert_in_sorted_list(list* l, list* elm);

// Extract the first element (not the sentinel) of the list.
// This operation removes the element from the list and returns it
// (the caller is responsible for freeing it).
// If the list is empty, the function returns NULL.
list * r_list_pop_front(list *l);

list* r_list_remove(list* l, size_t n);


//use a naive search algorithm to search val in list
//return the first occurence of the element if found
//else return NULL
list* r_list_search(list* l, int val);


//same as list_search but use the dichotomia algorithm
list* r_list_binary_search(list* l, int val);

void r_list_insert_sort(list* l);


void r_FreeList(list* l);

#endif
