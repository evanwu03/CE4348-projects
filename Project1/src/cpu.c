#include "../include/cpu.h"
#include "../include/memory.h"
#include "../include/disk.h"

// Forward Declarations
static void exit();
static void load_const();
static void move_from_mbr();
static void move_from_mar();
static void move_to_mbr();
static void move_to_mar();
static void load_at_addr();
static void write_at_addr();
static void add();
static void multiply();
static void and_op();
static void or_op();
static void ifgo();
static void sleep();

static int  mem_address(const int I_addr); 



cpu_regs_t cpu_regs;

//static const int NUM_INSTRUCTIONS = 14;
bool running = true; // we'll go ahead and make a file-local flag for cpu state


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


void execute_instruction() {

    opcode_t opcode = (opcode_t)cpu_regs.IR0;

    // Look up and execute instruction
    instruction[opcode]();
}


static int mem_address(const int I_addr) { return (cpu_regs.Base + I_addr);}


int clock_cycle() { 

    fetch_instruction(mem_address(cpu_regs.PC));

    execute_instruction();

    // If exit command has been reached
    if(!running) { 
        return 0;
    }
    
    cpu_regs.PC++;

    return 1;
}

// CPU Instruction definition 
static void exit()          { running      = false;}
static void load_const()    { cpu_regs.AC  = cpu_regs.IR1; }
static void move_from_mbr() { cpu_regs.AC  = cpu_regs.MBR;}
static void move_from_mar() { cpu_regs.AC  = cpu_regs.MAR;}
static void move_to_mbr()   { cpu_regs.MBR = cpu_regs.AC;}
static void move_to_mar()   { cpu_regs.MAR = cpu_regs.AC;}

static void load_at_addr()  { 
   Instruction data = {0};
   mem_read(cpu_regs.MAR, &data);
   cpu_regs.MBR = data.arg;
}

static void write_at_addr() {
    Instruction data = {.opcode = 0, .arg = cpu_regs.MBR};
    mem_write(cpu_regs.MAR, &data);
}

static void add()          {  cpu_regs.AC += cpu_regs.MBR; }
static void multiply()     {  cpu_regs.AC *= cpu_regs.MBR; }
static void and_op()       {  cpu_regs.AC  = cpu_regs.AC && cpu_regs.MBR;}
static void or_op()        {  cpu_regs.AC  = cpu_regs.AC || cpu_regs.MBR;}

static void ifgo() {  
    if(cpu_regs.AC != 0) { 
        cpu_regs.PC = cpu_regs.IR1-1;
    }
}

static void sleep() {return;}

/* End of CPU instruction definitions*/