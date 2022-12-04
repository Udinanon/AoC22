#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

int main(void)
{

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
    char *line_buf = NULL;
    size_t line_buf_size = 0;
    int line_count = 0;
    int line_size;

    int counter = 0;

    // read lines in order
    line_size = getline(&line_buf, &line_buf_size, fp);
    while ((line_size >= 0)){

        //printf("line[%06d]: chars=%06d, buf size=%06zu, contents: %s", line_count, line_size, line_buf_size, line_buf);
        
        // prepare necessary variables
        char* tmp;
        int intervals[4];
        int i = 0;
        // parse the file line
        tmp = strtok(line_buf, ",-");
        while(tmp != NULL){
            intervals[i] = strtol(tmp, NULL, 10);
            tmp = strtok(NULL, ",-");
            i++;
        }

        /*for (int i = 0; i < sizeof(intervals) / sizeof(intervals[0]); i++){
            printf("%d ", intervals[i]);
        }
        printf("\n");*/

        //check the intervals 
        if (intervals[0] <= intervals[2] && intervals[1] >= intervals[3]){
            counter++;
        }
        else if (intervals[0] >= intervals[2] && intervals[1] <= intervals[3]){
            counter++;
        }
    

        // prepare for and read next line
        line_count++;
        line_size = getline(&line_buf, &line_buf_size, fp);
    };
    printf("Result: %d\n", counter);

    // free text buffeer and return
    free(line_buf);
    line_buf = NULL;
    return EXIT_SUCCESS;
}