#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define N_SYMBOLS 14


// 5-tree node structure
struct folder{
    char* name;
    int size;
    struct folder* parent; // poiinter to parent node
    struct folder* child[50]; // pointer to up to 5 children
    int child_num; 
};

struct folder* folder_create(struct folder* parent, char* name);
void folder_increase(struct folder* node, int value);
struct folder* folder_new(char* name);
void folder_delete(struct folder* node);
int print_tree_sizes(struct folder *node, int sum);
struct folder *find_smallest_node(struct folder *node, int threshold);

int main(void){

    FILE *fp; // open file
    char crates_file[] = "./input.txt";
    if ((fp = fopen(crates_file, "r+")) == NULL)
    { // check for file access,
        printf("ERROR READING FILE %s", crates_file);
        perror("ERROR: ");
        return EXIT_FAILURE;
    }
    printf("Acessed file\n");
    // create root node
    // root avoids creator to allow use of NULL as flag for being root
    struct folder root = {"root", 0, NULL, {NULL}, 0};

    struct folder *place = &root;
    // crate parser to convert input in nodess
    // allocate variables to read filelines
    char *line_buf = NULL;
    size_t line_buf_size = 0;
    int line_count = 0;
    int line_size;

    // read lines in order
    line_size = getline(&line_buf, &line_buf_size, fp);
    while ((line_size >= 0))
    {
        printf("line[%06d]: chars=%06d, buf size=%06zu, contents: %s\n", line_count, line_size, line_buf_size, line_buf);
        if (line_buf[0] == '$')
        { // command
            if (line_buf[2] == 'c')
            { // cd - create new node and move to it
                if (line_buf[5] == '.')
                { // moving up a level
                    place = place->parent;
                }
                else
                { // mooving deeper
                    // create new node
                    struct folder *node = folder_create(place, line_buf + 5);
                    // move current pointer
                    place = node;
                }
            }
        }
        else
        { // file or directory
            if (!(line_buf[0] == 'd'))
            { // not a directory
                char *tmp;
                int value = 0;
                tmp = strtok(line_buf, " ");
                value = strtol(tmp, NULL, 10);
                folder_increase(place, value);
            }
        }

        // prepare for and read next line
        line_count++;
        line_size = getline(&line_buf, &line_buf_size, fp);
    }
    int sum = 0;
    sum = print_tree_sizes(&root, sum);
    printf("SUM UNDER 100000: %d\n", sum);
    printf("TOTAL OCCUPIED SIZE: %d\n", root.size);
    int needed_space = 30000000 - (70000000 - root.size);
    printf("NEEDED SPACE: %d\n", needed_space);
    struct folder* smallest_valid_folder = find_smallest_node(&root, needed_space);
    printf("SMALLEST VALID NODE: %d %s\n", smallest_valid_folder->size, smallest_valid_folder->name);
    // probably can ignore dir info and create folder nodes as they get visited
    // issues remains the final check, but we can probably doa  DFS recursive algorithm and just pass a sum parameter along for the ride
}

int print_tree_sizes(struct folder* node, int sum){
    if (node->size <= 100000 ){
        sum+=(node->size);
    }
    for(int i=0; i<(node->child_num); i++){
        sum = print_tree_sizes(node->child[i], sum);
    }
    return sum;
}

struct folder* find_smallest_node(struct folder* node, int threshold){
    struct folder* potential;
    if (node->size >= threshold){
        potential = node;
        printf("NODE: %s SIZE: %d\n", node->name, node->size);
        struct folder* tmp;
        for (int i = 0; i < (node->child_num); i++){
            tmp = find_smallest_node(node->child[i], threshold);
            if ((tmp != NULL) && (tmp->size <= potential->size)){
                potential = tmp;
            }
        }
        return potential;
    } else { 
        return NULL;
    }
}

//passing around structure pointers is not as hard as i thought
struct folder* folder_create(struct folder* parent, char* name){
    struct folder* node = folder_new(name);
    if (parent == NULL || node == NULL){
        return false;
    }
    node->parent = parent;
    parent->child[parent->child_num] = node;
    parent->child_num++;
    return node;

}

void folder_increase(struct folder* node, int value){
    if (node==NULL){
    return ;
    }
    node->size += value;
    
    folder_increase(node->parent, value);
}

struct folder* folder_new(char* name){
    struct folder* node = malloc(sizeof(struct folder));

    if (node == NULL){
        return NULL;
    }
    else{
        // initialize node contents
        node->parent = NULL;
        node->name = strdup(name);
    }

    return node;
}

void folder_delete(struct folder* node){
    if (node != NULL){
        if (node->name != NULL)
            free(node->name);
        free(node);
    }
}