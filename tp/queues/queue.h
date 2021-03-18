#ifndef QUEUE_H
#define QUEUE_H

#include "../lists/list.h"


#include "../structs.h"


//create an empty queue
//and initialise it !
queue* init_queue();

//add elt (WARNING IT IS AN INT, add the malloc stuff) to the queue
void enqueue(queue* q, int elt);

//remove an element of the queue
list* dequeue(queue* q);


//1-> q is empty else 0
int isempty(queue* q);

//Free the queue q
void FreeQueue(queue* q);


#endif
