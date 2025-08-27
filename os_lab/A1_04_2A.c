/***********************************************************************
*
* Name       : Aritra Sarkar, Anish Das, Dripta Patra
* Roll No.   : 002311001048, 002311001009, 002311001006
* Team No.   : 04
* Group      : A1
* Date       : 07-08-2025
*
* Assignment : 2(a)
* Description: This program demonstrates basic signal handling using the
*              `signal()` system call. It catches the SIGINT signal (Ctrl+C)
*              and displays the message "Ha Ha, Not Stopping".
*
* Input      : No command-line arguments are needed.
* Output     : Displays a custom message when SIGINT is received.
*
* Compilation Command:
*     gcc -o A1_04_2A A1_04_2A.c
*
* Execution Sequence:
*     ./A1_04_2A
*     (Press Ctrl+C to generate SIGINT)
*
* Sample Output:
*     desktop@adminpc-HP-Pro-Tower-280-G9-PCI-Desktop-PC:~/Desktop$ ./A1_04_2A
*	Running... Press Ctrl+C to test SIGINT
* 	Running... Press Ctrl+C to test SIGINT
*	^CHa Ha, Not Stopping
*
***********************************************************************/


#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

// Signal handler function
void handle_sigint(int sig) {
    printf("Ha Ha, Not Stopping\n");
}

int main() {
    // Register signal handler
    if (signal(SIGINT, handle_sigint) == SIG_ERR) {
        perror("signal");
        exit(EXIT_FAILURE);
    }

    // Infinite loop to keep the program running
    while (1) {
        printf("Running... Press Ctrl+C to test SIGINT\n");
        sleep(2);
    }

    return 0;
}
