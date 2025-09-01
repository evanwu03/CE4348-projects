#include <stdint.h>


typedef struct { 
    uint32_t Base;
    uint32_t IR0;
    int32_t IR1;
    int32_t AC;
    uint32_t MAR;
    int32_t MBR;
} cpu_regs_t;


extern cpu_regs_t cpu_regs;


void fetch_instruction(const int addr);