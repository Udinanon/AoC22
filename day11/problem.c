#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define N_MONKEYS 4
#define N_ROUNDS 10000

typedef struct Queue Queue; 
typedef struct node Node;
typedef struct Monkey Monkey;

struct node{
    unsigned long long data;
    struct node* next;
};

struct Queue{
    int count;
    Node* begin;
    Node* end;
};

struct Monkey{
    Queue* held;
    int index;
    int counter;    

    int update_type;
    long update_value;
    int test_value;
    
    Monkey* true;
    Monkey* false;

};

void moneky_update(Monkey* monkey);

void queue_add(Queue *queue, unsigned long long data);
unsigned long long queue_get(Queue *queue);

void moneky_update(Monkey* monkey){
    // update worry based on monkey properties
    if(monkey->held->count==0){
        return;
    }
    unsigned long long worry = queue_get(monkey->held);
    unsigned long long old = worry;
    monkey->counter++;
    switch (monkey->update_type){
    case 0: // sum
        worry += monkey->update_value;
        break;
    case 1: // product
        worry *= monkey->update_value;
        break;
    case 2: // squaring
        worry *= worry;
        break;
    default:
        printf("UNRECOGNIZED UPDATE TYPE: %d\n", monkey->update_type);
        break;
    }
    if (old > worry || worry < 0){
        printf("ERROR %d %d\n", old, worry);
        getchar();
    }
    //worry = worry / 3;
    // compute if test passed and send object to other monkeys
    if (worry % monkey->test_value == 0){
        queue_add(monkey->true->held, worry);
    } else {
        queue_add(monkey->false->held, worry);
    }
}

unsigned long long queue_get(struct Queue *queue)
{
    Node* begin = queue->begin;
    unsigned long long tmp_data = begin->data;
    queue->begin = begin->next;
    if(queue->begin == NULL){
        queue->end=NULL;
    }
    free(begin);
    queue->count--;
    return tmp_data;
}

void queue_add(struct Queue *queue, unsigned long long data)
{
    // create node
    Node* node = malloc(sizeof(Node));
    node->data=data;
    node->next = NULL;
    // check if list is empty
    if (queue->end == NULL){
        if (queue->begin != NULL){ // sanity check
            printf("QUEUE MAKES NO SENSE, end IS NULL BUT BEGIN IS NOT");
            getchar();
        }
        queue->begin = node;
    } else { // if not, link at old last value
        queue->end->next = node;
    }
    // rediredct pointer to last node
    queue->end = node;
    queue->count++;
}

int main(void){
   
    FILE *fp; // open file
    char in_file[] = "./test.txt";
    if ((fp = fopen(in_file, "r+")) == NULL)
    { // check for file access,
        printf("ERROR READING FILE %s", in_file);
        perror("ERROR: ");
        return EXIT_FAILURE;
    }
    printf("Acessed file\n");

    // allocate variables to read filelines
    char *line_buf = NULL;
    size_t line_buf_size = 0;
    int line_count = 0;
    int line_size;

    // allocate monkeys pointer and monkey memory
    struct Monkey** monkeys = malloc(N_MONKEYS * sizeof(struct Monkey*));
    for(int i = 0; i<N_MONKEYS; i++){
        monkeys[i] = malloc(sizeof(struct Monkey));
    } 

    do{ // read 7 lines

        // read monkey index
        line_size = getline(&line_buf, &line_buf_size, fp);
        line_count++;
        struct Monkey* monkey = monkeys[strtol(line_buf + line_size-3, NULL, 10)];
        monkey->index = strtol(line_buf + line_size - 3, NULL, 10);

        // read held objects
        char* tmp;
        unsigned long long value = 0;
        line_size = getline(&line_buf, &line_buf_size, fp);
        line_count++;
        tmp = strtok(line_buf+18, ",");
        monkey->held = malloc(sizeof(Queue)); // declare queue and strat filling
        queue_add(monkey->held, strtol(tmp, NULL, 10));
        tmp = strtok(NULL, ",");
        while(tmp != NULL){
            value = strtol(tmp, NULL, 10);
            queue_add(monkey->held, value);
            tmp = strtok(NULL, ",");
        }

        // read update worry method
        line_size = getline(&line_buf, &line_buf_size, fp);
        line_count++;
        switch (line_buf[23]){
            case '+':
                monkey->update_type = 0; //sum
                monkey->update_value = strtol(line_buf+25, NULL, 10);
                break;
            case '*':
                if (line_buf[25] == 'o'){
                    monkey->update_type = 2; // square
                    monkey->update_value = -1;
                } else {monkey->update_type = 1; // product
                    monkey->update_value = strtol(line_buf + 25, NULL, 10);
                }
                break;
            default:
                printf("UNRECOGNIZED UPDATE TYPE IN: %s\n", line_buf);
                break;
        }

        //read test value
        line_size = getline(&line_buf, &line_buf_size, fp);
        line_count++;
        monkey->test_value = strtol(line_buf+21, NULL, 10);

        // read true case monkey
        line_size = getline(&line_buf, &line_buf_size, fp);
        line_count++;
        monkey->true = monkeys[strtol(line_buf + 29, NULL, 10)];

        // read false case monkey
        line_size = getline(&line_buf, &line_buf_size, fp);
        line_count++;
        monkey->false = monkeys[strtol(line_buf + 30, NULL, 10)];

        // empty or NULL line
        line_size = getline(&line_buf, &line_buf_size, fp);
        line_count++;

    } while ((line_size >= 0));
    //printf("%d\n",monkeys[1]);

    free(line_buf);

    // update monkeys
    for(int round = 0; round < N_ROUNDS; round++){
        for(int i = 0; i<N_MONKEYS; i++){
            int obj_count = monkeys[i]->held->count;
            for (int j = 0; j < obj_count; j++){
                moneky_update(monkeys[i]);
            }
        }
    }
    int values[N_MONKEYS]={0};
    for(int i = 0; i<N_MONKEYS; i++){

        values[i]=monkeys[i]->counter;
        printf("MONKEY %d COUNT %d\n", i, values[i]);
    }


}