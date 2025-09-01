#include "../include/cpu.h"
#include "../include/memory.h"

cpu_regs_t cpu_regs;


void fetch_instruction(const int addr) { 

    Instruction instr = {0};
    mem_read(addr, &instr);

    cpu_regs.IR0 = instr.opcode;
    cpu_regs.IR1 = instr.arg;
}

