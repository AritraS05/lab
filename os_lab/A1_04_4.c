/**************************************************************************************************
* Name       : Aritra Sarkar, Anish Das, Dripta Patra
* Roll No.   : 002311001048, 002311001009, 002311001006
* Team No.   : 04
* Group      : A1
* Date       : 21-08-2025
*
*Assignment Details:
*The objective of this programming assignment is to use mmap() call and
*observe page-fault using the ‘sar’ command.
*A big file (about 8GB) should be created using the ‘fallocate’ command.
*This big file should be written with a single byte value (say X) at a specific
*offset (say F). Both the values and the offset should be generated using a
*random function. Please do remember this random function should
*generate a quantity anywhere between 0 and 8G for the value of F and
*between 0-255 for the value of X.
*The above big file should also be mapped in the virtual address space
*using mmap() call. Once it is mapped, the data should be read from the
*same specific offset (F). Now, if the data read is X`; then verify that X and
*X` are the same. In case of verification failure, an error message is to be
*printed and also the program should terminate. Note that, the offset value F
*can be anywhere between 0 and 8G and you should display the offset as
*hex number format.
*This sequence of writing and reading data to/from a specific offset and also
*verification should be put in a while loop to go forever.
*In another terminal execute the command ‘sar –B 1’ to observe for the
*page fault. This command should be started before the above program is
*put under execution. So, one can observe that the page faults are
*increasing, once the above program starts executing.
*The output of the program and the ‘sar’ command should be pasted as a
*comment at the beginning of the program file as indicated by the
*guidelines.
*
*Input Description:
*The name of the file to be transferred is entered as a command line input for the execution of the cmd
*
*Output Description:
*The method prints the value of the offset of the buffer and also the value read from the same offset 
* The method also prints whether the value written and read are the same or not
*
*command for creating a 8GB file: fallocate -l 8G sample.txt
*
* compilation command : gcc A1_04_4.c
*
* Execution command : ./a.out sample.txt
*sar -B 1
*Linux 5.15.0-139-generic (adminpc-HP-Pro-Tower-280-G9-PCI-Desktop-PC) 	21/08/25 	_x86_64_	(12 CPU)
*
*12:13:48 PM IST  pgpgin/s pgpgout/s   fault/s  majflt/s  pgfree/s pgscank/s pgscand/s pgsteal/s    %vmeff
*12:13:49 PM IST      0.00      8.00     37.00      0.00   5933.00      0.00      0.00      0.00      0.00
*12:13:50 PM IST      0.00      0.00     13.00      0.00    175.00      0.00      0.00      0.00      0.00
*12:13:51 PM IST      0.00      0.00     18.00      0.00    349.00      0.00      0.00      0.00      0.00
*12:13:52 PM IST      0.00     52.00     30.00      1.00    146.00      0.00      0.00      0.00      0.00
*12:13:53 PM IST      0.00     40.00    199.00      0.00   1178.00      0.00      0.00      0.00      0.00
*12:13:54 PM IST      0.00      0.00      8.00      0.00    179.00      0.00      0.00      0.00      0.00
*12:13:55 PM IST      0.00      8.00      0.00      0.00   2880.00      0.00      0.00      0.00      0.00
*12:13:56 PM IST      0.00      0.00      2.00      0.00   1705.00      0.00      0.00      0.00      0.00
*12:13:57 PM IST      0.00    444.00    171.00      0.00    482.00      0.00      0.00      0.00      0.00
*12:13:58 PM IST   4848.00      0.00   2292.00    745.00   1368.00      0.00      0.00      0.00      0.00
*12:13:59 PM IST  32668.00    148.00  76304.00  27790.00   1183.00      0.00      0.00      0.00      0.00
*12:14:00 PM IST  32180.00     72.00  75329.00  27596.00    908.00      0.00      0.00      0.00      0.00
*12:14:01 PM IST  31064.00     80.00  74499.00  27050.00    841.00      0.00      0.00      0.00      0.00
*12:14:02 PM IST  29352.00     80.00  68270.00  24838.00    879.00      0.00      0.00      0.00      0.00
*12:14:03 PM IST  28992.00   9320.00  68261.00  24745.00   1071.00      0.00      0.00      0.00      0.00
*12:14:04 PM IST  27840.00    320.00  66714.00  23977.00   1040.00      0.00      0.00      0.00      0.00
*12:14:05 PM IST  26144.00     96.00  63252.00  22775.00   1199.00      0.00      0.00      0.00      0.00
*12:14:06 PM IST  25228.00    256.00  59057.00  21242.00   1062.00      0.00      0.00      0.00      0.00
*12:14:07 PM IST  17468.00     88.00  42374.00  15279.00   2037.00      0.00      0.00      0.00      0.00
*^C
*
*Average:     12180.19  56810.67  28455.95  10287.52   1792.05      0.00      0.00      0.00      0.00






*********************************************************************************************************************/

#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <time.h>
#include <sys/types.h>
#include <limits.h>
#include <unistd.h>

char *mapBuffer; // The pointer returned by mmap() is stored as the buffer address.
void printLines();
int writeInteger(unsigned long pos, unsigned long num)
{
        printf("The written value is : %-10lu\n", num);
        sprintf(mapBuffer + pos, "%lu", num);
}
int readInteger(unsigned long pos);
unsigned long randomNumberGen()
{
    unsigned long minRange = 0;
    unsigned long maxRange = INT_MAX;
    unsigned long randNum = minRange + (rand() % (maxRange - minRange + 1));
    return randNum;
}
int main(int argc, char **argv)
{
    if (argc != 2)
    {
        printf("Please give necesary arguments...\n");
        printf("Usage: ./program <filename>\n");
        exit(0);
    }
    // Opening the user  file
    int fd = open(argv[1], O_RDWR, S_IRUSR | S_IWUSR);
    // The information of the file is stored in this structure
    struct stat fileInfo;
    // fetching the information of the file in the fileInfo variable
    if (fstat(fd, &fileInfo) == -1)
    {
        perror(" ERROR occured in the file size!");
        exit(1);
    }

    if ((mapBuffer = (char *)mmap(NULL, fileInfo.st_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0)) == MAP_FAILED)
    {
        perror("Some ERROR occured while mapping the file!");
        exit(2);
    }
    srand(time(NULL));
    unsigned long pos, writeVal, readVal;
    while (1)
    {
        writeVal = randomNumberGen();
        pos = randomNumberGen(); 
        writeInteger(pos, writeVal); 
        readVal = readInteger(pos); 
        
        if (writeVal == readVal)
        {
            printf("Both the value are equal!\n");
            printLines();
        }
        else
        {
            printf("Values are not equal!\n");
            printLines();
        }
    }
    return 0;
}



void printLines()
{
    printf(".............................printing...........................\n");
}
int readInteger(unsigned long pos)
{
    unsigned long val;
    sscanf(mapBuffer + pos, "%lu", &val);
    printf("The Read value is : %-10lu\n", val);
    return val;
}
