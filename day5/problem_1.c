#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define NUM_STACKS 9
struct Crates{
    char crates[100];
    int height;
};


int main(void)
{

    FILE *fp; // open file
    char crates_file[] = "./crates.txt";
    if ((fp = fopen(crates_file, "r+")) == NULL)
    { // check for file access,
        printf("ERROR READING FILE %s", crates_file);
        perror("ERROR: ");
        return EXIT_FAILURE;
    }
    printf("Acessed file\n");

    // allocate variables to read filelines
    int length = 0;
    while (getc(fp) != EOF){ 
        length++;
    }
    printf("LENGTH: %d\n", length);

    struct Crates piles[NUM_STACKS];

    int i = NUM_STACKS-1;
    int height = 0;

    for (int i = 0; i < NUM_STACKS; i++)
    {
        piles[i].height = 0;
        for (int j = 0; j < length + 1; j++)
        {
            piles[i].crates[j] = '\0';
        }
    }

    for (int position = length - 1; position >= 0; ){
        fseek(fp, position, SEEK_SET);
        char character = getc(fp);
        if (iscntrl(character) == 0 && character != ' '){
            piles[i].crates[height] = character;
            piles[i].height++;
            i--;
        } else if (character == ' '){
            i--;
        } else if (character == '\n'){
            height++;
            i = NUM_STACKS-1;
        } 
        position--;
    }
    fclose(fp); // close file

    FILE* fp_2;
    char moves_file[] = "./moves.txt";
    if ((fp_2 = fopen(moves_file, "r+")) == NULL)
    { // check for file access,
        printf("ERROR READING FILE %s", moves_file);
        perror("ERROR: ");
        return EXIT_FAILURE;
    }
    printf("Acessed file\n");
    char *line_buf = NULL;
    size_t line_buf_size = 0;
    int line_count = 0;
    int line_size;


    // read lines in order
    line_size = getline(&line_buf, &line_buf_size, fp_2);
    while ((line_size >= 0))
    {

        //printf("line[%06d]: chars=%06d, buf size=%06zu, contents: %s", line_count, line_size, line_buf_size, line_buf);

        // prepare necessary variables
        char *tmp;
        int values[4];
        int i = 1;
        tmp = strtok(line_buf, " ");
        // parse string
        while (tmp != NULL)
        {
            if(i%2==0){
                int val = strtol(tmp, NULL, 10);
                values[(i/2) - 1]=val;
                //printf("%d %d\n", val, i);
            }
            tmp = strtok(NULL, " ");
            i++;
        }
        for(int i = 0; i<values[0]; i++){
            char tmp;
            int from = values[1]-1, to = values[2]-1;


            tmp = piles[from].crates[piles[from].height-1];
            piles[from].crates[piles[from].height-1] = '\0';
            piles[from].height--;
            
            piles[to].height++;
            piles[to].crates[piles[to].height-1] = tmp;
        }

        // prepare for and read next line
        line_count++;
        line_size = getline(&line_buf, &line_buf_size, fp_2);
    };

    for (int i = 0; i < NUM_STACKS; i++)
    {
        printf("%c", piles[i].crates[piles[i].height-1]);
    }
    printf("\n");
    // free text buffeer and return
    free(line_buf);
    line_buf = NULL;

    return EXIT_SUCCESS;
}