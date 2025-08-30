#ifndef DISK_H
#define DISK_H 

#include "memory.h"

typedef struct { 
    const char *mnemonic;
    int opcode; 
    unsigned int num_args;
} InstructionInfo;

typedef enum { 
    EXIT = 0, 
    LOAD_CONST, 
    MOV_FROM_MBR, 
    MOV_FROM_MAR,
    MOV_TO_MBR,
    MOV_TO_MAR,
    LOAD_AT_ADDR,
    WRITE_AT_ADDR,
    ADD,
    MULT,
    AND,
    OR,
    IFGO,
    SLEEP
} opcode_t;

void load_program(const char* fname, int addr); 
Instruction  translate(char* instruction);

#endif //DISK_H 