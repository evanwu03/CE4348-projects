
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include "../include/disk.h"
#include "../include/memory.h"

static const int BUF_SIZE = 256;

static const InstructionInfo InstrTable[NUM_INSTRUCTIONS] =
    {
        [EXIT]          = {"exit", EXIT, 0},
        [LOAD_CONST]    =  {"load_const", LOAD_CONST, 1},
        [MOV_FROM_MBR]  = {"move_from_mbr", MOV_FROM_MBR, 0},
        [MOV_FROM_MAR]  = {"move_from_mar", MOV_FROM_MAR, 0},
        [MOV_TO_MBR]    = {"move_to_mbr", MOV_TO_MBR, 0},
        [MOV_TO_MAR]    = {"move_to_mar", MOV_TO_MAR, 0},
        [LOAD_AT_ADDR]  = {"load_at_addr", LOAD_AT_ADDR, 0},
        [WRITE_AT_ADDR] = {"write_at_addr", WRITE_AT_ADDR, 0},
        [ADD]           = {"add", ADD, 0},
        [MULT]          = {"multiply", MULT, 0},
        [AND]           = {"and", AND, 0},
        [OR]            = {"or", OR, 0},
        [IFGO]          = {"ifgo", IFGO, 1},
        [SLEEP]         = {"sleep", SLEEP, 0},
};

// Opens program .txt file, translates instructions line by line and stores it in OS memory
load_status_t load_program(const char *fname, int addr)
{

    // Open program file
    FILE *fptr = fopen(fname, "r");

    char line[BUF_SIZE];
    int program_counter = addr; 

    // Check if it's a valid file
    if (!fptr)
    {
        fprintf(stderr, "File was not found: %s\n", fname);
        return LOAD_ERR; // Might be more expressive
    }

    // While there are still instructions in the file
    while (fgets(line, BUF_SIZE, fptr) && program_counter < MEM_SIZE)
    {

        // Strip any text after first instance of a comment
        char *comment = strstr(line, "//");
        if (comment) *comment = '\0';

        // strip any whitespace from line
        line[strcspn(line, "\r\n")] = 0;

        // If line is empty after processing then ignore
        if (line[0] == '\0') continue;
    
        Instruction instr = {0};
        translate_status_t err = translate(line, &instr);

        if (err != TR_OK)
        {
            // print other diagnostic info here probably
            return LOAD_ERR;
        }

        mem_write(program_counter, &instr);

        program_counter++;
    }

    fclose(fptr);
    return LOAD_OK;
}

// Translates a single instruction into (int opcode, int arg)
translate_status_t translate(char *instruction, Instruction *outInstr)
{

    // Tokenize opcode and argument
    char *opcode = strtok(instruction, " \t");
    char *arg = strtok(NULL, " \t");

    const InstructionInfo *instrPtr = 0;

    // Look up opcode in the Instruction LUT
    for (size_t i = 0, n = ARRAY_LEN(InstrTable); i < n; i++)
    {

        if (strcmp(opcode, InstrTable[i].mnemonic) == 0)
        {
            instrPtr = &InstrTable[i];
            break;
        }
    }

    // If instruction is not found exit print error and exit program gracefully
    // Might not be the optimal way to do this, in future probably parse the program then keep log of all errors in program
    // We should also check args of Ifgo is > 0
    if (!instrPtr)
    {
        fprintf(stderr, "Error: Unknown instruction %s\n", opcode);
        return TR_UNKNOWN_INSTR;
    }

    int opcode_num = instrPtr->opcode;
    int arg_num;

    if (instrPtr->num_args > 0)
    {
        // Again need a better way to log errors before just exiting
        if (!string_is_number(arg))
        {
            fprintf(stderr, "Error: Argument %s is not numeric\n", arg);
            return TR_ARG_NOT_NUMERIC;
        }

        arg_num = atoi(arg); // Convert argument into integer
    }
    else
    {

        // If there more than 0 arguments detected then return an error
        if (arg)
        {
            fprintf(stderr, "More than arguments than expected\n");
            return TR_UNEXPECTED_ARG;
        }

        arg_num = 0; // Default value for arg field
    }

    outInstr->opcode = opcode_num;
    outInstr->arg = arg_num;

    return TR_OK;
}

static bool string_is_number(const char *str)
{

    if (str[0] == '\0')
        return false;

    if (*str == '+' || *str == '-')
        str++; // check for + or - signs

    while (*str)
    {
        if (!isdigit((unsigned char)*str))
            return false;
        str++;
    }

    return true;
}