#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>

#include "alloc.h"
#include ".tests/.garbage.h"

extern plist* garbage;
extern size_t all_alloc;
extern size_t all_free;
extern size_t all_realloc;


//the free that will be use by the user
void free(void *ptr) {
  if (!ptr) return;

  //one more free done
  all_free ++;
  //remove the pointer from the garbage collector
  plist* pfreed = garbage_remove(garbage,ptr);
  
  //pointer to stock real free function
  void (*vraiFree) (void *);

  // Get true free in the system lib
  
  vraiFree = (void *) dlsym(RTLD_NEXT, "free"); 

  //there is a problem with the getting of free
  if (vraiFree == NULL) {
    abort();
  }
  (*vraiFree) (ptr); // call of free
  g_free(pfreed);
}

//the malloc which will be use by the user
void *malloc(size_t size) {
  void * (*vraiMalloc) (size_t); // creation of a pointer to get the true malloc
  vraiMalloc = dlsym(RTLD_NEXT, "malloc");
  void *res = (*vraiMalloc) (size);
  
  //one more alloc done
  all_alloc ++;
  garbage_add(garbage,create_garbage(res));

  return res;
}


void* realloc(void* ptr, size_t size)
{
  if (!ptr) return;
  
  //pointer to get real realloc
  void* (*vraiRealloc) (void*, size_t);
  vraiRealloc = dlsym(RTLD_NEXT, "realloc");

  if (vraiRealloc == NULL)
    {
      abort();
    }
  
  void *res = (*vraiRealloc)(ptr,size);
  all_realloc ++;

  return res;
}



void r_free(void *ptr) {
  if (!ptr) return;

  plist* pfreed = garbage_remove(garbage,ptr);
  
  // Déclaration d'un pointeur sur fonction pour stoquer le vrai free
  void (*vraiFree) (void *);

  // Récup du vrai free dans la lib system (RTLD_NEXT vaut -1, d'ou le -1 tout à l'heure)
  
  vraiFree = (void *) dlsym(RTLD_NEXT, "free"); 
  if (vraiFree == NULL) {
    abort();
  }
  (*vraiFree) (ptr); // Appel au vrai free
  g_free(pfreed);
}

//malloc which append the pointer to the garbage collector
void *r_malloc(size_t size) {
  
  void * (*vraiMalloc) (size_t);
  vraiMalloc = dlsym(RTLD_NEXT, "malloc");

  void *res = (*vraiMalloc) (size);
  garbage_add(garbage,create_garbage(res));

  return res;
}




void g_free(void *ptr) {
  if (!ptr) return;

  void (*vraiFree) (void *);

  
  vraiFree = (void *) dlsym(RTLD_NEXT, "free"); 
  if (vraiFree == NULL) {
    abort();
  }
  (*vraiFree) (ptr);
}

//a malloc that only do what malloc do
void *g_malloc(size_t size) {

  void * (*vraiMalloc) (size_t); 
  vraiMalloc = dlsym(RTLD_NEXT, "malloc");
  void *res = (*vraiMalloc) (size);

  return res;
}






