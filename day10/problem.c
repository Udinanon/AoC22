#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct CPU{
    int cycle;
    int reg;
    int total;
};


// the actual code that runs for 1 cycle
void wait_cycle(struct CPU* cpu){ // wait for 1 cycle and update total if needed
    // update screen
    if ((cpu->cycle % 40) == 0)
    {
        printf("\n");
    }
    int sprite_cent = cpu->reg;
    int screen_pos = cpu->cycle %40;
    if (screen_pos == sprite_cent - 1 || screen_pos == sprite_cent || screen_pos == sprite_cent + 1)
    {
        printf("#");
    }
    else
    {
        printf(".");
    }

    // update CPU
    cpu->cycle++;
    if (((cpu->cycle - 20) % 40) == 0){
        cpu->total+=(cpu->reg*cpu->cycle);
    }

}

int main(void){
    FILE *fp; // open file
    char in_file[] = "./input.txt";
    if ((fp = fopen(in_file, "r+")) == NULL){ // check for file access,
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
    line_size = getline(&line_buf, &line_buf_size, fp);

    struct CPU cpu = {0, 1, 0};

    while ((line_size >= 0)){
        if(line_buf[0]=='n'){ // do nothing
            wait_cycle(&cpu);
        } else if (line_buf[0]=='a'){ // add value
            int value = strtol(line_buf+5, NULL, 10);
            wait_cycle(&cpu);
            wait_cycle(&cpu);
            cpu.reg += value;
        }


        line_count++;
        line_size = getline(&line_buf, &line_buf_size, fp);
    }
    printf("\nTOTAL %d, N_CYCLES %d\n", cpu.total, cpu.cycle);

    free(line_buf);
}