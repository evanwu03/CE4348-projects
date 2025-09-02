#include "../include/cpu.h"
#include "../include/memory.h"
#include "../include/disk.h"

cpu_regs_t cpu_regs;

static const int NUM_INSTRUCTIONS = 14;


// Jump table of all instruction operations
static void (*instruction[NUM_INSTRUCTIONS])() =
{   
    [EXIT]           =  exit,
    [LOAD_CONST]     =  load_const, 
    [MOV_FROM_MBR]   =  move_from_mbr,
    [MOV_FROM_MAR]   =  move_from_mar,
    [MOV_TO_MBR]     =  move_to_mbr,
    [MOV_TO_MAR]     =  move_to_mar, 
    [LOAD_AT_ADDR]   =  load_at_addr,
    [WRITE_AT_ADDR]  =  write_at_addr,
    [ADD]            =  add,
    [MULT]           =  multiply,
    [AND]            =  and_op,
    [OR]             =  or_op,
    [IFGO]           =  ifgo, 
    [SLEEP]          =  sleep
};


void fetch_instruction(const int addr) { 

    Instruction instr = {0};
    mem_read(addr, &instr);

    cpu_regs.IR0 = instr.opcode;
    cpu_regs.IR1 = instr.arg;
}

int  mem_address(const int I_addr) {
    return (cpu_regs.Base + I_addr);
}


void execute_instruction() {

    opcode_t opcode = (opcode_t)cpu_regs.IR0;

    // Look up and execute instruction
    instruction[opcode]();
}