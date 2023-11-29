//Josh Temple
//CruzID: Jktemple
//pa3


#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include "Graph.h"

void printTrees(FILE* out, Graph G, List L){
	int count = 0;
	for(int i = 1; i <= getOrder(G); i++){
		if(getParent(G, i) == NIL){
			count++;
		}
	}
	fprintf(out, "\nG contains %d strongly connected components:\n", count);
	if(count == 0){
		return;
	}
	List P = newList();
	int comp = 1;
	moveBack(L);
	prepend(P, get(L));
	movePrev(L);
	while(index(L) >= 0){
		prepend(P, get(L));
		if(getParent(G,get(L)) == NIL){
			fprintf(out, "Component %d: ", comp);
			printList(out, P);
			fprintf(out,"\n");
			clear(P);
			comp++;
		}
		movePrev(L);
	}	
	freeList(&P);
}

int main(int argc, char* argv[]) {
	
    FILE* in, * out;
	
    // check command line for correct number of arguments
    if (argc != 3) {
        printf("Usage: %s <input file> <output file>\n", argv[0]);
        exit(1);
	}
	
    // open files for reading and writing 
    in = fopen(argv[1], "r");
    if (in == NULL) {
        printf("Unable to open file %s for reading\n", argv[1]);
        exit(1);
	}
	
    out = fopen(argv[2], "w");
    if (out == NULL) {
        printf("Unable to open file %s for writing\n", argv[2]);
        exit(1);
	}
	int order = 0;
	fscanf(in, "%d", &order);
	Graph G = newGraph(order);
	int x = 0;
	int y = 0;
	fscanf(in,"%d %d\n", &x, &y);
	while(x != 0 && y != 0){
		addArc(G, x, y);
		fscanf(in,"%d %d\n", &x, &y);
	}
	fprintf(out, "Adjacency list representation of G:\n");
	printGraph(out, G);
    Graph T = transpose(G);
    List L = newList();
    for(int i = 1; i <= getOrder(G); i++){
        append(L,i);
    }
    DFS(G,L);
    DFS(T,L);
    printTrees(out, T, L);
    freeList(&L);
    freeGraph(&G); 	
    fclose(in);
    fclose(out);
    return(0);
}
