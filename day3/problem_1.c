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
    char* line_buf = NULL;
    size_t line_buf_size = 0;
    int line_count = 0;
    int line_size;
    
    int total_priority=0;
    
    // read lines in order
    line_size = getline(&line_buf, &line_buf_size, fp);
    while ((line_size >= 0)){
        //printf("line[%06d]: chars=%06d, buf size=%06zu, contents: %s", line_count, line_size, line_buf_size, line_buf);
        
        // dopy the 2nd half o fthe line in half_string
        size_t half_line = (line_size-1)/2;
        char half_string[half_line+1];
        strncpy(half_string, line_buf + half_line, half_line);
        half_string[half_line]='\0';
        printf("%s\n", half_string);
        // 
        size_t offset = strcspn(line_buf, half_string);
        char common_char =line_buf[offset];
        int priority = common_char - 96;
        if (isupper(common_char)){
            priority += 58;
        }
        total_priority += priority;

        // prepare for and read next line
        line_count++;
        line_size = getline(&line_buf, &line_buf_size, fp);
    };
    printf("Result: %d\n", total_priority);

    // free text buffeer and return
    free(line_buf);
    line_buf = NULL;
    return EXIT_SUCCESS;
}