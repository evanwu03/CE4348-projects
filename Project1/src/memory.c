#include "../include/memory.h"


int memory[MEM_SIZE][MEM_FIELDS] = {0};

mem_status_t mem_read(const int addr, Instruction* const instr){

    if(!instr) return MEM_ERR_NULL; 

    if(addr < 0 || addr >= MEM_SIZE) return MEM_ERR_OOB;

    instr->opcode = memory[addr][OPCODE_IDX];
    instr->arg    = memory[addr][ARG_IDX];
    return MEM_OK;
}

// Precondition: data must point to an array of MEM_FIELDS ints (opcode, arg)
mem_status_t mem_write(const int addr, const Instruction* const instr){
    if(!instr) return MEM_ERR_NULL; 

    if(addr < 0 || addr >= MEM_SIZE) return MEM_ERR_OOB;

    memory[addr][OPCODE_IDX] = instr->opcode;
    memory[addr][ARG_IDX]    = instr->arg;
    return MEM_OK;
}
