#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#define matrix_size 1000
#define N_KNOTS 9

struct knot
{
    int pos[2];
    int index;
    struct knot *head;
    struct knot *tail;
};

void print_rope(struct knot *);
void update_head(struct knot *, char);
void update_tail(struct knot *);
struct knot *create_knot(struct knot *, int);
void update_matrix(int **, struct knot *);
int compute_visited(int **);