/***************************************************************
 * ASSIGNMENT : 1B
 * TEAM NO    : 04
 *
 * NAME       : Aritra Sarkar   ROLL NO : 002311001048
 * NAME       : Anish Das       ROLL NO : 002311001009
 * NAME       : Dripta Patra    ROLL NO : 002311001006
 *
 * FILE NAME  : A1_04_1B.c
 *
 * DESCRIPTION :
 * This program demonstrates the use of UNIX environment variable
 * system calls `getenv()` and `setenv()`.
 *
 * It displays the values of predefined environment variables:
 *   - USER, HOME, HOST, ARCH, DISPLAY, PRINTER, PATH
 *
 * Then, it sets two new environment variables using command line
 * arguments and displays their values.
 *
 * INPUT  : Command line arguments:
 *          <VAR1_NAME> <VAR1_VALUE> <VAR2_NAME> <VAR2_VALUE>
 *
 * OUTPUT : Prints existing environment variables and the newly
 *          set ones.
 *
 * COMPILATION (Warning free):
 *     gcc -Wall -o A1_04_1B A1_04_1B.c
 *
 * EXECUTION :
 *     ./A1_04_1B MY_VAR1 HelloWorld MY_VAR2 OpenAI_2025
 *
 ***************************************************************/

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    // Check for correct number of arguments
    if (argc != 5)
    {
        fprintf(stderr, "Usage: %s <VAR1_NAME> <VAR1_VALUE> <VAR2_NAME> <VAR2_VALUE>\n", argv[0]);
        return EXIT_FAILURE;
    }

    // List of predefined environment variables
    const char *vars[] = {
        "USER", "HOME", "HOST", "ARCH", "DISPLAY", "PRINTER", "PATH"};

    int num_vars = sizeof(vars) / sizeof(vars[0]);

    printf("----- Predefined Environment Variables -----\n\n");

    for (int i = 0; i < num_vars; ++i)
    {
        char *value = getenv(vars[i]);

        if (value != NULL)
        {
            printf("%s = %s\n", vars[i], value);
        }
        else
        {
            printf("%s is not defined in the environment.\n", vars[i]);
        }
    }

    printf("\n----- Setting New Environment Variables -----\n\n");

    // Set the first environment variable
    if (setenv(argv[1], argv[2], 1) != 0)
    {
        perror("Error setting first environment variable");
    }

    // Set the second environment variable
    if (setenv(argv[3], argv[4], 1) != 0)
    {
        perror("Error setting second environment variable");
    }

    // Retrieve and display the new environment variable values
    char *new_val1 = getenv(argv[1]);
    char *new_val2 = getenv(argv[3]);

    printf("%s = %s\n", argv[1], new_val1 ? new_val1 : "Not Found");
    printf("%s = %s\n", argv[3], new_val2 ? new_val2 : "Not Found");

    return EXIT_SUCCESS;
}

/******************************************************************************************************
 *
 *[be2348@localhost assign1]$ gcc -o A1_04_1B A1_04_1B.c
 *[be2348@localhost assign1]$ ./A1_04_1B x 20 y 50
 *----- Predefined Environment Variables -----
 *
 *USER = be2348
 *HOME = /home/usr/student/ug/yr23/be2348
 *HOST is not defined in the environment.
 *ARCH is not defined in the environment.
 *DISPLAY is not defined in the environment.
 *PRINTER is not defined in the environment.
 *PATH = /sr/lib64/qt-3.3/bin:/usr/local/bin:/usr/bin:/usr/local/sbin:/usr/sbin:/home/usr/student/ug/yr23/8be2348/.local/bin:/home/usr/student/ug/yr23/be2348/bin
 *
 *----- Setting New Environment Variables -----
 *
 *x = 20
 *y = 50
 ******************************************************************************************************/
