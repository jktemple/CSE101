//Josh Temple
//CruzID: jktemple
//pa3

#include "Graph.h"
#include <stdio.h>

int main(void){

	Graph g = newGraph(5);
	printf("G's order = %d\n", getOrder(g));
	addEdge(g,1,2);
	addEdge(g,2,3);
	addEdge(g,1,3);
	addArc(g,4,1);
	addArc(g,4,5);
	printGraph(stdout, g);
	printf("G's size: %d\n", getSize(g));
	BFS(g, 1);
	printf("G's source: %d\n", getSource(g));
	makeNull(g);
 	addEdge(g,1,2);
        addEdge(g,2,3);
        addEdge(g,1,3);
        addArc(g,4,1);
        addArc(g,4,5);
	List L = newList();
	for(int i = 1; i<=getOrder(g); i++){
		append(L, i);
	}
	DFS(g, L);
	for(int i = 1; i <= getOrder(g); i++){
		printf("getDiscover(g, %d) = %d getFinish(g, %d) = %d\n", i, getDiscover(g,i), i, getFinish(g, i));
	}
	freeList(&L);
	freeGraph(&g);

}
