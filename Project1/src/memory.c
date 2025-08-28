#include "../include/memory.h"


int memory[MEM_SIZE][MEM_FIELDS] = {0};

int* mem_read(const int addr) {
    return memory[addr]; // naive implementation, no out-of-bounds handling
}

// Precondition: data must point to an array of MEM_FIELDS ints (opcode, arg)
void mem_write(const int addr, const int* data){
    memory[addr][OPCODE_IDX] = data[OPCODE_IDX];
    memory[addr][ARG_IDX]    = data[ARG_IDX];
}
