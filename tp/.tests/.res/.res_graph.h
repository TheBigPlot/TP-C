#ifndef R_GRAPH_H
#define R_GRAPH_H

#include "../../structs.h"
#include ".res_list.h"



//generate an empty graph
graph* r_init_graph(int order, int is_directed);


//add an edge between src and dst
//if directed only add the link to src
//cannot have duplicatins in a adjlist
void r_add_edge(graph* G, int src, int dst);

//add a vertice to the graph
//it has to re alloc the adjlist
//it has to change the graph order
void r_add_vertice(graph* G);

//it print the back edges of a graph G
//one function by version
void r_backedges_dfs(graph* G);

//return the number of connected components of a graph G
//one function by version
int r_components_dfs(graph* G);
int r_components_bfs(graph* G);

//return the shortest path between vertice a and vertice b
list* r_path(graph* G, int src, int dst);

//return the eccentricity of the vertice src in the graph G
int r_eccentricity(graph* G, int src);

//return the list of vertice which compose the center
list* r_center(graph* G);

void r_FreeGraph(graph* g);


#endif
