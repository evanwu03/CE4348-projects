#include "CppUTest/TestHarness.h" 
#include "../include/memory.h"
#include "../include/disk.h"
#include "../include/cpu.h"


TEST_GROUP(MemoryTests)
{
    void setup()
    {
        //Init stuff
        memset(memory, 0, sizeof(memory));
    }

    void teardown()
    {

    }
};


TEST(MemoryTests, ReadDataFromMemory)
{
    // Preload data 
    memory[0][0] = 1;
    memory[0][1] = 2;

    Instruction data = {0};
    mem_read(0, &data);


    // Check opcode and argument fields were read succesffully
    CHECK_EQUAL(1, data.opcode);
    CHECK_EQUAL(2, data.arg);
}


TEST(MemoryTests, WriteOPCodeAndData) 
{ 
    //int data[MEM_FIELDS] = {1, 15};
    Instruction data = {.opcode=1, .arg=15};
    int addr = 0;
    mem_write(addr, &data);

    Instruction data_read = {0};
    mem_read(addr, &data_read);

    CHECK_EQUAL(1, data_read.opcode);
    CHECK_EQUAL(15, data_read.arg);
}

TEST(MemoryTests, OutOfBoundsWrite) 
{ 
    //int data[MEM_FIELDS] = {1, 15};
    Instruction data = {.opcode=1, .arg=15};
    int addr = -1;
    mem_status_t err = mem_write(addr, &data);

    CHECK_EQUAL(MEM_ERR_OOB, err);

    addr = 1024; 
    err = mem_write(addr, &data);

    CHECK_EQUAL(MEM_ERR_OOB, err);
}

TEST(MemoryTests, OutofBoundsRead) 
{
    int addr = -1;
    Instruction data = {0};
    mem_status_t err = mem_read(-1, &data);

    CHECK_EQUAL(MEM_ERR_OOB, err);

    addr = 1024;
    err = mem_read(addr, &data);

    CHECK_EQUAL(MEM_ERR_OOB, err);
}

TEST(MemoryTests, NullPointerArgRead) 
{
    Instruction* data = NULLPTR; 
    int addr = 0;
    mem_status_t err = mem_read(addr, data);

    CHECK_EQUAL(MEM_ERR_NULL, err);
}


TEST(MemoryTests, NullPointerArgWrite)
{
    //int data[MEM_FIELDS] = {1, 15};
    Instruction* data = NULLPTR; 
    int addr = 0;
    mem_status_t err = mem_write(addr, data);

    CHECK_EQUAL(MEM_ERR_NULL, err);
}


TEST_GROUP(DiskTests) { 
    void setup() { 
        // Clear memory & set to sentinel value 0 just for unit tests
        memset(memory, 0, sizeof(memory));
    }
    
    void teardown() { 

    }

};



TEST(DiskTests, InstructionNoArgsExit) { 

    // Example program
    // exit 

    char test_instruction[] = "exit"; 
    
    int expected_opcode = 0;
    int expected_arg    = 0; // Sentinel value
    int addr = 4;


    Instruction translated_instruction = {0};
    translate(test_instruction, &translated_instruction);
    mem_write(addr, &translated_instruction);

    Instruction data = {0};
    mem_read(addr, &data); 
    
    CHECK_EQUAL(expected_opcode, data.opcode);
    CHECK_EQUAL(expected_arg,    data.arg);  

}

TEST(DiskTests, LoadConst) { 

    // Example program
    // load_const 50

    char test_instruction[] = "\tload_const 50\t\r\n"; 
    
    int expected_opcode = LOAD_CONST;
    int expected_arg    = 50; // Sentinel value
    int addr = 4;

    Instruction translated_instruction = {0};

    translate(test_instruction, &translated_instruction);
    mem_write(addr, &translated_instruction);

    Instruction data = {0};
    mem_read(addr, &data); 
    
    CHECK_EQUAL(expected_opcode, data.opcode);
    CHECK_EQUAL(expected_arg,    data.arg);  

}

TEST(DiskTests, ProgramWithEmptyLines) { 

    const char fname[] = "../programs/empty_lines.txt";
    int addr = 4;

    load_program(fname, addr);

    Instruction instr1 = {0};
    Instruction instr2 = {0};

    mem_read(addr, &instr1);
    mem_read(addr+1, &instr2);

    CHECK_EQUAL(1, instr1.opcode); // load_const 250
    CHECK_EQUAL(250, instr1.arg);
    CHECK_EQUAL(0, instr2.opcode); // exit
    CHECK_EQUAL(0, instr2.arg);
}

TEST(DiskTests, ProgramWithInlineComments) { 

    const char fname[] = "../programs/inline_comments.txt";
    int addr = 4;

    load_program(fname, addr);

    Instruction instr1 = {0};
    Instruction instr2 = {0};

    mem_read(addr, &instr1);
    mem_read(addr+1, &instr2);

    CHECK_EQUAL(1, instr1.opcode); // load_const 250
    CHECK_EQUAL(250, instr1.arg);
    CHECK_EQUAL(0, instr2.opcode); // exit
    CHECK_EQUAL(0, instr2.arg);
}

TEST(DiskTests, ProgramLoadBadArguments) { 
    
    const char fname[] = "../programs/bad_arguments.txt";
    int addr = 4;


    load_status_t err = load_program(fname,addr);

    CHECK_EQUAL((int)LOAD_ERR, err);
}

TEST(DiskTests, ProgramUnexpectedArgs) {

    const char fname[] = "../programs/unexpected_arguments.txt";
    int addr = 4;

    load_status_t err = load_program(fname,addr);

    CHECK_EQUAL((int)LOAD_ERR, err);
}

TEST(DiskTests, ProgramUnknownInstruction) {

    const char fname[] = "../programs/unknown_instruction.txt";
    int addr = 4;

    load_status_t err = load_program(fname,addr);

    CHECK_EQUAL((int)LOAD_ERR, err);
}


// Testing if the sample programs given will load into memory correctly 
TEST(DiskTests, LoadProgramAdd) { 
    const char fname[] = "../programs/program_add.txt";
    int addr = 4;

    load_status_t err = load_program(fname,addr);

    /*
    for (int i = 0; i < 20; i++) { 
            Instruction instr = {0};
            mem_read(i, &instr); 
            printf("opcode : %u, arg: %d\n", instr.opcode, instr.arg); 
    }
    */

    CHECK_EQUAL((int)LOAD_OK, err);

}

TEST(DiskTests, LoadProgramIf) { 
    const char fname[] = "../programs/program_if.txt";
    int addr = 4;

    load_status_t err = load_program(fname,addr);

    /*
    for (int i = 0; i < 20; i++) { 
            Instruction instr = {0};
            mem_read(i, &instr); 
            printf("opcode : %u, arg: %d\n", instr.opcode, instr.arg); 
    }
    */
    

    CHECK_EQUAL((int)LOAD_OK, err);
}


TEST_GROUP(CpuTests) { 

    void setup() {

        //Init stuff
        memset(memory, 0, sizeof(memory));
        cpu_regs = {0};


    }

    void teardown() { 


    }
};

TEST(CpuTests, FetchInstructionFromMemory) { 

    const int NUM_INSTRUCTIONS = 9;
    const int addr = 4;

    // contents of program_add.txt 
    int program[NUM_INSTRUCTIONS][MEM_FIELDS] = 
    { [0] = {1, 18}, // load_const 18
        [1] = {3, 0},  // move_to_mar
        [2] = {1, 25}, // load_const 25
        [3] = {4, 0},  // move_to_mbr
        [4] = {1, 5},  // load_const 5
        [5] = {8, 0},  // add 
        [6] = {4, 0},  // move_to_mbr 
        [7] = {7, 0},  // write_at_addr
        [8] = {0, 0},  // exit
    };

    // Preload program into memory before tests
    for (int i = addr, j = 0; j < NUM_INSTRUCTIONS && i < MEM_SIZE; i++, j++) { 
        memory[i][OPCODE_IDX] = program[j][OPCODE_IDX];
        memory[i][ARG_IDX]    = program[j][ARG_IDX];
    }

    // Check that the contents of IR0 and IR1 match load_const 5 (1,5) instruction 
    int expected_opcode = 1;
    int expected_arg    = 5;

    fetch_instruction(addr+4);


    CHECK_EQUAL(expected_opcode, cpu_regs.IR0);
    CHECK_EQUAL(expected_arg, cpu_regs.IR1);
} 

TEST_GROUP(InstructionTests) { 

    void setup() {

        //Init stuff
        memset(memory, 0, sizeof(memory));
        cpu_regs = {0};

    }

    void teardown() { 


    }
};

TEST(InstructionTests, ExitProgram) { 

    // Load the exit instruction into cpu registers
    cpu_regs.IR1 = 0;
    cpu_regs.IR0 = 0; 

    execute_instruction();

    CHECK_EQUAL(false, running);
}

TEST(InstructionTests, LoadConstant) { 

    // Preload load_const 
    cpu_regs.IR0 = 1;
    cpu_regs.IR1 = 100;
    
    execute_instruction();

    CHECK_EQUAL(cpu_regs.IR1, cpu_regs.AC);
}

TEST(InstructionTests, MoveFromMBR) { 

    // Preload move_from_mbr 
    cpu_regs.IR0 = 2;
    cpu_regs.IR1 = 0;
    cpu_regs.MBR = 1000;
    
    execute_instruction();

    // AC = MBR = 1000
    CHECK_EQUAL(cpu_regs.MBR, cpu_regs.AC);
}

TEST(InstructionTests, MoveFromMAR) { 

    // Preload move_from_mar
    cpu_regs.IR0 = 3;
    cpu_regs.IR1 = 0;
    cpu_regs.MBR = 20;
    
    execute_instruction();

    // AC = MAR = 20
    CHECK_EQUAL(cpu_regs.MAR, cpu_regs.AC);
}

TEST(InstructionTests, MoveToMBR) { 

    // Preload move_to_mbr
    cpu_regs.IR0 = 4;
    cpu_regs.IR1 = 0;
    cpu_regs.AC  = 155;
    
    execute_instruction();

    // MBR <- AC = 155
    CHECK_EQUAL(cpu_regs.AC, cpu_regs.MBR);
}

TEST(InstructionTests, MoveToMAR) { 

    // Preload move_to_mar
    cpu_regs.IR0 = 5;
    cpu_regs.IR1 = 0;
    cpu_regs.AC  = 300;
    
    execute_instruction();

    // MAR <- AC = 300
    CHECK_EQUAL(cpu_regs.AC, cpu_regs.MAR);
}

TEST(InstructionTests, LoadAtAddr) { 

    // Preload load_at_addr
    cpu_regs.IR0  = 6;
    cpu_regs.IR1  = 0;
    cpu_regs.MAR  = 300;

    memory[300][1] = 1500;
    
    execute_instruction();

    // MBR <- MEM[300] = 1500
    CHECK_EQUAL(memory[300][1], cpu_regs.MBR);
}

TEST(InstructionTests, WriteAtAddr) { 

    // Preload write_at_addr
    cpu_regs.IR0  = 7;
    cpu_regs.IR1  = 0;
    cpu_regs.MAR  = 1023;
    cpu_regs.MBR  = 1500;
    
    execute_instruction();

    // MBR -> MEM[300] = 1500
    CHECK_EQUAL(cpu_regs.MBR, memory[1023][1]);
}

TEST(InstructionTests, Add) { 

    // Preload add
    cpu_regs.IR0  = 8;
    cpu_regs.IR1  = 0;
    cpu_regs.MBR  = 2;
    cpu_regs.AC   = 2;
    
    execute_instruction();

    // AC+MBR = 4  2+2 
    CHECK_EQUAL(4, cpu_regs.AC);
}

TEST(InstructionTests, Multiply) { 

    // Preload multiply
    cpu_regs.IR0  = 9;
    cpu_regs.IR1  = 0;
    cpu_regs.MBR  = 4;
    cpu_regs.AC   = 4;
    
    execute_instruction();

    // AC*MBR = 16  4*4 = 16
    CHECK_EQUAL(16, cpu_regs.AC);
}

TEST(InstructionTests, AndFalse) { 

    // Preload and
    cpu_regs.IR0  = 10;
    cpu_regs.IR1  = 0;
    cpu_regs.MBR  = 1;
    cpu_regs.AC   = 0;
    
    execute_instruction();

    // AC*MBR =  0 1 && 0 = 0
    CHECK_EQUAL(false, cpu_regs.AC);
}

TEST(InstructionTests, AndTrue) { 

    // Preload and
    cpu_regs.IR0  = 10;
    cpu_regs.IR1  = 0;
    cpu_regs.MBR  = 12;
    cpu_regs.AC   = 1;
    
    execute_instruction();

    // AC*MBR =  0 12 && 1 = 0 
    // This pasts as long as AC and MBR are nonzero
    CHECK_EQUAL(true, cpu_regs.AC);
}

TEST(InstructionTests, OrFalse) { 

    // Preload move_to_mbr
    cpu_regs.IR0  = 11;
    cpu_regs.IR1  = 0;
    cpu_regs.MBR  = 0;
    cpu_regs.AC   = 0;
    
    execute_instruction();
    
    CHECK_EQUAL(false, cpu_regs.AC);
}

TEST(InstructionTests, OrTrue) { 

    // Preload move_to_mbr
    cpu_regs.IR0  = 11;
    cpu_regs.IR1  = 0;
    cpu_regs.MBR  = 0;
    cpu_regs.AC   = 1;
    
    execute_instruction();

    CHECK_EQUAL(true, cpu_regs.AC);
}

TEST(InstructionTests, IfGoValid) { 

    // Preload move_to_mbr
    cpu_regs.IR0  = 12;
    cpu_regs.IR1  = 8; 
    cpu_regs.AC   = 1;
    cpu_regs.PC   = 6;
    cpu_regs.Base = 4;
    
    execute_instruction();

    CHECK_EQUAL((cpu_regs.IR1-1), cpu_regs.PC);
}

