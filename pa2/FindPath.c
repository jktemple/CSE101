//Josh Temple
//CruzID: 1797034
//pa2


#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include "Graph.h"

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
		addEdge(G, x, y);
		fscanf(in,"%d %d\n", &x, &y);
	}
	printGraph(out, G);
	fprintf(out, "\n");
	int source = 1;
	int dest = 1;
	fscanf(in,"%d %d\n", &source, &dest);
	while(source != 0 && dest != 0){
		BFS(G,source);
		int dist = getDist(G, dest);
		if(dist == INF){
			fprintf(out, "The distance from %d to %d is infinity\n", source, dest);
			fprintf(out, "No %d-%d path exists\n\n", source, dest);
		} else {
			fprintf(out, "The distance from %d to %d is %d\n", source, dest, dist);
			fprintf(out, "A shortest %d-%d path is: ", source, dest);
			List temp = newList();
			getPath(temp, G, dest);
			printList(out, temp);
			fprintf(out, "\n\n");
			freeList(&temp);
		}
		fscanf(in,"%d %d\n", &source, &dest);
	}
    freeGraph(&G); 	
    fclose(in);
    fclose(out);
    return(0);
}
