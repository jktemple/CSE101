//Josh Temple
//CruzID: 1797034
//pa1

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include "List.h"

#define MAX_LEN 300

int main(int argc, char* argv[]) {
	
    int line_count;
    FILE* in, * out;
    char token[MAX_LEN];
	
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
	
    line_count = 0;
    while(fgets(token, MAX_LEN, in) != NULL){
		line_count++;	    
	}
    rewind(in);
    char** array = calloc(line_count, sizeof(char*));
    for (int i = 0; i < line_count; i++) {
        array[i] = (char*)calloc(1, MAX_LEN);
	}
    int count = 0;
    while (fgets(token, MAX_LEN, in) != NULL) {
		strcpy(array[count],token);
        count++;
	}
	
    List sortedList = newList();
    append(sortedList, 0);
    moveFront(sortedList);
	for(int i = 1; i < line_count; i++){
		while(index(sortedList) >=0){ //go through list, if the word at array[i] is
			//smaller than the word at array[the current index in the list]
			//add i to the list in front of the current index
			int currentIndex = get(sortedList);
			if(strcmp(array[i],array[currentIndex]) < 0){
				insertBefore(sortedList, i);
				break;	
			}
			moveNext(sortedList); //if the loops makes it to the end of the list without
			//inserting i into the list, add i to the end
			if(index(sortedList)<0){
				append(sortedList, i);
			}
		}
		moveFront(sortedList);
	}
	
	moveFront(sortedList);
	while(index(sortedList) >= 0){
		fprintf(out,"%s", array[get(sortedList)]);
		moveNext(sortedList);
	}
	freeList(&sortedList);
	for (int i = 0; i < line_count; i++) {
		free(array[i]);
	}
	free(array);
    fclose(in);
    fclose(out);
    return(0);
}
