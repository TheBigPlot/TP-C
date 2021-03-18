#ifndef TOOLS_H
#define TOOLS_H

#include "../structs.h"

void printArr(int* arr, size_t len);
int* copy_array(int* src, size_t len);
int* generate_int_array(int n);
int array_equals(int* a, int* b, int len);
void insert_sort(int arr[], int n);

list* make_list(int n);
void printList(list* l);
int list_equals(list* l1, list* l2);
list* copy_list(list* l);
list* list_from_array(int* arr, int len);

graph* generate_full_graph(int order, int is_directed);
void todot(graph* G);

#endif
