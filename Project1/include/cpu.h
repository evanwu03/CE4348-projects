#include <stdint.h>
#include <stdbool.h>


typedef struct { 
    uint32_t Base;
    uint32_t PC;
    uint32_t IR0;
    int32_t IR1;
    int32_t AC;
    uint32_t MAR;
    int32_t MBR;
} cpu_regs_t;


extern cpu_regs_t cpu_regs;
extern bool running; 


void fetch_instruction(const int addr);
void execute_instruction();
int clock_cycle();

// Instruction operations
/*
    load_const, 
    move_from_mbr,
    move_from_mar,
    move_to_mbr,
    move_to_mar, 
    load_at_addr,
    write_at_addr,
    add,
    multiply,
    and,
    or,
    ifgo, 
    sleep
*/
