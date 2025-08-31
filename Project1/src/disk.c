
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include "../include/disk.h"
#include "../include/memory.h"

static const int BUF_SIZE = 256;

static const InstructionInfo InstrTable[] =
    {
        {"exit", EXIT, 0},
        {"load_const", LOAD_CONST, 1},
        {"move_from_mbr", MOV_FROM_MBR, 0},
        {"move_from_mar", MOV_FROM_MAR, 0},
        {"move_to_mbr", MOV_TO_MBR, 0},
        {"move_to_mar", MOV_TO_MAR, 0},
        {"load_at_addr", LOAD_AT_ADDR, 0},
        {"write_at_addr", WRITE_AT_ADDR, 0},
        {"add", ADD, 0},
        {"multiply", MULT, 0},
        {"and", AND, 0},
        {"or", OR, 0},
        {"ifgo", IFGO, 1},
        {"sleep", SLEEP, 0},
};

// Opens program .txt file, translates instructions line by line and stores it in OS memory
void load_program(const char *fname, int addr)
{

    // Open program file
    FILE *fptr = fopen(fname, "r");

    char line[BUF_SIZE];

    // Check if it's a valid file
    if (!fptr)
    {
        fprintf(stderr, "File was not found: %s\n", fname);
        exit(EXIT_FAILURE);
    }

    // While there are still instructions in the file
    while (fgets(line, BUF_SIZE, fptr) && addr < MEM_SIZE)
    {

        // Strip any text after first instance of a comment
        char *comment = strstr(line, "//");
        if (comment)
        {
            *comment = '\0';
        }


        // strip any whitespace from line
        line[strcspn(line, "\r\n")] = 0;

        // If line is empty after processing then ignore
        if (line[0] == '\0')
        {
            continue;
        }

        Instruction instr = translate(line);

        mem_write(addr, &instr);

        addr++;
    }

    fclose(fptr);
}

// Translates a single instruction into (int opcode, int arg)
Instruction translate(char *instruction)
{

    // Tokenize opcode and argument
    char *opcode = strtok(instruction, " \t");
    char *arg = strtok(NULL, " \t");

    const InstructionInfo *instrPtr = 0;

    // Look up opcode in the Instruction LUT
    for (int i = 0; i < sizeof(InstrTable) / sizeof(InstrTable[0]); i++)
    {

        if (strcmp(opcode, InstrTable[i].mnemonic) == 0)
        {
            instrPtr = &InstrTable[i];
            break;
        }
    }

    // If instruction is not found exit print error and exit program gracefully
    // Might not be the optimal way to do this, in future probably parse the program then keep log of all errors in program
    if (!instrPtr)
    {
        fprintf(stderr, "Error: Unknown instruction %s\n", opcode);
        exit(EXIT_FAILURE);
    }

    // For now let's naively assume the number of args is correct
    int opcode_num = instrPtr->opcode;
    int arg_num;

    if (instrPtr->num_args > 0)
    {
        // Again need a better way to log errors before just exiting
        if(!string_is_number(arg)) 
        {
          fprintf(stderr, "Error: Argument %s is not numeric\n", arg);    
          exit(EXIT_FAILURE);
        }   

        arg_num = atoi(arg); // Convert argument into integer
    }
    else
    {

        // If there more than 0 arguments detected then return an error
        if(arg) { 
            fprintf(stderr, "More than 0 arguments detected");
            exit(EXIT_FAILURE);
        }

        arg_num = 0; // Default value for arg field
    }

    Instruction result = {.opcode = opcode_num, .arg = arg_num};
    return result;
}

static bool string_is_number(const char* str) { 

    if (str[0] == '\0' ) return false; 

    if (*str == '+' || *str == '-') str++; //check for + or - signs

    
    while(*str) { 
        if(!isdigit((unsigned char)*str)) return false;
        str++;
    } 
    
    return true;

}