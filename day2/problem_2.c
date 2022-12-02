#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_CHARS 4

int main(void)
{
    FILE *fp;
    char filename[] = "./input_1.txt";
    if ((fp = fopen(filename, "r+")) == NULL)
    { // check for file access,
        printf("ERROR READING FILE %s", filename);
        return 1;
    }
    int score = 0;
    char data[MAX_CHARS];
    while (fgets(data, MAX_CHARS, fp) != NULL)
    { // read all file lines
        if (data[0] == 'A' && data[2] == 'X')
        {
            score += 0 + 3;
        }
        else if (data[0] == 'A' && data[2] == 'Y')
        {
            score += 3 + 1;
        }
        else if (data[0] == 'A' && data[2] == 'Z')
        {
            score += 6 + 2;
        }
        else if (data[0] == 'B' && data[2] == 'X')
        {
            score += 0 + 1;
        }
        else if (data[0] == 'B' && data[2] == 'Y')
        {
            score += 3 + 2;
        }
        else if (data[0] == 'B' && data[2] == 'Z')
        {
            score += 6 + 3;
        }
        else if (data[0] == 'C' && data[2] == 'X')
        {
            score += 0 + 2;
        }
        else if (data[0] == 'C' && data[2] == 'Y')
        {
            score += 3 + 3;
        }
        else if (data[0] == 'C' && data[2] == 'Z')
        {
            score += 6 + 1;
        }
    }

    fclose(fp); // close file
    printf("%d\n", score);
    return 0;
}