//Josh Temple 
//CruzID: Jktemple 
//pa4


#include "Matrix.h"

int main(void){
	Matrix M = newMatrix(5);
	printf("Matrix made\n");
	printMatrix(stdout, M);
	printf("printed empty matrix\n");
	changeEntry(M,1,1,1.1);
	changeEntry(M,2,2,2.2);
	changeEntry(M,3,3,3.3);
	changeEntry(M,4,4,4.4);
	changeEntry(M,5,5,5.5);
	printMatrix(stdout, M);
	printf("added 1,2\n");
	changeEntry(M,1,2,1.2);
	printMatrix(stdout, M);
	printf("updated 1,1\n");
	changeEntry(M,1,1, 10.1);
	printf("making 5,5 0\n");
	changeEntry(M,5,5,0);
	printf("added 1,3\n");
	changeEntry(M,1,3, 1.3);
	printf("adding 0 at 4,3\n");
	changeEntry(M,4,3, 0);
	printf("printing updated matrix\n");
	printMatrix(stdout, M);
	printf("Copying List\n");
	Matrix C = copy(M);
	printMatrix(stdout, C);
	printf("getting transpose\n");
	Matrix T = transpose(C);
	printMatrix(stdout, T);
	printf("scalar mult\n");
	Matrix sM = scalarMult(3, C);
	printMatrix(stdout, sM);
	printf("adding matrixes\n");
	Matrix A = sum(M,C);
	printMatrix(stdout, A);
	printf("subracting Matrixes\n");
	Matrix S = diff(M,C);
	printMatrix(stdout, S);
	printf("multiplying Matrixes\n");
	Matrix G = product(M,C);
	printf("done mult\n");
	printMatrix(stdout, G);
	printf("NNZ of G = %d\n", NNZ(G));
	freeMatrix(&M);
	freeMatrix(&C);
	freeMatrix(&T);
	freeMatrix(&sM);
	freeMatrix(&A);
	freeMatrix(&S);
	freeMatrix(&G); 
}
