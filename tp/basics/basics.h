#ifndef BASIC_H
#define BASIC_H

//return 2^n (it has to be as fast as possible)
unsigned long power_of_two(int n);

//bin is a binary number represented by an int
//return the convert number
unsigned long binary_to_int(int bin);


//display the decomposition in prime numbers of n
void decompose(int n, int* tab);

//reverse the element in the arr
void reverse_arr(int* arr,size_t length);

//shift all elements in the array arr by n
//n could be negative
void n_shift_arr(int* arr,size_t length, int n);


//replace as much as you can the char of s1 by the char of s2
//s1 and s2 could be empty
void replace(char* s1, char* s2);


//implement the cesar cypher
void cesar(char* s, int dec);

//return the result of operations without priorities
//ex: 2+2*2 = 8
//ex: 2*2+2 = 6
//ex: 3-1*2 = 4
unsigned long basic_calculator(char* s);


#endif
