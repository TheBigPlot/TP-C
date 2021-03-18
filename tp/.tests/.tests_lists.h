#ifndef TEST_LIST_H

#define TEST_LIST_H



void test_list_init(char* name, int nb_tests);
void test_create_list(char* name, int nb_tests);
void test_list_is_empty(char* name, int nb_tests);
void test_list_len(char* name, int nb_tests);
void test_list_get(char* name, int nb_tests);
void test_list_push_front(char* name, int nb_test);
void test_list_insert(char* name, int nb_tests);
void test_list_pop_front(char* name, int nb_tests);
void test_list_remove(char* name, int nb_tests);
void test_list_search(char* name, int nb_tests);
void test_list_binary_search(char* name, int nb_tests);
void test_list_insert_sort(char* name, int nb_tests);
void test_list_reverse(char* name, int nb_tests);

void test_FreeList(char* name, int nb_tests);


void all_lists_tests (int nb_tests);


#endif
