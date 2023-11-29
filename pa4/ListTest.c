//Josh Temple 
//CruzID Jktemple 
//pa4

#include "List.h"

typedef struct EntryObj* Entry;

typedef struct EntryObj {
	int column;
	double value;
} EntryObj;

Entry newEntry(int c, double v){
	Entry E = malloc(sizeof(EntryObj));
	E->column = c;
	E->value = v;
	return E;
}

void freeEntry(Entry* eN) {
	if (eN != NULL && *eN != NULL) {
		free(*eN);
		*eN = NULL;
	}
}

void printListOfEntries(List L){
	moveFront(L);
	Entry x = NULL;
	while(index(L) >= 0){
		x = (Entry)get(L);
		printf("(%d, %f) ", x->column, x->value); 
		moveNext(L);
	}
	printf("\n");
}

int main(void){
	List L = newList();
	printf("new list made\n");
	Entry e1 = newEntry(1, 1.1);
	Entry e2 = newEntry(2, 2.2);
	Entry e3 = newEntry(3, 3.3);
	Entry e4 = newEntry(4, 4.4);
	Entry e5 = newEntry(5, 5.5);
	printf("e1 = (%d, %f)\n", e1->column, e1->value);
	printf("new Entries mande\n");
	prepend(L, e1);
	printf("prepend\n");
	append(L, e2);
	printf("append\n");
	moveFront(L);
	printf("move front\n");
	insertAfter(L, e3);
	printf("insert after\n"); 
	insertBefore(L, e4);
	printf("insertBefore\n");
	moveBack(L);
	printf("move back\n");
	insertBefore(L, e5);
	printf("insert Before\n");
	printListOfEntries(L); 
	printf("should be e4 e1 e3 e5 e2\n");
	moveFront(L);
	Entry x;
	moveFront(L);
	moveNext(L);
	delete(L);
	printListOfEntries(L);
	deleteFront(L);
	printListOfEntries(L);
	deleteBack(L);
	printListOfEntries(L);
	while(index(L) >= 0){
                x = (Entry)get(L);
                freeEntry(&x);
                moveNext(L);
        }

	freeList(&L);
}
