#ifndef MEMORY_H
#define MEMORY_H


// Constants
enum { MEM_SIZE = 1024, MEM_FIELDS = 2};
enum { OPCODE_IDX = 0, ARG_IDX = 1};

// Simulated memory array
extern int memory[MEM_SIZE][MEM_FIELDS];

// Function Prototypes 
int* mem_read(int addr); 
void mem_write(int addr, int* data);

#endif // MEMORY_H