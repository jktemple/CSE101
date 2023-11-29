//Josh Temple
//CruzID: Jktemple
//pa4


#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include "Matrix.h"

int main(int argc, char* argv[]) {
	
    FILE* in, * out;
	
    // check command line for correct number of arguments
    if (argc != 3) {
        printf("Usage: %s <input file> <output file>\n", argv[0]);
        exit(1);
	}
	
    // open files for reading and writing
    //printf("%s\n", argv[1]); 
    in = fopen(argv[1], "r");
    if (in == NULL) {
        printf("Unable to open file %s for reading\n", argv[1]);
        exit(1);
	}
    //printf("%s\n", argv[2]);		
    out = fopen(argv[2], "w");
    if (out == NULL) {
        printf("Unable to open file %s for writing\n", argv[2]);
        exit(1);
    }
    int n = 0;
    int a = 0;
    int b = 0;
    fscanf(in, "%d %d %d", &n, &a, &b);
    //printf("n = %d a = %d b = %d\n", n, a, b);
    fscanf(in,"\n");
    Matrix A = newMatrix(n);
    Matrix B = newMatrix(n);
    int row = 0;
    int col = 0;
    double val = 0;
    for(int i = 0; i< a; i++){
    	fscanf(in,"%d %d %lf", &row, &col, &val);
	changeEntry(A, row, col, val);
    }
    //printMatrix(stdout,A); 
    fscanf(in, "\n");
    for(int i = 0; i < b; i++){
    	fscanf(in,"%d %d %lf", &row, &col, &val);
        changeEntry(B, row, col, val);
    }
    
    fprintf(out, "A has %d non-zero entries:\n", NNZ(A));
    printMatrix(out, A);
    fprintf(out, "B has %d non-zero entries:\n", NNZ(B));
    printMatrix(out, B);

    fprintf(out,"(1.5)*A =\n");
    Matrix sM = scalarMult(1.5, A);
    printMatrix(out, sM);
    freeMatrix(&sM);

    fprintf(out, "A+B =\n");
    Matrix APB = sum(A,B);
    printMatrix(out, APB);
    freeMatrix(&APB);

    fprintf(out,"A+A =\n");
    Matrix aCopy = copy(A);
    Matrix APA = sum(A, aCopy);
    printMatrix(out, APA);
    freeMatrix(&APA);

    fprintf(out,"B-A =\n");
    Matrix BSA = diff(B, A);
    printMatrix(out, BSA);
    freeMatrix(&BSA);

    fprintf(out,"A-A =\n");
    Matrix ASA = diff(A, aCopy);
    printMatrix(out,ASA);
    freeMatrix(&aCopy);
    freeMatrix(&ASA);

    fprintf(out,"Transpose(A) =\n");
    Matrix T = transpose(A);
    printMatrix(out, T);
    freeMatrix(&T);

    fprintf(out,"A*B =\n");
    Matrix ATB = product(A,B); 
    printMatrix(out, ATB);
    freeMatrix(&ATB);

    fprintf(out, "B*B =\n");
    Matrix BTB = product(B,B);
    printMatrix(out,BTB);
    freeMatrix(&BTB);

    freeMatrix(&A);
    freeMatrix(&B);
    fclose(out); 
    fclose(in);
    return(0);
}

