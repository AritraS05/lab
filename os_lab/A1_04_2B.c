/***********************************************************************
 *
 * Name       : Aritra Sarkar, Anish Das, Dripta Patra
 * Roll No.   : 002311001048, 002311001009, 002311001006
 * Team No.   : 04
 * Group      : A1
 * Date       : 07-08-2025
 *
 * Assignment : 2(b)
 * Description: This program demonstrates Inter-Process Communication (IPC)
 *              using Named Pipes (FIFOs). It does the following:
 *
 *              1. A parent process creates a 1GB file named "original".
 *              2. The parent sends this file to the child via FIFO1.
 *              3. The child receives it and sends it back via FIFO2.
 *              4. The parent receives the returned file and compares it
 *                 using `cmp` or `diff`.
 *              5. It prints the time taken for this double transfer.
 *
 * Input      : No user input is needed. The file transfer is automated.
 * Output     : Confirmation of file match and time required for the operation.
 *
 * Compilation Command:
 *     gcc -o A1_04_2B A1_04_2B.c
 *
 * Execution Sequence:
 *     ./A1_04_2B
 *
 * Sample Commands Used:
 *     To create FIFO: mkfifo fifo1 fifo2
 *     To create 1GB file: dd if=/dev/zero of=1gb_file.bin bs=1M count=1024
 *     To compare files: cmp original received_back.dat
 *     To list files: ls -l original fifo1 fifo2
 *
 * Sample Output:
 *        Time taken (in seconds): 2.62
 *	 Running cmp...
 *	 original received differ: byte 1, line 1
 *	 Files differ
 *
 *	 Listing large file and FIFOs:
 *	 prw-rw-r-- 1y desktop _desktop          0 Aug  7 12:56 fifo1
 *	 prw-rw-r-- 1 desptop _ desktop          0 Aug  7 12:56 fifo2
 *	 -rw-rw-r-- 1 desktop _desktop  1073741824 Aug  7 12:54 original
 *	 -rw-rw-r-- 1 desktop _desktop 1073741824 Aug  7 12:56 parenttochild
 *	 -rw-rw-r-- 1 desktop _desktop 1073741824 Aug  7 12:56 received
 *
 ***********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/types.h>
#include <string.h>
#include <errno.h>

#define BUF_SIZE 8192

int main()
{
    // Create FIFOs
    if (mkfifo("fifo1", 0666) == -1 && errno != EEXIST)
    {
        perror("mkfifo fifo1");
        exit(EXIT_FAILURE);
    }
    if (mkfifo("fifo2", 0666) == -1 && errno != EEXIST)
    {
        perror("mkfifo fifo2");
        exit(EXIT_FAILURE);
    }
    struct timeval start, end;
    gettimeofday(&start, NULL); // Start timer

    pid_t pid = fork();
    if (pid < 0)
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    // child process
    // read from fifo1 and write to parenttochild, then write the content of that file to fifo2 for parent to read
    if (pid == 0)
    {
        int fd_in = open("fifo1", O_RDONLY);
        if (fd_in < 0)
        {
            perror("child open fifo1");
            exit(EXIT_FAILURE);
        }

        int fd_tmp = open("parenttochild", O_WRONLY | O_CREAT | O_TRUNC, 0666);
        if (fd_tmp < 0)
        {
            perror("parenttochild open");
            exit(EXIT_FAILURE);
        }

        char buf[BUF_SIZE];
        ssize_t n;
        while ((n = read(fd_in, buf, BUF_SIZE)) > 0)
        {
            if (write(fd_tmp, buf, n) != n)
            {
                perror("child write temp");
                exit(EXIT_FAILURE);
            }
        }
        close(fd_in);
        close(fd_tmp);

        fd_tmp = open("parenttochild", O_RDONLY);
        int fd_out = open("fifo2", O_WRONLY);
        if (fd_out < 0)
        {
            perror("parenttochild open fifo2");
            exit(EXIT_FAILURE);
        }

        while ((n = read(fd_tmp, buf, BUF_SIZE)) > 0)
        {
            if (write(fd_out, buf, n) != n)
            {
                perror("parenttochild write fifo2");
                exit(EXIT_FAILURE);
            }
        }
        close(fd_tmp);
        close(fd_out);
    }
    // Parent Process
    // read from original file and then write to fifo1 for child to read, then read from fifo2
    else
    {
        int fd_orig = open("1gb_file.bin", O_RDONLY);
        if (fd_orig < 0)
        {
            perror("parent open file");
            exit(EXIT_FAILURE);
        }
        int fd_fifo1 = open("fifo1", O_WRONLY);
        if (fd_fifo1 < 0)
            perror("parent open fifo1");

        char buf[BUF_SIZE];
        ssize_t n;
        while ((n = read(fd_orig, buf, BUF_SIZE)) > 0)
        {
            if (write(fd_fifo1, buf, n) != n)
            {
                perror("parent write fifo1");
                exit(EXIT_FAILURE);
            }
        }
        close(fd_orig);
        close(fd_fifo1);

        int fd_fifo2 = open("fifo2", O_RDONLY);
        int fd_recv = open("received", O_WRONLY | O_CREAT | O_TRUNC, 0666);
        if (fd_recv < 0)
        {
            perror("parent open received");
            exit(EXIT_FAILURE);
        }

        while ((n = read(fd_fifo2, buf, BUF_SIZE)) > 0)
        {
            if (write(fd_recv, buf, n) != n)
            {
                perror("parent write received");
                exit(EXIT_FAILURE);
            }
        }
        close(fd_fifo2);
        close(fd_recv);

        gettimeofday(&end, NULL);

        double elapsed = (end.tv_sec - start.tv_sec) +
                         (end.tv_usec - start.tv_usec) / 1e6;

        printf("Time taken (in seconds): %.2f\n", elapsed);
        printf("Running cmp...\n");
        system("cmp 1gb_file.bin received && echo 'Files are identical' || echo 'Files differ'");
        printf("\nListing large file and FIFOs:\n");
        system("ls -l original received parenttochild fifo1 fifo2");
    }

    return 0;
}

//            (write)                 (read)
// Parent ----------------> fifo1 ----------------> Child

// Child ----------------> fifo2 ----------------> Parent
//            (write)                 (read)
