#ifndef GARBAGE_H
#define GARBAGE_H

typedef struct plist plist;
struct plist {
  void* p;
  plist* next;
};

plist* create_garbage(void* p);

void garbage_add(plist* l, plist *elm);

plist* garbage_remove(plist* l, void* p);

void garbage_free(plist* l);

#endif
