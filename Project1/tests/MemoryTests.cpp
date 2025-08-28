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

    int* data = mem_read(0);

    // Check opcode and argument fields were read succesffully
    CHECK_EQUAL(1, data[OPCODE_IDX]);
    CHECK_EQUAL(2, data[ARG_IDX]);
}


TEST(MemoryTests, WriteOPCodeAndData) 
{ 
    int data[MEM_FIELDS] = {1, 15};
    int addr = 0;
    mem_write(addr, data);

    int* data_read = mem_read(addr);

    CHECK_EQUAL(1, data_read[OPCODE_IDX]);
    CHECK_EQUAL(15, data_read[ARG_IDX]);
}

TEST_GROUP(DiskTests) { 
    void setup() { 
        // Clear memory & set to sentinel value -1 just for unit tests
        memset(memory, -1, sizeof(memory));
    }
    
    void teardown() { 

    }

};


TEST(DiskTests, InstructionNoArgs) { 

    // Example program 
    // exit 
    const char* test_instruction = "exit"; 

    int* translated_instruction = translate(test_instruction);
    
    int expected_opcode = 0;
    int expected_arg    = -1; // Sentinel value

    int addr = 4;
    mem_write(addr, translated_instruction);
    int* data_read = mem_read(addr);

    CHECK_EQUAL(expected_opcode, data_read[OPCODE_IDX]);
    CHECK_EQUAL(expected_arg,    data_read[ARG_IDX]);  

}