#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

int main(void){

    FILE *fp; // open file
    char filename[] = "./input.txt";
    if ((fp = fopen(filename, "r+")) == NULL)
    { // check for file access,
        printf("ERROR READING FILE %s", filename);
        perror("ERROR: ");
        return EXIT_FAILURE;
    }
    printf("Acessed file\n");

    // allocate variables to read filelines
    char* line_buf_1 = NULL;
    char* line_buf_2 = NULL;
    char* line_buf_3 = NULL;
    size_t line_buf_size = 0;
    int line_count = 0;
    size_t line_size[3];
    
    int total_priority=0;
    
    // read lines in order
    line_size[0] = getline(&line_buf_1, &line_buf_size, fp);
    line_size[1] = getline(&line_buf_2, &line_buf_size, fp);
    line_size[2] = getline(&line_buf_3, &line_buf_size, fp);
    while ((line_size[0] >= 0) && (line_size[1] >= 0) && (line_size[2] >= 0) && line_count < 300)
    {
        
        char common_chars[50]="";
        int i=0;

        char* common_char = strpbrk(line_buf_1, line_buf_2);
        while (common_char != NULL)
        {
            common_chars[i]=*common_char;
            common_char = strpbrk(common_char+1, line_buf_2);
            i++;
        }
        
        char final[50] = "";
        i = 0;

        common_char = strpbrk(common_chars, line_buf_3);
        while (common_char != NULL)
        {
            final[i] = *common_char;
            common_char = strpbrk(common_char+1, line_buf_3);
            i++;
        }
        int priority = final[0] - 96;
        if (isupper(final[0]))
        {
            priority += 58;
        }
        total_priority += priority;
        // prepare for and read next line
        line_count+=3;
        line_size[0] = getline(&line_buf_1, &line_buf_size, fp);
        line_size[1] = getline(&line_buf_2, &line_buf_size, fp);
        line_size[2] = getline(&line_buf_3, &line_buf_size, fp);
    }
    printf("Result: %d\n", total_priority);

    // free text buffeer and return
    free(line_buf_1);
    free(line_buf_2);
    free(line_buf_3);
    return EXIT_SUCCESS;
}