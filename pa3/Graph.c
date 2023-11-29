//Josh Temple
//CruzID: jktemple
//pa3

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include "Graph.h"

typedef struct GraphObj {
	int order;
	int size;
	int source;
	int* colors;
	int* parents;
	int* dist;
	int* finish;
	int* discover;
	List* lists; 
} GraphObj;

Graph newGraph(int n){
	Graph g;
	g = (Graph) malloc(sizeof(GraphObj));
	g->order = n;
	g->lists = (List*) calloc(n+1, sizeof(List));
	g->colors = (int*) calloc(n+1,sizeof(int));
	g->parents = (int *) calloc(n+1, sizeof(int));
	g->dist = (int*) calloc(n+1, sizeof(int));
	g->finish = (int*) calloc(n+1, sizeof(int));
	g->discover = (int*) calloc(n+1, sizeof(int));
	for(int i = 0; i < n+1; i++){
		g->lists[i] = newList();
		g->parents[i] = NIL;
		g->dist[i] = INF;
		g->finish[i] = UNDEF;
		g->discover[i] = UNDEF;
	}
	g->source = NIL;
	return g;
}

void freeGraph(Graph* pG){
	if (pG != NULL && *pG != NULL) {
		for(int i = 0; i < getOrder(*pG) + 1; i++){
			freeList(&(*pG)->lists[i]);
		}
		free((*pG)->lists);
		free((*pG)->colors);
		free((*pG)->parents);
		free((*pG)->dist);
		free((*pG)->finish);
		free((*pG)->discover);
		free(*pG);
		*pG = NULL;
	}
}

int getOrder(Graph G){
	if(G==NULL){
		fprintf(stderr, "Cannot get the order of the graph because the graph does not exist\n");
		exit(EXIT_FAILURE);
	}
	return G->order;
}

int getSize(Graph G){
	if(G==NULL){
		fprintf(stderr, "Cannot get the size of the graph because the graph does not exist\n");
		exit(EXIT_FAILURE);
	}
	return G->size;
}

int getSource(Graph G){
	if(getOrder(G) == 0){
		fprintf(stderr, "Cannot get the source of the graph because the graph has order = 0\n");
		exit(EXIT_FAILURE);
	}
	return G->source;
}

int getParent(Graph G, int u){
	int o = getOrder(G);
	if(o == 0){
		fprintf(stderr, "Cannot get the parent of u because the graph has order = 0\n");
		exit(EXIT_FAILURE);
	} else if( u > (o+1) || u < 1){
		fprintf(stderr, "Cannot get the parent of u because u is outside the range of the graph\n");
		exit(EXIT_FAILURE);
	}
	return G->parents[u];
}

int getDist(Graph G, int u){
	int o = getOrder(G);
	if(o == 0){
		fprintf(stderr, "Cannot get the dist to u because the graph has order = 0\n");
		exit(EXIT_FAILURE);
	} else if( u > (o+1) || u < 1){
		fprintf(stderr, "Cannot get the dist to u because u is outside the range of the graph\n");
		exit(EXIT_FAILURE);
	}
	return G->dist[u];
}

int getFinish(Graph G, int u){
	int o = getOrder(G);
	if(o == 0){
		fprintf(stderr, "Cannot get the finish of u because the graph has order = 0\n");
		exit(EXIT_FAILURE);
	} else if( u > (o+1) || u < 1){
		fprintf(stderr, "Cannot get the finish of u because u is outside the range of the graph\n");
		exit(EXIT_FAILURE);
	}
	return G->finish[u];
}

int getDiscover(Graph G, int u){
	int o = getOrder(G);
	if(o == 0){
		fprintf(stderr, "Cannot get the Discover of u because the graph has order = 0\n");
		exit(EXIT_FAILURE);
	} else if( u > (o+1) || u < 1){
		fprintf(stderr, "Cannot get the Discover of u because u is outside the range of the graph\n");
		exit(EXIT_FAILURE);
	}
	return G->discover[u];
}

void getPath(List L, Graph G, int u){
	if(getSource(G) == NIL){
		fprintf(stderr, "cannot get the path since BFS has not yet been called\n");
		exit(EXIT_FAILURE);
	} else if( u > (getOrder(G)+1) || u < 1){
		fprintf(stderr, "Cannot get the path to u because u is outside the range of the graph\n");
		exit(EXIT_FAILURE);
	}
	List temp = newList();
	append(temp, u);
	int p = getParent(G, u);
	if(p == NIL){
		append(L,NIL);
		return;
	}
	while(p != NIL){
		if(p == getSource(G)){
			append(temp, p);
			break;
		}
		else if (p == NIL) {
			append(L,NIL);
			return;
		} 
		else{
			append(temp, p); 
			p = getParent(G, p);
		}
	}
	moveBack(temp);
	while(index(temp) >= 0){
		
		append(L, get(temp));
		movePrev(temp);
	}
	freeList(&temp);
}

void makeNull(Graph G){
	if(G==NULL){
		fprintf(stderr, "Cannot make G null because G is NULL\n");
		exit(EXIT_FAILURE);
	}
	for(int i = 0; i < getOrder(G)+1; i++){
		clear(G->lists[i]);
		G->parents[i] = NIL;
		G->dist[i] = INF;
		G->finish[i] = INF;
		G->discover[i] = INF;
	}
	G->source = NIL;
	G->size = 0; 
} 

void addEdge(Graph G, int u, int v){
	int order = getOrder(G);
	if( u < 1 || u > order + 1){
		fprintf(stderr, "cannot add edge because u is out of the graph's range\n");
		exit(EXIT_FAILURE);
	} else if( v < 1 || v > order + 1){
		fprintf(stderr, "cannot add edge because v is out of the graph's range\n");
		exit(EXIT_FAILURE);
	}
	G->size += 1;
	List temp = G->lists[u];
	moveFront(temp);
	while(index(temp) >=0){
		if(v < get(temp)){
			insertBefore(temp, v);
			break;
		}
		moveNext(temp);
	}
	if(index(temp)<0){
		append(temp, v);
	}
	temp = G->lists[v];
	moveFront(temp);
	while(index(temp) >=0){
		if( u < get(temp)){
			insertBefore(temp, u);
			break;
		}
		moveNext(temp);
	}
	if(index(temp)<0){
		append(temp, u);
	}
}
void addArc(Graph G, int u, int v){
	int order = getOrder(G);
	if( u < 1 || u > order + 1){
		fprintf(stderr, "cannot add arc because u is out of the graph's range\n");
		exit(EXIT_FAILURE);
	} else if( v < 1 || v > order + 1){
		fprintf(stderr, "cannot add arc because v is out of the graph's range\n");
		exit(EXIT_FAILURE);
	}
	G->size += 1;
	List temp = G->lists[u];
	moveFront(temp);
	while(index(temp) >=0){
		if(v < get(temp)){
			insertBefore(temp, v);
			break;
		}
		moveNext(temp);
	}
	if(index(temp)<0){
		append(temp, v);
	}
}

void BFS(Graph G, int s){
	int order = getOrder(G);
	if( s < 1 || s > order + 1){
		fprintf(stderr, "cannot perform BFS on graph because s is out of the graph's range\n");
		exit(EXIT_FAILURE);
	}
	for(int i = 0; i < order + 1; i++){
		G->colors[i] = WHITE;
		G->dist[i] = INF;
		G->parents[i] = NIL;
	}
	G->colors[s] = GRAY;
	G->parents[s] = NIL;
	G->dist[s] = 0;
	List queue = newList();
	prepend(queue, s);
	while(length(queue) > 0){
		int x = back(queue);
		deleteBack(queue);
		List temp = G->lists[x];
		moveFront(temp);
		while(index(temp)>= 0){
			int current = get(temp);
			if(G->colors[current] == WHITE){
				G->colors[current] = GRAY;
				G->dist[current] = G->dist[x] + 1;
				G->parents[current] = x;
				prepend(queue, current);
			}
			moveNext(temp);
		}
		G->colors[x] = BLACK;
	}
	G->source = s;
	freeList(&queue);
}


int Visit(Graph G, int time, int v, List L){
        G->discover[v] = (++time);
        G->colors[v] = GRAY;
        moveFront(G->lists[v]);
        while(index(G->lists[v])>=0){
                if(G->colors[get(G->lists[v])] == WHITE){
                        G->parents[get(G->lists[v])] = v;
                        time = Visit(G, time, get(G->lists[v]), L);
                }
                        moveNext(G->lists[v]);
        }
        G->colors[v] = BLACK;
        G->finish[v] = (++time);
	prepend(L, v);
        return time;
}



void DFS(Graph G, List L){
	if(length(L) != getOrder(G)){
		fprintf(stderr, "Cannot perform DFS because the List does not have length = to the order of the graph\n");
		exit(EXIT_FAILURE);
	}
	for(int i = 1; i <= getOrder(G); i++){
		G->parents[i] = NIL;
		G->colors[i] = WHITE;
	}
	int time = 0;
	List vOrder = copyList(L);
	clear(L);
	moveFront(vOrder); 
	while(index(vOrder)>=0){
		if(G->colors[get(vOrder)] == WHITE){
			time = Visit(G, time, get(vOrder), L);
		}
		moveNext(vOrder);
	}
	freeList(&vOrder);
}


void printGraph(FILE* out, Graph G){
	int order = getOrder(G);
	for(int i = 1; i < order + 1; i++){
		fprintf(out, "%d: ", i);
		printList(out, G->lists[i]);
		fprintf(out, "\n");
	}
}

Graph copyGraph(Graph G){
	int n = getOrder(G);
	Graph g;
	g = (Graph) malloc(sizeof(GraphObj));
	g->order = n;
	g->lists = (List*) calloc(n+1, sizeof(List));
	g->colors = (int*) calloc(n+1,sizeof(int));
	g->parents = (int *) calloc(n+1, sizeof(int));
	g->dist = (int*) calloc(n+1, sizeof(int));
	g->finish = (int*) calloc(n+1, sizeof(int));
	g->discover = (int*) calloc(n+1, sizeof(int));
	for(int i = 0; i < n+1; i++){
		g->lists[i] = copyList(G->lists[i]);
		g->parents[i] = G->parents[i];
		g->dist[i] = G->dist[i];
		g->finish[i] = G->finish[i];
		g->discover[i] = G->discover[i];
	}
	g->source = G->source;
	return g;
}

Graph transpose(Graph G){
	int order = getOrder(G);
	Graph newG = newGraph(order);
	for(int i = 1; i <= order; i++){
		moveFront(G->lists[i]);
		while(index(G->lists[i]) >= 0){
			addArc(newG, get(G->lists[i]), i);
			moveNext(G->lists[i]);
		}
	}
	return newG;
}
