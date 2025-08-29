
#include <stdio.h>
#include <string.h>
#include "../include/disk.h"
#include "../include/memory.h"


static const InstructionInfo InstrTable[] = 
{
    {"exit",          EXIT,          0},
    {"load_const",    LOAD_CONST,    1},
    {"move_from_mbr", MOV_FROM_MBR,  0},
    {"move_from_mar", MOV_FROM_MAR,  0},
    {"move_to_mbr",   MOV_TO_MBR,    0},
    {"move_to_mar",   MOV_TO_MAR,    0},
    {"load_at_addr",  LOAD_AT_ADDR,  0},
    {"write_at_addr", WRITE_AT_ADDR, 0},
    {"add",           ADD,           0},
    {"multiply",      MULT,          0},
    {"and",           AND,           0},
    {"or",            OR,            0}, 
    {"ifgo",          IFGO,          1},
    {"sleep",         SLEEP,         0},
};



void load_program(const char* fname, const int addr) { 


    // While there are still instructions in the file
    while(1) {



    // write the instruction to memory 
    // update the current address 
    } 


    // close file 
}



Instruction translate(char* instruction) { 

    // strip any whitespace from line
    instruction[strcspn(instruction, "\r\n")] = 0; 

    // Tokenize opcode and argument
    char* opcode = strtok(instruction, " \t");
    char* arg    = strtok(NULL, " \t");

    // Look up opcode in the Instruction LUT
    for(int i = 0; i < sizeof(InstrTable)/sizeof(InstrTable[0]); i++) { 
        
    }


    // Check number of arguments associated with instruction
    // if number of arguments is invalid or there are bad arguments then return exit code  and exit program


    // Else: 
    // return the instruction with (opcode, arg)
    // If the instruction does not have an argument then arg = 0


    // return result;

}

