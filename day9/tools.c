#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#include "tools.h"

void print_rope(struct knot *knot)
{
    printf(" %d POS %d %d ", knot->index, knot->pos[0], knot->pos[1]);
    if (knot->tail == NULL)
    { // tail fo the rope
        printf("\n");
    }
    else
    { // continue recurisvely
        print_rope(knot->tail);
    }
}

void update_head(struct knot *head_knot, char dir)
{
    switch (dir)
    {
    case 'R':
        head_knot->pos[0]++;
        break;
    case 'U':
        head_knot->pos[1]++;
        break;
    case 'L':
        head_knot->pos[0]--;
        break;
    case 'D':
        head_knot->pos[1]--;
        break;
    default:
        printf("ERROR UNRECOGNIZED CHAR: %c\n", dir);
        break;
    }
}

void update_tail(struct knot *knot)
{
    struct knot *head = knot->head;
    int diff_x = head->pos[0] - knot->pos[0];
    int diff_y = head->pos[1] - knot->pos[1];
    int taxt_dist = abs(diff_x) + abs(diff_y);
    if ((taxt_dist < 2) || (abs(diff_x) == abs(diff_y)))
    {
        // taxi < 2 is obvius
        // diffx == diff_y meqans it's either 0,0 or 1,1, 2,2 is not spossible as it can't move diagonally
        return;
    }
    knot->pos[0] += (diff_x > 0) - (diff_x < 0);
    knot->pos[1] += (diff_y > 0) - (diff_y < 0);
    if (knot->tail != NULL)
    { // continue recursively
        update_tail(knot->tail);
    }
};

struct knot *get_end(struct knot *knot)
{ // recursively find last piece
    if (knot->tail == NULL)
    {
        return knot;
    }
    return get_end(knot->tail);
}

struct knot *create_knot(struct knot *curr_knot, int index)
{ // create pieces and link them together
    struct knot *knot = malloc(sizeof(struct knot));
    knot->pos[0] = matrix_size / 2;
    knot->pos[1] = matrix_size / 2;
    knot->head = curr_knot;
    knot->tail = NULL;
    knot->index = index;
    curr_knot->tail = knot;
    return knot;
}

void update_matrix(int **matrix, struct knot *head_knot)
{ // update matrix positions
    struct knot *end = get_end(head_knot);
    int x = end->pos[0], y = end->pos[1];
    matrix[x][y] = 1;
}

int compute_visited(int **matrix)
{
    int counter = 0;
    for (int i = 0; i < matrix_size; i++)
    {
        for (int j = 0; j < matrix_size; j++)
        {
            counter += matrix[i][j];
        }
    }
    return counter;
}