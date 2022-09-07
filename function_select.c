#include <stdio.h>
#include <string.h>
#include "header.h"
void function_select(stack_t **stack, unsigned int line_number, char *command)
{
    instruction_t function[] = {
        {"push", pall},
        {"push", push},
    };
    int l;
    if (command[0] == "#")
    {
        return;
    }
    for (l = 0; function[l].opcode != NULL; l++)
    {
        if (strcmp(function->opcode, command) == 0)
        {
            function[l].f(stack, line_number);
            return;
        }
    }
    fprintf(stderr, "L%u: unknown instruction %s\n", line_number, command);
    exit(EXIT_SUCCESS);
}
void find_file(char *path, stack_t **stack)
{
    FILE *fp;
    int bufferSize = 100;
    char buffer[bufferSize];
    char *command;
    int line = 1;

    if (!path)
    {
        fprintf(stderr, "Error: can't open file %s", path);
        exit(EXIT_FAILURE);
    }
    fp = fopen(path, "r");
    if (!fp)
    {
        fprintf(stderr, "Error: can't open file %s", path);
        exit(EXIT_FAILURE);
    }
    header.file = fp;
    while (fgets(buffer, bufferSize, fp) != -1)
    {
        header.buffer = buffer;
        command = strtok(buffer, " \n\t\r");
        if (command)
        {
            function_select(stack, line, command);
            line++;
        }
    }
    atexit(free_all);
    exit(EXIT_SUCCESS);
}
