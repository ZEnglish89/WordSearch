#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>

// Declarations of the two functions you will implement
// Feel free to declare any helper functions or global variables
void printPuzzle(char** arr);
void searchPuzzle(char** arr, char* word);
bool searchHelper(char** arr, char* word, int row, int column, int length);
int bSize;
int** results;
int startingLength;
char*** output;

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

void printResult(char*** out){
    for(int i=0;i<bSize;i++){
        for(int j=0;j<bSize;j++){
            printf("%s",*(*(out+i)+j));
        }
        printf("\n");
    }
}

void writeResult(int** res){
    for(int i=startingLength-1;i>=0;i--){
        if(*(*(res+i))!=-1){
            int row=*(*(res+i));
            int column=*(*(res+i)+1);
            int j=0;
            while(*(*(*(output+row)+column)+j)!='0'&&*(*(*(output+row)+column)+j)!=' '){
                j++;
            }
            *(*(*(output+row)+column)+j) = (i+1)+'0';
        }
    }
}

void searchPuzzle(char** arr, char* word) {
    // This function checks if arr contains the search word. If the 
    // word appears in arr, it will print out a message and the path 
    // as shown in the sample runs. If not found, it will print a 
    // different message as shown in the sample runs.
    // Your implementation here...

    //find the first letter.
    bool successever=false;
    bool successnow=false;
    
    output = (char***)malloc((bSize)*sizeof(char**));
    
    for(int i=0;i<bSize;i++){
        *(output+i)=(char**)malloc((bSize)*sizeof(char*));
        for(int j=0;j<bSize;j++){
            *(*(output+i)+j)=(char*)malloc(7);
            *(*(*(output+i)+j))='0';
            for(int k=1;k<6;k++){
                *(*(*(output+i)+j)+k)=' ';
            }
            *(*(*(output+i)+j)+6)='\0';

        }
    }

    startingLength = strlen(word);
    int length = startingLength;
    
    results = (int**)malloc(length*sizeof(int*)); //Array of int arrays, of the same length as the word being searched. Each int array corresponds to a coordinate pair.
    for(int i=0;i<length;i++){
        *(results+i) = (int*)malloc(2*sizeof(int));
        *(*(results+i))=-1;
        *(*(results+i)+1)=-1;
    } //initialize everything to -1, a number which does not exist within the grid, so we can tell if each element has been modified or not.
    for(int i=0;i<length;i++){ //loop through every letter of the word.
        if(*(word+i)>96&&*(word+i)<123){ //if the current character is a lowercase letter:
            *(word+i)-=32; //capitalize it.
        }
    }
    
    int row = 0; //first letter row
    int column = 0; //first letter column
    
    for(int i=0;i<bSize;i++){
        for(int j=0;j<bSize;j++){
            if(*(*(arr+i)+j)==*(word)){
                *(*(results))=i;
                *(*(results)+1)=j;
                if(startingLength==1){
                    successever=true;
                    writeResult(results);
                }
                successnow = searchHelper(arr,word+1,i,j,length-1); //variable changes made in passing so as not to interfere with their actual values.
                if(successnow){
                    successever=true;
                }
            }
        }
    }

    if(successever){
        printf("\nWord found!\n");
        printf("Printing the search path:\n");
        printResult(output);
    }
    else{
        printf("Word not found!\n");
    }


    //The above for loop is now finding every instance of the first letter of the word, and calling searchHelper on all of them, in order.
    //if the solution array contains the length of the word, print the array.
    //else print the "we failed" sentence.
}
bool searchHelper(char** arr, char* word, int row, int column, int length){
    int top,bottom,left,right;
    //find the second letter, within the 3x3 of the first letter
    //Here we define our movement pattern  of all 8 possible directions using malloc
    if(row>0){
        top=-1;
    }
    else
        top=0;
    if(row<bSize-1){
        bottom=1;
    }
    else
        bottom=0;
    if(column>0){
        left=-1;
    }
    else
        left=0;
    if(column<bSize-1){
        right=1;
    }
    else
        right=0;
        //this setup for the loops will check the valid slots, without any chance of wraparound.
    //For example: If the letter is on the leftmost column, trying to go left will wrap around to the right side of the previous row. Those if statements might not be the most
    //efficient way to set the values, but setting the values prevents wraparound.
    bool found=false;

    for (int i = top; i <= bottom; i++)
    {
        for (int j = left; j <= right; j++)
        {
            if (*word == *(*(arr + i + row) + j + column)&&!(i==0&&j==0))
            {
                *(*(results+(startingLength-length)))=row+i;
                *(*(results+(startingLength-length))+1)=column+j;
                if(length>1){
                    found=searchHelper(arr,word+1,row + i,column + j,length-1);
                    if(found){
                        return true;
                    }
                }
                else{
                    writeResult(results);
                    return true;
                }
            }

        }
    }
    return false;
}