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


    Instruction translated_instruction = translate(test_instruction);
    mem_write(addr, &translated_instruction);

    Instruction data = {0};
    mem_read(addr, &data); 
    
    CHECK_EQUAL(expected_opcode, data.opcode);
    CHECK_EQUAL(expected_arg,    data.arg);  

}

TEST(DiskTests, LoadConst) { 

    // Example program
    // load_const 50

    char test_instruction[] = "load_const 50\r\n"; 
    
    int expected_opcode = LOAD_CONST;
    int expected_arg    = 50; // Sentinel value
    int addr = 4;


    Instruction translated_instruction = translate(test_instruction);
    mem_write(addr, &translated_instruction);

    Instruction data = {0};
    mem_read(addr, &data); 
    
    CHECK_EQUAL(expected_opcode, data.opcode);
    CHECK_EQUAL(expected_arg,    data.arg);  

}

