//Josh Temple
//CruzID: Jktemple
//pa3


#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include "List.h"

typedef struct NodeObj* Node;

typedef struct NodeObj {
	int data;
	Node next;
	Node prev;
} NodeObj;

typedef struct ListObj {
	Node front;
	Node back;
	int length;
	int index;
	Node cursor;
} ListObj;

//newNode()
//creates a new node object
Node newNode(int data) {
	Node N = malloc(sizeof(NodeObj));
	N->data = data;
	N->next = NULL;
	N->prev = NULL;
	return(N);
}

// freeNode()
// Frees heap memory pointed to by *pN, sets *pN to NULL.
void freeNode(Node* pN) {
	if (pN != NULL && *pN != NULL) {
		free(*pN);
		*pN = NULL;
	}
}

// newQueue()

// Creates and returns a new empty List.
List newList(void) {
	List L;
	L = malloc(sizeof(ListObj));
	L->front = L->back = L->cursor = NULL;
	L->length = 0;
	L->index = -1;
	return L;
}
// Frees all heap memory associated with *pL, and sets
void freeList(List* pL) { 
	if (pL != NULL && *pL != NULL) {
		moveFront(*pL);
		while (index(*pL) >= 0) {
			Node temp = (*pL)->cursor; 
			moveNext(*pL);
			freeNode(&temp);
		}
		free(*pL);
		*pL = NULL;
	}
}

int length(List L) {
	if (L==NULL) {
		fprintf(stderr, "Length(L) failed because the list does not exist\n");
		exit(EXIT_FAILURE);
	}
	return L->length;
}

int index(List L) {
	if (L==NULL) {
		fprintf(stderr, "Index(L) failed because the list does not exist\n");
		exit(EXIT_FAILURE);
	}
	if (index < 0) {
		return -1;
	}
	return L->index;
}

int front(List L) {
	if (L == NULL) {
		fprintf(stderr, "Front(L) failed because the list does not exist\n");
		exit(EXIT_FAILURE);
	}
	if (length(L) <= 0) {
		fprintf(stderr, "Front(L) failed because the list is empty\n");
		exit(EXIT_FAILURE);
	}
	return(L->front->data);
}

int back(List L) {
	if (L == NULL) {
		fprintf(stderr, "Back(L) failed because the list does not exist\n");
		exit(EXIT_FAILURE);
	}
	if (length(L) <= 0) {
		fprintf(stderr, "Back(L) failed because the list is empty\n");
		exit(EXIT_FAILURE);
	}
	return(L->back->data);
}

int get(List L) {
	if (L == NULL) {
		fprintf(stderr, "Get(L) failed because the list does not exist\n");
		exit(EXIT_FAILURE);
	}
	if (length(L) <= 0) {
		fprintf(stderr, "Get(L) failed because the list is empty\n");
		exit(EXIT_FAILURE);
	}
	return(L->cursor->data);
}

bool equals(List A, List B) {
	if (A == NULL) {
		fprintf(stderr, "Equals(A,B) failed because the A is NULL\n");
		exit(EXIT_FAILURE);
	}
	if (B == NULL) {
		fprintf(stderr, "Equals(A,B) failed because the B is NULL\n");
		exit(EXIT_FAILURE);
	}
	if (length(A) != length(B)) {
		return false;
	}
	moveFront(A);
	moveFront(B);
	while (index(A) >= 0) {
		if (get(A) != get(B)) {
			return false;
		}
		moveNext(A);
		moveNext(B);
	}
	return true;
}

void clear(List L) {
	moveFront(L);
	while (index(L) >= 0) {
		Node temp = L->cursor;
		moveNext(L);
		freeNode(&temp);
	}
	L->front = L->back = L->cursor = NULL;
	L->length = 0;
	L->index = -1;
}

void set(List L, int x) {
	if (length(L) <= 0) {
		fprintf(stderr, "set(L, x) failled because L is empty");
		exit(EXIT_FAILURE);
	}
	if (index(L) < 0) {
		fprintf(stderr, "set(L,x) failed because L's index is undefined");
		exit(EXIT_FAILURE);
	}
	L->cursor->data = x;
}
void moveFront(List L) {
	if (length(L) > 0) {
		L->cursor = L->front;
		L->index = 0;
	}
}
void moveBack(List L) {
	if (length(L) > 0) {
		L->cursor = L->back;
		L->index = length(L) - 1;
	}
}
void movePrev(List L) {
	if (index(L) > 0) {
		L->cursor = L->cursor->prev;
		L->index = L->index - 1; 
	}
	else if (index(L) == 0) {
		L->cursor = NULL;
		L->index = -1;
	}
}
void moveNext(List L) {
	if (index(L) < length(L) - 1) {
		L->cursor = L->cursor->next;
		L->index = L->index + 1;
	}
	else if (index(L) == length(L) - 1) {
		L->cursor = NULL;
		L->index = -1;
	}
}

void prepend(List L, int x) {
	if (length(L) == 0) {
		L->back = L->front = newNode(x);
		L->length = L->length + 1;
	}
	else{
		Node newN = newNode(x);
		newN->next = L->front;
		L->front->prev = newN;
		L->front = newN;
		L->length = L->length + 1;
		if (index(L) >= 0) {
			L->index = L->index + 1;
		}
	}
}
void append(List L, int x) {
	if (length(L) == 0) {
		L->back = L->front = newNode(x);
		L->length = L->length + 1;
	}
	else{
		Node newN = newNode(x);
		newN->prev = L->back;
		L->back->next = newN;
		L->back = newN;
		L->length = L->length + 1;
	}
}

void insertBefore(List L, int x) {
	if(index(L)==0 && length(L) >0){
		prepend(L,x); 
	} 
	else if (length(L) > 0 && index(L) >= 0) {
		Node newN = newNode(x);
		newN->prev = L->cursor->prev;
		newN->next = L->cursor;
		L->cursor->prev->next = newN;
		L->cursor->prev = newN;
		L->length = L->length + 1;
		L->index = L->index + 1;
	}
	else if (length(L) <= 0) {
		fprintf(stderr, "InsertBefore(L) failed because L is empty\n");
		exit(EXIT_FAILURE);
	}
	else if (index(L) < 0) {
		fprintf(stderr, "InsertBefore(L) failed because the Cursor is undefined\n");
		exit(EXIT_FAILURE);
	}
}

void insertAfter(List L, int x) {
	if (length(L) > 0 && index(L) >= 0) {
		Node newN = newNode(x);
		newN->prev = L->cursor;
		newN->next = L->cursor->next;
		if(L->cursor->next){
			L->cursor->next->prev = newN;
		}
		L->cursor->next = newN;
		L->length = L->length + 1;
	}
	else if (length(L) <= 0) {
		fprintf(stderr, "InsertAfter(L) failed because L is empty\n");
		exit(EXIT_FAILURE);
	}
	else if (index(L) < 0) {
		fprintf(stderr, "InsertAfter(L) failed because the Cursor is undefined\n");
		exit(EXIT_FAILURE);
	}
}

void deleteFront(List L) {
	if(length(L) == 1){
                Node temp = L->back;
                L->front = NULL;
                L->back = NULL;
                L->length -= 1;
                freeNode(&temp);
        }
        else if (length(L) > 0) {
		Node temp = L->front;
		L->front = L->front->next;
		L->front->prev = NULL;
		if (index(L) == 0) {
			L->index = -1;
			L->cursor = NULL;
		}
		else if (index > 0) {
			L->index = L->index - 1; 
		}
		L->length = L->length - 1;
		freeNode(&temp);
	}
	else if (length(L) <= 0) {
		fprintf(stderr, "DeleteFront(L) failed because L is empty\n");
		exit(EXIT_FAILURE);
	}
}

void deleteBack(List L) {
	if(length(L) == 1){
		Node temp = L->back;
		L->front = NULL;
		L->back = NULL;
		L->length -= 1;
		freeNode(&temp);
	}
	else if (length(L) > 0) {
		Node temp = L->back;
		L->back = L->back->prev;
		L->back->next = NULL;
		if (index(L) == length(L) -1 ){
			L->index = -1;
			L->cursor = NULL;
		}
		L->length = L->length - 1;
		freeNode(&temp);
	}
	else if (length(L) <= 0) {
		fprintf(stderr, "DeleteBack(L) failed because L is empty\n");
		exit(EXIT_FAILURE);
	}
}

void delete(List L) {
	if(index(L) == 0 && length(L) == 1){
                Node temp = L->cursor;
                L->front = NULL;
                L->back = NULL;
                L->length -= 1;
                freeNode(&temp);
		L->cursor = NULL;
        } else if(index(L) == 0 && length(L) > 0){
		deleteFront(L); 
		L->cursor = NULL;
		L->index = -1;
	} else if(index(L) == length(L)- 1){
		deleteBack(L);
		L->index = -1;
		L->cursor = NULL;
	}
	else if (length(L) > 0 && index(L) >= 0) {
		Node temp = L->cursor;
		L->cursor->prev->next = L->cursor->next;
		L->cursor->next->prev = L->cursor->prev;
		L->cursor = NULL;
		L->index = -1;
		L->length = L->length - 1;
		freeNode(&temp);
	}
	else if (length(L) <= 0) {
		fprintf(stderr, "delete(L) failed because L is empty\n");
		exit(EXIT_FAILURE);
	}
	else if (index(L) < 0) {
		fprintf(stderr, "delete(L) failed because L's cursor is undefined\n");
		exit(EXIT_FAILURE);
	}
}

void printList(FILE* out, List L) {
	moveFront(L);
	while (index(L) >= 0) {
		fprintf(out, "%d ", get(L));
		moveNext(L);
	}
}

List copyList(List L) {
	List listN = newList();
	moveFront(L);
	while (index(L)>=0) {
		append(listN, get(L));
		moveNext(L);
	}
	return listN;
}
