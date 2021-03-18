#ifndef UNIT_TEST_H
#define UNIT_TEST_H

#include <stdlib.h>
#include "../../structs.h"

void red ();
void green();
void blue();
void reset ();
void trans(void);
void BigTrans(void);

void CallFile(char* name,Func funcs[],char* names[],int len, int nb_tests);
void callFunction(Func f,char* name, int nb_tests);
void call_all_functions(Func funcs[], char* names[],int len, int nb_tests);


void comp_bool(char* testname,int expected, int got,char* data);
void comp_size_t(char* testname, size_t expected, size_t got,char* data);
void comp_int(char* testname, int expected, int got, char* data);
void comp_array(char* testname, int* expected, int len, int* got, char* data);
void comp_string(char* testname, char* expected, char* got, char* data);
void comp_list(char* testname, list* expected, list* got, char* data);
void comp_full_list(char* testname, list* expected, list* got, char* data);

void check_allocs();


#endif
