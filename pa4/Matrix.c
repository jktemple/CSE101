//Josh Temple 
//CruzID: Jktemple 
//pa4

#include "Matrix.h"


typedef struct EntryObj {
	int column;
	double value;
} EntryObj;

typedef struct EntryObj* Entry;

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

typedef struct MatrixObj {
	int size;
	List* lists;
} MatrixObj;

Matrix newMatrix(int n){
	Matrix M = malloc(sizeof(MatrixObj));
	M->size = n;
	M->lists = (List*) calloc(n + 1, sizeof(List));
	for(int i = 1; i <= n; i++){
		M->lists[i] = newList();
	}
	return M;
}


void freeMatrix(Matrix* pM){
	if(pM != NULL && *pM != NULL){
		for(int i = 1; i <= size(*pM); i++){
			moveFront((*pM)->lists[i]);
			Entry x;
			while(index((*pM)->lists[i]) >= 0){
				x = (Entry)get((*pM)->lists[i]);
				freeEntry(&x);
				moveNext((*pM)->lists[i]);
			}
			freeList(&(*pM)->lists[i]);
		}
		free((*pM)->lists);
		free(*pM);
		*pM = NULL;
	}
}

int size(Matrix M){
	if(M == NULL){
		fprintf(stderr, "Cannot get size of Matrix because the pointer is NULL\n");
		exit(EXIT_FAILURE);
	}
	return M->size;
}	

int NNZ(Matrix M){
	if(M == NULL){
		fprintf(stderr, "Cannot get NNZ of the Matrix because the pointer is NULL\n");
		exit(EXIT_FAILURE);
	}
	int sum = 0;
	for(int i = 1; i <= size(M); i++){
		if(M->lists[i]){
			sum = sum + length(M->lists[i]);
		}
	}
	return sum;
}

int equals(Matrix A, Matrix B){
	if(size(A) != size(B)){
		return 0;
	}
	if(NNZ(A) != NNZ(B)){
		return 0;
	}
	Entry x;
	Entry y;
	for(int i = 1; i <= size(A); i++){
		moveFront(A->lists[i]);
		moveFront(B->lists[i]);
		while(index(A->lists[i]) >= 0 && index(B->lists[i]) >= 0){
			x = (Entry)get(A->lists[i]);
			y = (Entry)get(B->lists[i]);
			if(x->column != y->column || x->value != y->value){
				return 0;
			}
			moveNext(A->lists[i]);
			moveNext(B->lists[i]);
		}
	}
	return 1;
}

void makeZero(Matrix M){
	for(int i = 1; i <= size(M); i++){
		Entry x;
		moveFront(M->lists[i]);
		while(index(M->lists[i]) >= 0){
			x = (Entry)get(M->lists[i]);
			freeEntry(&x);
			moveNext(M->lists[i]);
		}
		clear(M->lists[i]);
	}
}

void changeEntry(Matrix M, int i, int j, double x){
	if( i > size(M) || j > size(M) || i < 1 || j < 1){
		fprintf(stderr, "Cannot change entry at [%d, %d] because i or j is out of bounds\n", i, j);
		exit(EXIT_FAILURE);
	}
	//printf("getting list\n");
	List L = M->lists[i];
	Entry e;
	//printf("i = %d j = %d x = %f L exists: %d\n", i, j, x, L==NULL);
	moveFront(L);
	while(index(L) >= 0){
		//printf("getting entry\n");
		e = (Entry)get(L);
		if(e->column == j){
			if(x==0)
			{
				freeEntry(&e);
				delete(L); //if there is an entry at i,j and x = 0 delete the entry there
			} 
			else {
				e->value = x; //otherwise update the value
			}
			return;
		} else if (j < e->column){
			if(x == 0){ //if the entry does not exist and x = 0, do nothing
				return;
			}
			//printf("inserting after\n");
			insertBefore(L, newEntry(j,x)); //if x != 0, the create a new entry at i, j with value x
			return;
		}
		//printf("moving prev\n");
		moveNext(L);
	}
	if(x != 0){ //if you have made it through the loop 
				//that means j is less than every entry in the list's column
				//if x != 0, then add a new entry at the beginging of the list
				//if x == 0 the function does nothing
		append(L, newEntry(j, x));
	}
}

Matrix copy(Matrix A){
	Matrix C = newMatrix(size(A));
	for(int i = 1; i <= size(A); i++){
		moveFront(A->lists[i]);
		Entry x;
		while(index(A->lists[i]) >= 0){
			x = (Entry)get(A->lists[i]);
			append(C->lists[i], newEntry(x->column, x->value));
			moveNext(A->lists[i]);
		}
	}
	return C;
}

Matrix transpose(Matrix A){
	Matrix C = newMatrix(size(A));
	for(int i = 1; i <= size(A); i++){
		moveFront(A->lists[i]);
		Entry x;
		while(index(A->lists[i]) >= 0){
			x = (Entry)get(A->lists[i]);
			changeEntry(C,x->column, i, x->value);
			moveNext(A->lists[i]);
		}
	}
	return C;
}

Matrix scalarMult(double x, Matrix A){
	Matrix C = newMatrix(size(A));
	for(int i = 1; i <= size(A); i++){
                moveFront(A->lists[i]);
                Entry y;
                while(index(A->lists[i]) >= 0){
                        y = (Entry)get(A->lists[i]);
                        append(C->lists[i], newEntry(y->column, x * y->value));
                        moveNext(A->lists[i]);
                }
        }
	return C;
}

//Adds or subtracts 2 lists making list R the result
//Assumes that R is an empty list
//if sign is > 0 the function adds the lists A + B
//ortherwise it subtracts the lits A - B
void addLists(List A, List B, List R, int sign){
	moveFront(A);
	moveFront(B);
	Entry x;
	Entry y;
	while(index(A) >= 0 && index(B) >= 0){
		x =(Entry) get(A);
		y =(Entry) get(B);
		if(x->column == y->column){ //if the entries have the same column add or subtract them
			if(sign > 0 && x->value + y->value != 0){
				append(R, newEntry(x->column, x->value + y->value));
			} else if(sign <= 0 && x->value - y->value != 0){
				append(R, newEntry(x->column, x->value - y->value));
			}
			moveNext(A);
			moveNext(B);
		} else if(x->column < y->column) {// if x has a lower column than y, add x to the list and move forward on A
			append(R, newEntry(x->column, x->value));
			moveNext(A);
		} else { //x's column is greater than y's column add y or -y to the list move forward on B
			if (sign > 0){
				append(R, newEntry(y->column, y->value));
			} else {
				append(R, newEntry(y->column, -y->value));
			}
			moveNext(B);
		}
	}
	while(index(A) >= 0){
		x = (Entry) get(A);
		append(R, newEntry(x->column, x->value));
		moveNext(A);
	}
	while(index(B) >= 0){
		y = (Entry) get(B);
		if(sign > 0){
			append(R, newEntry(y->column, y->value));
		} else {
			append(R, newEntry(y->column, -y->value));
		}
		moveNext(B);
	}	
}

Matrix sum(Matrix A, Matrix B){
	if(size(A) != size(B)){
		fprintf(stderr, "Cannot add Matrix A and B because they have different sizes\n");
		exit(EXIT_FAILURE);
	}
	Matrix C = newMatrix(size(A));
	if(A==B){
		Matrix Temp = copy(A);
		for(int i = 1; i <= size(A); i++){
                	addLists(A->lists[i], Temp->lists[i], C->lists[i], 1);
        	}
		freeMatrix(&Temp);
        	return C;
	}
	for(int i = 1; i <= size(A); i++){
		addLists(A->lists[i], B->lists[i], C->lists[i], 1);
	}
	return C;
}

Matrix diff(Matrix A, Matrix B){
	if(size(A) != size(B)){
                fprintf(stderr, "Cannot subtract Matrix A and B because they have different sizes\n");
                exit(EXIT_FAILURE);
        }
        Matrix C = newMatrix(size(A));
 	if(A==B){
                Matrix Temp = copy(A);
                for(int i = 1; i <= size(A); i++){
                        addLists(A->lists[i], Temp->lists[i], C->lists[i], 1);
                }
                freeMatrix(&Temp);
                return C;
        }
        for(int i = 1; i <= size(A); i++){
                addLists(A->lists[i], B->lists[i], C->lists[i], -1);
        }
        return C;
}

double dot(List A, List B){
	if(!A || !B){
		return 0;
	}
	double sum = 0;
	Entry x;
	Entry y;
	moveFront(A);
	moveFront(B);
	while(index(A) >= 0 && index(B) >= 0){
		x = (Entry) get(A);
		y = (Entry) get(B);
		if(x->column == y->column){
			sum += x->value * y->value;
			moveNext(A);
			moveNext(B);
		} else if(x->column < y->column){
			moveNext(A);
		} else {
			moveNext(B);
		}
	}
	return sum;
}

Matrix product(Matrix A, Matrix B){
	 if(size(A) != size(B)){
                fprintf(stderr, "Cannot multiply Matrix A and B because they have different sizes\n");
                exit(EXIT_FAILURE);
        }
	Matrix T = transpose(B);
	Matrix C = newMatrix(size(A));
	for(int i  = 1; i <= size(A); i++){
		//printf("doing row = %d\n", i);
		for(int j = 1; j<= size(T); j++){
			//printf("row of transpose: %d\n", j);
			double temp = dot(A->lists[i], T->lists[j]);
			changeEntry(C, i, j, temp);
		}
	}
	//printf("about to free matrix\n");	
	freeMatrix(&T);
	return C;
}

void printListOfEntries(FILE* out, List L){
	//printf("length of list: %d\n", length(L));
        moveFront(L);
        Entry x;
        while(index(L) >= 0){
                x = (Entry)get(L);
                fprintf(out, " (%d, %.1f)", x->column, x->value);
                moveNext(L);
        }
}

void printMatrix(FILE* out, Matrix M){
	for(int i = 1; i <= size(M); i++){
		if(length(M->lists[i]) > 0){
			fprintf(out, "%d:", i);
			printListOfEntries(out, M->lists[i]);
			fprintf(out,"\n");
		} else if(i == size(M)) {
			fprintf(out,"\n");
		}
	}	
}
