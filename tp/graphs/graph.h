#ifndef GRAPH_H
#define GRAPH_H

#include "../lists/list.h"

#include "../structs.h"

//generate an empty graph
graph* init_graph(int order, int is_directed);


//add an edge between src and dst
//if directed only add the link to src
//cannot have duplicatins in a adjlist
void add_edge(graph* G, int src, int dst);

//add a vertice to the graph
//it has to re alloc the adjlist
//it has to change the graph order
void add_vertice(graph* G);

//it print the back edges of a graph G
//one function by version
void backedges_dfs(graph* G);

//return the number of connected components of a graph G
//one function by version
int components_dfs(graph* G);
int components_bfs(graph* G);

//return the shortest path between vertice a and vertice b
list* path(graph* G, int src, int dst);

//return the eccentricity of the vertice src in the graph G
int eccentricity(graph* G, int src);

//return the list of vertice which compose the center
list* center(graph* G);

//free the graph g
void FreeGraph(graph* g);


#endif
