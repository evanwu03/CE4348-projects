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
void execute_instruction();
int  mem_address(const int I_addr); 


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

static void exit() {} 
static void load_const() {}
static void move_from_mbr() {}
static void move_from_mar() {}
static void move_to_mbr() {}
static void move_to_mar() {}
static void load_at_addr() {}
static void write_at_addr() {}
static void add() {}
static void multiply() {}
static void and_op() {}
static void or_op() {}
static void ifgo() {}
static void sleep() {}
