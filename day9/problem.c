#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#include "tools.h"

#define matrix_size 1000
#define N_KNOTS 9

int main(void){
    FILE* fp; // open file
    char crates_file[] = "./input.txt";
    if ((fp = fopen(crates_file, "r+")) == NULL)
    { // check for file access,
        printf("ERROR READING FILE %s", crates_file);
        perror("ERROR: ");
        return EXIT_FAILURE;
    }
    printf("Acessed file\n");

    // allocate variables to read filelines
    char* line_buf = NULL;
    size_t line_buf_size = 0;
    int line_count = 0;
    int line_size;

    // declare matrix
    int** visited_matrix;
    visited_matrix = malloc(matrix_size * sizeof *visited_matrix);
    for (int i = 0; i < matrix_size; i++)
    {
        visited_matrix[i] = malloc(matrix_size * sizeof *visited_matrix[i]);
    }

    // deaclare rope
    struct knot head = {{matrix_size / 2, matrix_size / 2}, 0, NULL, NULL};
    struct knot* curr_knot = &head;
    for(int i=1; i<N_KNOTS; i++){
        curr_knot = create_knot(curr_knot, i);
    }
    print_rope(&head);

    // read lines in order
    line_size = getline(&line_buf, &line_buf_size, fp);
    while ((line_size >= 0))
    {
        // read number of steps
        int step = strtol(line_buf+2, NULL, 10);
        for(int i = 0; i< step; i++){
            // update head, tail and matrix
            update_head(&head, line_buf[0]);
            update_tail(head.tail);
            update_matrix(visited_matrix, &head);
            print_rope(&head);
            }
        // prepare for and read next line
        line_count++;
        line_size = getline(&line_buf, &line_buf_size, fp);
    }
    int total = compute_visited(visited_matrix);
    printf("TOTAL %d\n", total);

    free(line_buf);
}

