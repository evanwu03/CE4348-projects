#include "../include/memory.h"


int memory[MEM_SIZE][MEM_FIELDS] = {0};

int* mem_read(int addr) {
    return memory[addr]; // naive implementation, no out-of-bounds handling
}

void mem_write(int addr, int* data){
    memory[addr][ARG_IDX] = *data;
}
