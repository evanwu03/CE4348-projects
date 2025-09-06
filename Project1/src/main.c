
#include "../include/cpu.h"
#include "../include/disk.h"
#include "string.h"

const char fname[] = "../tests/programs/program_add.txt";

int main()
{
    memset(memory, 0, sizeof(memory));
    memset(&cpu_regs, 0, sizeof(cpu_regs));
    cpu_regs.Base = 4; 
    
    int addr = 4;

    load_program(fname, addr);

    while (clock_cycle()) { }

    //for (int i = 0; i < 20; i++) { 

        
    //}

    Instruction res = {0};
    mem_read(18, &res);

    printf("Data at Memory[18]: %d\n", res.arg);
}