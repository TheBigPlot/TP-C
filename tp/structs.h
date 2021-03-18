#ifndef STRUCTS_H
#define STRUCTS_H

#define _GNU_SOURCE 
#include <dlfcn.h>


typedef struct list list;
struct list {
  int val;
  list* next;
};

typedef struct graph graph;
struct graph{
  int is_directed;
  int order;
  list** adjlists;
};

typedef struct queue queue;
struct queue{
  list* Queue;
};


typedef void (*Func) (char*, int);

#endif
