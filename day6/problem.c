#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define N_SYMBOLS 14

int main(void)
{

    FILE *fp; // open file
    char crates_file[] = "./input.txt";
    if ((fp = fopen(crates_file, "r+")) == NULL)
    { // check for file access,
        printf("ERROR READING FILE %s", crates_file);
        perror("ERROR: ");
        return EXIT_FAILURE;
    }
    printf("Acessed file\n");
    char buff[N_SYMBOLS] = {
        '0'
    };
    bool found = false;

    // allocate variables to read filelines
    int pos = 0;
    char symbol;
    while ((symbol = getc(fp)) != EOF)
    {
        buff[pos % N_SYMBOLS] = symbol;
        if(pos>(N_SYMBOLS-1)){
            found = true;
        }
        for(int i=0; i<N_SYMBOLS; i++){
            for(int j=0; j<N_SYMBOLS; j++){
                if(i!=j){
                    if (buff[i] == buff[j]){
                        found = false;
                    }
                }
            }
        }
        if (found){
            break;
        }
        pos++;
    }
    printf("FOUND: %d\n", pos+1);

}