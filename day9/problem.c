#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#define matrix_size 1000

struct rope{
    int head_pos[2];
    int tail_pos[2];
};

void print_rope(struct rope* rope);
void update_head(struct rope* rope, char dir);
void update_tail(struct rope* rope);
void update_matrix(int** matrix, struct rope *rope);
int compute_visited(int **matrix);

void print_rope(struct rope *rope){
    printf("H POS %d %d T POS %d %d\n", rope->head_pos[0], rope->head_pos[1], rope->tail_pos[0], rope->tail_pos[1]);
}

void update_head(struct rope* rope, char dir){
    switch (dir)
    {
    case 'R':
        rope->head_pos[0]++;
        break;
    case 'U':
        rope->head_pos[1]++;
        break;
    case 'L':
        rope->head_pos[0]--;
        break;
    case 'D':
        rope->head_pos[1]--;
        break;
    default:
        printf("ERROR UNRECOGNIZED CHAR: %c\n", dir);
        break;
    }
}

void update_tail(struct rope* rope){
    int diff_x = rope->head_pos[0] - rope->tail_pos[0];
    int diff_y = rope->head_pos[1] - rope->tail_pos[1];
    int taxt_dist = abs(diff_x) + abs(diff_y);
    if ( (taxt_dist < 2) || (abs(diff_x) == abs(diff_y)) ){
        // taxi < 2 is obvius
        // diffx == diff_y meqans it's either 0,0 or 1,1, 2,2 is not spossible as it can't move diagonally
        return;
    }
    rope->tail_pos[0] += (diff_x > 0) - (diff_x < 0);
    rope->tail_pos[1] += (diff_y > 0) - (diff_y < 0);
};

void update_matrix(int** matrix, struct rope* rope){
    int x=rope->tail_pos[0], y=rope->tail_pos[1];
    matrix[x][y] = 1;
}

int compute_visited(int** matrix){
    int counter = 0;
    for (int i=0; i<matrix_size; i++){
        for(int j=0; j<matrix_size; j++){
            counter += matrix[i][j];
        }
    }
    return counter;
}

int main(void)
{


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
    struct rope rope = {{500, 500}, {500, 500}};
    print_rope(&rope);

    // read lines in order
    line_size = getline(&line_buf, &line_buf_size, fp);
    while ((line_size >= 0))
    {
        // read number of steps
        int step = strtol(line_buf+2, NULL, 10);
        for(int i = 0; i< step; i++){
            // update head, tail and matrix
            update_head(&rope, line_buf[0]);
            update_tail(&rope);
            update_matrix(visited_matrix, &rope);
            print_rope(&rope);
            }
        // prepare for and read next line
        line_count++;
        line_size = getline(&line_buf, &line_buf_size, fp);
    }
    int total = compute_visited(visited_matrix);
    printf("TOTAL %d\n", total);

    free(line_buf);
}

