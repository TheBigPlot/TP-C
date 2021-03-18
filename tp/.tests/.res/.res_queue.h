#ifndef R_QUEUE_H
#define R_QUEUE_H

#include "../../structs.h"
#include ".res_list.h"


//create an empty queue
queue* r_init_queue();

//add elt (WARNING IT IS AN INT, add the malloc stuff) to the queue
void r_enqueue(queue* q, int elt);

//remove an element of the queue
list* r_dequeue(queue* q);


//1-> q is empty else 0
int r_isempty(queue* q);

void r_FreeQueue(queue* q);


#endif
