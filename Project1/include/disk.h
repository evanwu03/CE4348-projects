#ifndef DISK_H
#define DISK_H 

#include "memory.h"

#define ARRAY_LEN(a) (sizeof(a) / sizeof((a)[0]))

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


typedef enum { 
    TR_OK = 0,
    TR_UNKNOWN_INSTR,
    TR_ARG_NOT_NUMERIC,
    TR_UNEXPECTED_ARG
} translate_status_t;

typedef enum{ 
    LOAD_OK = 0,
    LOAD_ERR 
} load_status_t;


load_status_t load_program(const char* fname, int addr); 
translate_status_t  translate(char* instruction, Instruction* outInstr);
static bool string_is_number(const char* str);

#endif //DISK_H 