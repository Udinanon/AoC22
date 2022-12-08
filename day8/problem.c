#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

/*3 step appraoch
1. create basic matric and fill with data
2. for each perimeter element, check visibility towards center
3. count all values in visibility matrix

*/

void print_matrix(char** matrix, int size);

int compute_scenic_score(char **matrix, int x, int y, int size);

int main(void)
{

    FILE *fp; // open file
    char crates_file[] = "./test.txt";
    if ((fp = fopen(crates_file, "r+")) == NULL)
    { // check for file access,
        printf("ERROR READING FILE %s", crates_file);
        perror("ERROR: ");
        return EXIT_FAILURE;
    }
    printf("Acessed file\n");

    // allocate variables to read filelines
    char *line_buf = NULL;
    size_t line_buf_size = 0;
    int line_size;

    // read first line and read matrix size
    line_size = getline(&line_buf, &line_buf_size, fp);
    int n_columns = line_size - 1;
    // free memory and reset file pointer
    free(line_buf);
    fseek(fp, 0, SEEK_SET);

    // copy data from file to memory
    char symbol;
    int x = 0, y = 0;
    // Old method, not alllwing for passing of pointers
    // char data_matrix[n_columns][n_columns];
    // char visibility_matrix[n_columns][n_columns];
    //  New Method allows for pointer passing of 2D arrays
    char **visibility_matrix;
    visibility_matrix = malloc(n_columns * sizeof *visibility_matrix);
    for (int i = 0; i < n_columns; i++)
    {
        visibility_matrix[i] = malloc(n_columns * sizeof *visibility_matrix[i]);
    }
    char **data_matrix;
    data_matrix = malloc(n_columns * sizeof *data_matrix);
    for (int i = 0; i < n_columns; i++)
    {
        data_matrix[i] = malloc(n_columns * sizeof *data_matrix[i]);
    }

    while ((symbol = getc(fp)) != EOF)
    {
        if (symbol == '\n')
        {
            x++;
            y = 0;
        }
        else
        {
            data_matrix[x][y] = strtol(&symbol, NULL, 10);
            y++;
        }
    }
    // prepare the visibility matrix
    for (int i = 0; i < n_columns; i++)
    {
        for (int j = 0; j < n_columns; j++)
        {
            visibility_matrix[i][j] = 0;
            if (i == 0 || i == n_columns - 1 || j == 0 || j == n_columns - 1)
            {
                visibility_matrix[i][j] = 1;
            }
        }
    }

    // for each elem in perimeter, look inward and set to visible any object taht is higher than all the previous ones, stop whrn you find 9
    // matrix is data[row][column]
    // first row, looking down
    int i = 0; // line 0
    for (int j = 1; j < n_columns - 1; j++)
    { // skip frst and last, they're already known
        int highest_tree = 0;
        for (int k = i; k < n_columns; k++)
        { // start from top row and go down
            if (data_matrix[k][j] > highest_tree)
            { // if we find higehr trees update values
                visibility_matrix[k][j] = 1;
                highest_tree = data_matrix[k][j];
                if (highest_tree == 9)
                { // if we find 9 break and move to next column
                    k = n_columns;
                }
            }
        }
    }

    i = n_columns - 1; // line n
    for (int j = 1; j < n_columns - 1; j++)
    { // skip first and last, they're already known
        int highest_tree = 0;
        for (int k = i; k > 0; k--)
        { // start from bottom row and go up
            if (data_matrix[k][j] > highest_tree)
            { // if we find higher trees update values
                visibility_matrix[k][j] = 1;
                highest_tree = data_matrix[k][j];
                if (highest_tree == 9)
                { // if we find 9 break and move to next column
                    k = n_columns;
                }
            }
        }
    }

    i = 0; // column 0
    for (int j = 1; j < n_columns - 1; j++)
    { // skip frst and last, they're already known
        int highest_tree = 0;
        for (int k = i; k < n_columns; k++)
        { // start from left row and go right
            if (data_matrix[j][k] > highest_tree)
            { // if we find higehr trees update values
                visibility_matrix[j][k] = 1;
                highest_tree = data_matrix[j][k];
                if (highest_tree == 9)
                { // if we find 9 break and move to next row
                    k = n_columns;
                }
            }
        }
    }

    i = n_columns - 1; // column n
    for (int j = 1; j < n_columns - 1; j++)
    { // skip first and last, they're already known
        int highest_tree = 0;
        for (int k = i; k > 0; k--)
        { // start from right row and go left
            if (data_matrix[j][k] > highest_tree)
            { // if we find higher trees update values
                visibility_matrix[j][k] = 1;
                highest_tree = data_matrix[j][k];
                if (highest_tree == 9)
                { // if we find 9 break and move to next column
                    k = n_columns;
                }
            }
        }
    }
    // print data matrix
    int sum = 0;
    for (int i = 0; i < n_columns; i++)
    {
        for (int j = 0; j < n_columns; j++)
        {
            printf("%d", visibility_matrix[i][j]);
            if (visibility_matrix[i][j] == 1)
            {
                sum++;
            }
        }
        printf("\n");
    }
    printf("\n");
    // print visibility matrix
    print_matrix(data_matrix, n_columns);
    printf("TOTAL VISIBLE TREES: %d\n", sum);
    int best_score = -1, score;
    for (int x = 0; x < n_columns; x++)
    {
        for (int y = 0; y < n_columns; y++)
        {
            score = compute_scenic_score(data_matrix, x, y, n_columns);
            if (score > best_score)
            {
                best_score = score;
            }
        }
    }
    printf("BEST SCIENIC SCORE: %d\n", best_score);
}

void print_matrix(char **matrix, int size)
{
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            printf("%d", matrix[i][j]);
        }
        printf("\n");
    }
}

int compute_scenic_score(char **matrix, int x, int y, int size)
{ // check from matrix[x][y] in all directions
    // matrix is data[row][column]
    int base_height = matrix[x][y];
    int score = 1;
    int tmp_val = 0;
    for (int i = x+1; i < size; i++)
    {   
        if(tmp_val == 0){
            tmp_val = 1;
        }

        if (matrix[i][y] < base_height)
        {
            tmp_val++;
        }
        else
        {
            tmp_val--;
            i = size;
        }
    }
    score *= tmp_val;
    tmp_val = 0;
    for (int i = x-1; i >= 0; i--)
    {
        if (tmp_val == 0)
        {
            tmp_val = 1;
        }
        if (matrix[i][y] < base_height)
        {
            tmp_val++;
        }
        else{
            tmp_val--;
            i = -1;
        }
    }
    score *= tmp_val;
    tmp_val = 0;
    for (int i = y-1; i >= 0; i--)
    {
        if (tmp_val == 0)
        {
                tmp_val = 1;
        }
        if (matrix[x][i] < base_height)
        {
            tmp_val++;
        }
        else
        {
            tmp_val--;
            i = -1;
        }
    }
    score *= tmp_val;
    tmp_val = 0;
    for (int i = y+1; i < size; i++)
    {
        if (tmp_val == 0)
        {
            tmp_val = 1;
        }
        if (matrix[x][i] < base_height)
        {
            tmp_val++;
        }
        else
        {
            tmp_val--;
            i = size;
        }
    }
    score *= tmp_val;
    return score;

}