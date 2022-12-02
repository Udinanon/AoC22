#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(void){
    FILE* fp;
    char filename[] = "./input_1.txt";
    if ((fp = fopen(filename, "r+")) == NULL){ // check for file access, 
        printf("ERROR READING FILE %s", filename);
        return 1;
    }
    // setup needed variables
    char data[255];
    int number = 0, sum = 0, max = 0;
    
    while (fgets(data, 100, fp)!= NULL){ // read all file lines
        if (strcmp(data, "\n") == 0){ //if line is a \n 
            printf("%d\n", sum); // print final sum of block
            if (sum > max){
                max = sum; // save max value
            }
            sum = 0, number = 0; // reset values
            printf("LINE\n"); // signal
        }
        
        number = atoi(data); // convert text to number
        sum = sum + number; // update sum
    }
    
    fclose(fp); // close file
    printf("\n"); 
    printf("%d\n", max); // return result
    return 0;
}