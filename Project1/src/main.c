
#include "../include/cpu.h"
#include "../include/disk.h"
#include <string.h>
#include <stdio.h>

const char fname[] = "../tests/programs/program_add.txt";

int main()
{
    memset(memory, 0, sizeof(memory));
    memset(&cpu_regs, 0, sizeof(cpu_regs));
    cpu_regs.Base = 4; 
    
    int addr = 4;

    load_program(fname, addr);

    // Execute program
    while (clock_cycle()) { }

    for (int i = 0; i < 20; i++) { 
        Instruction res;
        mem_read(i, &res);
        printf("Data at Memory[%u]:\tOpcode:%u,\tArgument: %d\n", i, res.opcode, res.arg);
    }
}