#include "CppUTest/TestHarness.h" 
#include "../include/memory.h"


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


TEST(MemoryTests, WriteDataToMemory) 
{   
    int data = 15; 
    int addr = 0;
    mem_write(addr, &data);
    int* data_frame = mem_read(addr);

    // Check if data was successfully written
    CHECK_EQUAL(data, data_frame[ARG_IDX]);
}

