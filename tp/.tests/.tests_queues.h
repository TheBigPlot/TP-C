#ifndef TEST_QUEUES_H
#define TEST_QUEUES_H

#include "../structs.h"


void test_init_queue(char* name, int nb_tests);
void test_enqueue(char* name, int nb_tests);
void test_dequeue(char* name, int nb_tests);
void test_isempty(char* name, int nb_tests);
void test_FreeQueue(char* name, int nb_tests);

void all_queues_tests(int nb_tests);

#endif
