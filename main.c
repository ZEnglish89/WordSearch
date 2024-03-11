#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

// Declarations of the two functions you will implement
// Feel free to declare any helper functions or global variables
void printPuzzle(char** arr);
void searchPuzzle(char** arr, char* word);
int bSize;

// Main function, DO NOT MODIFY 	
int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <puzzle file name>\n", argv[0]);
        return 2;
    }
    int i, j;
    FILE *fptr;

    // Open file for reading puzzle
    fptr = fopen(argv[1], "r");
    if (fptr == NULL) {
        printf("Cannot Open Puzzle File!\n");
        return 0;
    }

    // Read the size of the puzzle block
    fscanf(fptr, "%d\n", &bSize);
    
    // Allocate space for the puzzle block and the word to be searched
    char **block = (char**)malloc(bSize * sizeof(char*));
    char *word = (char*)malloc(20 * sizeof(char));

    // Read puzzle block into 2D arrays
    for(i = 0; i < bSize; i++) {
        *(block + i) = (char*)malloc(bSize * sizeof(char));
        for (j = 0; j < bSize - 1; ++j) {
            fscanf(fptr, "%c ", *(block + i) + j);            
        }
        fscanf(fptr, "%c \n", *(block + i) + j);
    }
    fclose(fptr);

    printf("Enter the word to search: ");
    scanf("%s", word);
    
    // Print out original puzzle grid
    printf("\nPrinting puzzle before search:\n");
    printPuzzle(block);
    
    // Call searchPuzzle to the word in the puzzle
    searchPuzzle(block, word);
    
    return 0;
}

void printPuzzle(char** arr) {
	for(int i=0;i<bSize;i++){
		for(int j=0;j<bSize;j++){
			printf("%c",*(*(arr+i)+j));
			if(j!=bSize-1){
				printf(" ");
			}
		}
		printf("\n");
	}

}

void searchPuzzle(char** arr, char* word) {
    // This function checks if arr contains the search word. If the 
    // word appears in arr, it will print out a message and the path 
    // as shown in the sample runs. If not found, it will print a 
    // different message as shown in the sample runs.
    // Your implementation here...

    //find the first letter.

    int length = strlen(word);
    int row = 0; //first letter row
    int column = 0; //first letter column
    word++;//remove the first letter of the word.
    length--;//length of the word without the letter we removed.
    searchHelper(arr, word, row, column, length);

    //if the solution array contains the length of the word, print the array.
    //else print the "we failed" sentence.
}
void searchHelper(char** arr, char* word, int row, int column, int length){

    //find the second letter, within the 3x3 of the first letter

    //Here we define our movement pattern  of all 8 possible directions using malloc
    int r_move = (int*)malloc(8 * sizeof(int));
    int c_move = (int*)malloc(8 * sizeof(int));

    *(r_move + 0) = -1; *(c_move + 0) = -1;
    *(r_move + 1) = -1; *(c_move + 1) = 0;
    *(r_move + 2) = -1; *(c_move + 2) = 1;
    *(r_move + 3) = 0; *(c_move + 3) = -1;
    *(r_move + 4) = 0; *(c_move + 4) = 1;
    *(r_move + 5) = 1; *(c_move + 5) = -1;
    *(r_move + 6) = 1; *(c_move + 6) = 0;
    *(r_move + 7) = 1; *(c_move + 7) = 1;

    int WordFound = 0;

//The next two loops create an index that goes through each possible direction that the next letter can be in
    // for (int i = 0; i < 8; i++){
    //     int r_index = row;
    //     int c_index = column;
    //     for (int j = 0; j < length; j++){
    //         r_index  = r_index + *(r_move + i);
    //         c_index = c_index + *(c_move + i);
    //     }
    // }

    //


    word++;
    length--;
    row = 0; //second letter row
    column = 0; //second letter column
    searchHelper(arr, word, row, column, length);
    
    
    //Find some way to detect if we've finished the word, and return all the way back up to the top.
    //Don't return true if you find it, just return the array, and at the end, if the array
    //doesn't have all the letters, consider it a failure.
}
