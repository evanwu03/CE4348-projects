#include "CppUTest/TestHarness.h" 
#include "../include/memory.h"
#include "../include/disk.h"


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

    CHECK_EQUAL((int)LOAD_OK, err);

}

TEST(DiskTests, LoadProgramIf) { 
    const char fname[] = "../programs/program_if.txt";
    int addr = 4;

    load_status_t err = load_program(fname,addr);

    CHECK_EQUAL((int)LOAD_OK, err);
}