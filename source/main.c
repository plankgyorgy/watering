#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>     // For POSIX exit statuses
#include <string.h>

#include "main.h"

int main(int argc, char **argv)
{
    int returnCode = EXIT_SUCCESS;

    if (!ProcessBlockingArgs(argc, argv, &returnCode))
    {

    }
    
    return returnCode;
}

/*
* Processes command line arguments that block the start of the program
*
* argc: count of command line arguments to process
* argv: command line arguments (after processing, will point the address as before processing)
* returnCode: exit status (only changed if found and processed a blocking argument)
*
* Returns: true if found (means it has been processed and the program must stop)
*/
bool ProcessBlockingArgs(int argc, char **argv, int *returnCode)
{
    bool gotStoppingArg = false;
    char **originalArgv = argv;

    while(--argc && !gotStoppingArg)
    {        
        ++argv;

        if (strcmp(*argv, "--version") == 0)
        {
            printf("Watering 0.1\n");
            gotStoppingArg = true;
            *returnCode = EXIT_SUCCESS;
        }
        else if ((strcmp(*argv, "--help") == 0)
                || (strcmp(*argv, "-h") == 0)
                || (strcmp(*argv, "-?") == 0))
        {
            printf("usage: Watering [--version | --help | -h | -?]\n");
            printf("Parameters:\n");
            printf("\t--version: Writes the version of program to the standard output\n");
            printf("\t-h,\n");
            printf("\t-?,\n");
            printf("\t--help: Writes this help to the standard output\n");
            gotStoppingArg = true;
            *returnCode = EXIT_SUCCESS;
        }     
        else
        {
            printf("Unknown command line parameter: %s\n", *argv);
            gotStoppingArg = true;
            *returnCode = EXIT_FAILURE;
        }
    }

    argv = originalArgv;
    return gotStoppingArg;
}

