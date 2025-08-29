#ifndef MEMORY_H
#define MEMORY_H

typedef struct { 
    int opcode; 
    int arg;

} Instruction; 

typedef enum { 
    MEM_OK = 0, 
    MEM_ERR_OOB,     // Address access out of bounds
    MEM_ERR_NULL,    // Null pointer argumnet 
    MEM_ERR_UNKNOWN  // Catch all for errors 
} mem_status_t;

// Constants
enum { MEM_SIZE = 1024, MEM_FIELDS = 2};
enum { OPCODE_IDX = 0, ARG_IDX = 1};

// Simulated memory array
extern int memory[MEM_SIZE][MEM_FIELDS];

// Function Prototypes 
mem_status_t mem_read(const int addr,  Instruction* const instr); 
mem_status_t mem_write(const int addr, const Instruction* const instr);

#endif // MEMORY_H