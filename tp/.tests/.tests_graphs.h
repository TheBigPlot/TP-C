#ifndef TESTS_GRAPHS_H
#define TESTS_GRAPHS_H

#include "../structs.h"

void test_init_graph(char* name, int nb_tests);
void test_add_edge(char* name, int nb_tests);
void test_add_vertice(char* name, int nb_tests);
void test_backedges_dfs(char* name, int nb_tests);
void test_components_dfs(char* name, int nb_tests);
void test_components_bfs(char* name, int nb_tests);
void test_path(char* name, int nb_tests);
void test_eccentricity(char* name, int nb_tests);
void test_center(char* name, int nb_tests);


void all_graphs_tests(int nb_tests);

#endif



