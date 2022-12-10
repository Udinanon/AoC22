#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct CPU{
    int cycle;
    int reg;
    int total;
};

void noop_CPU(struct CPU* cpu){ // wait for 1 cycle and update total if needed
    cpu->cycle++;
    if (((cpu->cycle - 20) % 40) == 0){
        cpu->total+=(cpu->reg*cpu->cycle);
    }
}

void addx_CPU(struct CPU* cpu, int add){ // wait 2 times and then add value
    noop_CPU(cpu);
    noop_CPU(cpu);
    cpu->reg+=add;
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
        if(line_buf[0]=='n'){
            noop_CPU(&cpu);
        } else if (line_buf[0]=='a'){
            int value = strtol(line_buf+5, NULL, 10);
            addx_CPU(&cpu, value);
        }

        line_count++;
        line_size = getline(&line_buf, &line_buf_size, fp);
    }
    printf("TOTAL %d, N_CYCLES %d\n", cpu.total, cpu.cycle);

    free(line_buf);
}