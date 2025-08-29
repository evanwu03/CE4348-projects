#ifndef DISK_H
#define DISK_H 


typedef struct { 
    const char *mnemonic;
    int opcode; 
    int num_args;
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


static const InstructionInfo InstrTable[] = 
{
    {"exit",          EXIT,          0},
    {"load_const",    LOAD_CONST,    1},
    {"move_from_mbr", MOV_FROM_MBR,  0},
    {"move_from_mar", MOV_FROM_MAR,  0},
    {"move_to_mbr",   MOV_TO_MBR,    0},
    {"move_to_mar",   MOV_TO_MAR,    0},
    {"load_at_addr",  LOAD_AT_ADDR,  0},
    {"write_at_addr", WRITE_AT_ADDR, 0},
    {"add",           ADD,           0},
    {"multiply",      MULT,          0},
    {"and",           AND,           0},
    {"or",            OR,            0}, 
    {"ifgo",          IFGO,          1},
    {"sleep",         SLEEP,         0},
};



void load_program(const char* fname, const int addr); 
int* translate(const char* instruction);

#endif DISK_H 