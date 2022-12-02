#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void update_max(int*, int);

int main(void)
{
    FILE *fp;
    char filename[] = "./input_1.txt";
    if ((fp = fopen(filename, "r+")) == NULL)
    { // check for file access,
        printf("ERROR READING FILE %s", filename);
        return 1;
    }
    // setup needed variables
    char data[255];
    int max[] = {0, 0, 0};
    int number = 0, sum = 0;

    while (fgets(data, 100, fp) != NULL)
    { // read all file lines
        if (strcmp(data, "\n") == 0)
        {                        // if line is a \n
            //printf("%d\n", sum); // print final sum of block
            update_max(max, sum);
            sum = 0, number = 0; // reset values
            //printf("LINE\n");    // signal
        }

        number = atoi(data); // convert text to number
        sum = sum + number;  // update sum
    }

    fclose(fp); // close file
    printf("\n");
    printf("%d\n", max[0]+max[1]+max[2]); // return result
    return 0;
}

void update_max(int* max, int sum){
    int position = -1;
    for(int i=0; i<3; i++){
        if (sum > max[i]){
            position = i;
        }
    }
        switch (position)
        {
        case 2:
            max[0] = max[1];
            max[1] = max[2];
            max[2] = sum;

            break;
        
        case 1:
            max[0] = max[1];
            max[1] = sum;
            break;

        case 0:
            max[0] = sum;
            break;
        default:
        }
    }

