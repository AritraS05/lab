###############################################################
#                        Assignment 1A                        #
#-------------------------------------------------------------#
# Team No. : 04                                               #
#                                                             #
# Name            : Aritra Sarkar      | Roll No. : 002311001048
# Name            : Anish Das          | Roll No. : 002311001009
# Name            : Dripta Patra       | Roll No. : 002311001006
#-------------------------------------------------------------#
# Topic      : Familiarity with User and System-level         #
#              Operating System Commands                      #
###############################################################


# 1) who :  It displays the information about all the users who have logged into the system
# currently
#
# who
#
# [be2348@localhost OS_lab]$ who
# (unknown) :0           2024-10-21 11:46 (:0)
# root     pts/0        2025-07-24 11:08 (172.16.5.159)
# be2361   pts/1        2025-07-24 12:05 (172.16.5.29)
# be2359   pts/3        2025-07-24 12:07 (172.16.5.29)
# be2316   pts/4        2025-07-24 12:13 (172.16.4.216)
# be2315   pts/6        2025-07-24 12:17 (172.16.4.209)
# be2353   pts/7        2025-07-24 12:10 (172.16.4.222)
# be2325   pts/8        2025-07-24 12:14 (172.16.4.211)
# be23L07  pts/9        2025-07-24 12:20 (172.16.5.16)
# be2348   pts/10       2025-07-24 12:22 (172.16.4.215)
# be2321   pts/12       2025-07-24 12:23 (172.16.4.204)
# be2320   pts/13       2025-07-24 12:24 (172.16.4.202)
# be2306   pts/14       2025-07-24 12:25 (172.16.4.203)
# be2312   pts/15       2025-07-24 12:35 (172.16.4.218)
# be2308   pts/16       2025-07-24 12:35 (172.16.4.207)
# be2309   pts/18       2025-07-24 12:39 (172.16.4.210)
# be2333   pts/19       2025-07-24 12:45 (172.16.4.214)
# be2338   pts/20       2025-07-24 12:45 (172.16.4.236)



# 2) whoami : It displays Current username, Terminal number, date and time at which userlogged into # the system
#
# whoami
#
# [be2348@localhost OS_lab]$ whoami
# be2348


# 3)pwd  : It displays current working directory
#
# pwd
#
# [be2348@localhost OS_lab]$ pwd
# /home/usr/student/ug/yr23/be2348/OS_lab
#



#4)date : It displays system date and time
#
# date
#
# [be2348@localhost OS_lab]$ date
# Thu Jul 24 12:56:02 IST 2025


#5)ls : It lists the files and directories stored in the current directory. To list the files in a
# directory use the following syntax: $ls dirname
#
# ls
#
# [be2348@localhost OS_lab]$ ls
# assign1


#6)mkdir : It is used to create directories by using the command: $mkdir dirname
#
# mkdir assign1
#
# [be2348@localhost OS_lab]$ mkdir assign1


#7)clear : It clears the screen
#
# clear
#
#[be2348@localhost OS_lab]$ 


#8)cd : It is used to change the current working directory to any other directory specified
#
# cd assign1/
#
# [be2348@localhost OS_lab]$ cd assign1/
# [be2348@localhost assign1]$ 


#9) df:  It displays currently mounted file systems.
#
# df
#
# [be2348@localhost assign1]$ df
# Filesystem                   1K-blocks      Used  Available Use% Mounted on
# /dev/mapper/scientific-root   52399104  27788896   24610208  54% /
# devtmpfs                      32758584         0   32758584   0% /dev
# tmpfs                         32774652     10340   32764312   1% /dev/shm
# tmpfs                         32774652    789320   31985332   3% /run
# tmpfs                         32774652         0   32774652   0% /sys/fs/cgroup
# /dev/sda2                      1039616    238088     801528  23% /boot
# /dev/mapper/scientific-home 2256669952 136296840 2120373112   7% /home
# tmpfs                          6554932        16    6554916   1% /run/user/42
# tmpfs                          6554932         0    6554932   0% /run/user/3067
# tmpfs                          6554932         0    6554932   0% /run/user/3097
# tmpfs                          6554932         0    6554932   0% /run/user/3014
# tmpfs                          6554932         0    6554932   0% /run/user/3107
# tmpfs                          6554932         0    6554932   0% /run/user/3218
# tmpfs                          6554932         0    6554932   0% /run/user/3213
# tmpfs                          6554932         0    6554932   0% /run/user/3271
# tmpfs                          6554932         0    6554932   0% /run/user/3292
# tmpfs                          6554932         0    6554932   0% /run/user/3211
# tmpfs                          6554932         0    6554932   0% /run/user/3209
# tmpfs                          6554932         0    6554932   0% /run/user/3223
# tmpfs                          6554932         0    6554932   0% /run/user/3275
# tmpfs                          6554932         0    6554932   0% /run/user/0
# tmpfs                          6554932         0    6554932   0% /run/user/3264
# tmpfs                          6554932         0    6554932   0% /run/user/3262
# tmpfs                          6554932         0    6554932   0% /run/user/3256
# tmpfs                          6554932         0    6554932   0% /run/user/3219
# tmpfs                          6554932         0    6554932   0% /run/user/3228
# tmpfs                          6554932         0    6554932   0% /run/user/3354
# tmpfs                          6554932         0    6554932   0% /run/user/3251
# tmpfs                          6554932         0    6554932   0% /run/user/3224
# tmpfs                          6554932         0    6554932   0% /run/user/3215
# tmpfs                          6554932         0    6554932   0% /run/user/3236
# tmpfs                          6554932         0    6554932   0% /run/user/3241
# tmpfs                          6554932         0    6554932   0% /run/user/3248
# tmpfs                          6554932         0    6554932   0% /run/user/3208
# tmpfs                          6554932         0    6554932   0% /run/user/3232
# tmpfs                          6554932         0    6554932   0% /run/user/3234
# tmpfs                          6554932         0    6554932   0% /run/user/3231
# tmpfs                          6554932         0    6554932   0% /run/user/3235

# 10) rmdir : Directories can be deleted using the rmdir command - $rmdir dirname
#
# rmdir assign1/
#
# [be2348@localhost OS_lab]$ ls
# assign1
# [be2348@localhost OS_lab]$ rmdir assign1/
# [be2348@localhost OS_lab]$ ls
# [be2348@localhost OS_lab]$ 


#11) cat : It displays the contents of a file - $cat filename
#
# cat test.c
#
#[be2348@localhost OS_lab]$ cat test.c 
# // this is a test file here 
# //here
# //are 
# //the
# //contents 
# //of 
# //this 
# //file


#12) cp : It is used to copy a file - $ cp source_file destination_file
#
# cat test.c test2.c
#
# [be2348@localhost OS_lab]$ cp test.c test2.c
# [be2348@localhost OS_lab]$ cat test2.c
# // this is a test file here 
# //here
# //are 
# //the
# //contents 
# //of 
# //this 
# //file


#13)mv- It is used to change the name of a file - $ mv old_file new_file
#
# mv p1.java  p1a.java
# [be2309@localhost labevaluation]$ mv p1.java  p1a.java
#[be2309@localhost labevaluation]$ ls


# Animal.class  Dog.class  Main.class  p2.java  p4.java  p6.java  p8.java  ScannerDemo.class
# Cat.class     HI.class   p1a.java    p3.java  p5.java  p7.java  p9.java



#14) rm – It is used to delete an existing file - $ rm filename
#
# rm p1a.java
# [be2309@localhost labevaluation]$ rm p1a.java
#[be2309@localhost labevaluation]$ ls
#
#Animal.class  Cat.class  Dog.class  HI.class  Main.class  p2.java  p3.java  p4.java  p5.java  p6.java  #p7.java  p8.java  p9.java  ScannerDemo.class


#15) stat- It is used to display file or file system status - $ stat filename
#
#stat p2.java
#[be2309@localhost labevaluation]$ stat p2.java
#
#  File: âp2.javaâ
#  Size: 235             Blocks: 8          IO Block: 4096   regular file
# Device: fd02h/64770d    Inode: 2418729504  Links: 1
# Access: (0644/-rw-r--r--)  Uid: ( 3212/  be2309)   Gid: ( 2926/  ugyr23)
# Context: unconfined_u:object_r:user_home_t:s0
# Access: 2025-06-13 16:41:10.785155726 +0530
# Modify: 2025-02-10 17:28:02.734311607 +0530
# Change: 2025-02-10 17:28:02.734311607 +0530
# Birth: -


#16) ln - It is used to create links between files and directories.
#
# ln -s p2.java p2a.txt
#[be2309@localhost labevaluation]$ ln -s p2.java p2a.txt
#[be2309@localhost labevaluation]$ ls
#
#Animal.class  Dog.class  Main.class  p2.java  p3.java  p5.java  p7.java  p9.java            symlink1.txt
# Cat.class     HI.class   p2a.txt     p2.txt   p4.java  p6.java  p8.java  ScannerDemo.class



#17) tty – It prints the filename of the terminal connected to standard input.
#
#  tty
#[be2309@localhost labevaluation]$ tty
#
#/dev/pts/31
#


#18) uname –It prints system information
#
# uname
#[be2309@localhost labevaluation]$ uname
#
#Linux


#19) umask – It specifies user file creation mask, implying which of the 3 permissions are to be denied to the owner,group and others.
#
# umask
#[be2309@localhost labevaluation]$ umask
#
#
#0022


#20) find – It searches for files in a directory hierarchy
#
# find . -name p8.java
#[be2309@localhost ~]$ find . -name p8.java
#
#./labevaluation/p8.java



#21) sort – It sorts the lines of text files
#
# sort p2a.txt
#[be2309@localhost labevaluation]$ sort p2a.txt
#
#  {
# {
#  }
# }
#  {
# {
# } 
# }
# catch(ArithmeticException e);
# class Test
#  d=100;
#  int d=0;
 # Public static void main(String args[])
 # result=100/d;
 # System.out.print("After Catch block");
 # System.out.printlin("Exception caught");
 # try

#22) ps - It displays information about the current processes.
#
#[be2309@localhost labevaluation]$ ps
#
# PID TTY          TIME CMD
# 16346 pts/31   00:00:00 bash
# 18321 pts/31   00:00:00 ps


#23) chmod 777 file1 - gives full permission to owner, group and others
#
#[be2309@localhost labevaluation]$ chmod 777 test.c
#1b.c  test2.c  test.c



# 24) grep - It finds specific patterns in files.
#
# grep "int" p2a.txt
#
# [be2309@localhost labevaluation]$ grep "int" p2a.txt
#  int d=0;
#  System.out.printlin("Exception caught");
#  System.out.print("After Catch block");



# Q.25)
# It creates an empty file or updates the timestamp of an existing file.
# touch sample.txt
# [be2306@localhost OS]$ touch sample.txt
# [be2306@localhost OS]$ ls
# sample.txt
#


# Q.26) 
# It displays file content one screen at a time, allowing you to scroll.
#
# more poem.txt
# [be2306@localhost OS]$ more poem.txt 
# Whispers of the Night
# 
# The moonlight paints the skies so bright,
# A silver glow, a calm delight,
# The stars, they twinkle, soft and near,
# Whispering tales that none can hear.
# 
# The trees sway gently, lost in thought,
# A quiet world, by dreams once caught,
# Beneath their leaves, the secrets hide,
# In shadows where the quiet sighs.
# 
# The wind it carries songs untold,
# Of ancient times and hearts of gold,
# And as the night begins to fade,
# The world awakes, and dreams are laid.
# 
#
#  less poem.txt
# [be2306@localhost OS]$ less poem.txt 
# Whispers of the Night
# 
# The moonlight paints the skies so bright,
# A silver glow, a calm delight,
# The stars, they twinkle, soft and near,
# Whispering tales that none can hear.
# 
# The trees sway gently, lost in thought,
# A quiet world, by dreams once caught,
# Beneath their leaves, the secrets hide,
# In shadows where the quiet sighs.
# 
# The wind it carries songs untold,
# Of ancient times and hearts of gold,
# And as the night begins to fade,
# The world awakes, and dreams are laid.
# poem.txt (END)
# 



# Q.27) 
# It displays First/Last 10 lines of a File.
# head/tail
# 
# [be2306@localhost OS]$ head poem.txt 
# Whispers of the Night
#
# The moonlight paints the skies so bright,
# A silver glow, a calm delight,
# The stars, they twinkle, soft and near,
# Whispering tales that none can hear.
#
# The trees sway gently, lost in thought,
# A quiet world, by dreams once caught,
# Beneath their leaves, the secrets hide,
#
#
# [be2306@localhost OS]$ tail poem.txt
# 
# The trees sway gently, lost in thought,
# A quiet world, by dreams once caught,
# Beneath their leaves, the secrets hide,
# In shadows where the quiet sighs.
# 
# The wind it carries songs untold,
# Of ancient times and hearts of gold,
# And as the night begins to fade,
# The world awakes, and dreams are laid.
#

# Q.28)
# It dynamically displays real-time information about system statistics.
# top 
#
# [be2306@localhost OS]$ top
# top - 13:23:42 up 276 days,  1:37, 26 users,  load average: 0.08, 0.05, 0.05
# Tasks: 399 total,   1 running, 391 sleeping,   4 stopped,   0 zombie
# %Cpu(s):  0.0 us,  0.0 sy,  0.0 ni, 99.9 id,  0.0 wa,  0.0 hi,  0.0 si,  0.0 st
# KiB Mem : 65549308 total, 53888284 free,  2374376 used,  9286648 buff/cache
# KiB Swap: 32899068 total, 32899068 free,        0 used. 61630808 avail Mem 
# 
#   PID    USER      PR   NI    VIRT    RES    SHR   S  %CPU %MEM    TIME+ COMMAND          
#   16925 be2306    20    0  157980   2532   1556   R   0.7       0.0                0:00.10 top              
#    927    root          20    0    4368     672      524    S   0.3       0.0  		24:05.96 rngd             
#    6609  root          20    0       0          0          0      S   0.3  	    0.0   	0:00.67 kworker/6:2      
#   11254 root          20    0       0          0          0       S   0.3      0.0   	0:00.83 kworker/9:1      
#   13277 be2321    20    0  147988   2436    1120   S   0.3      0.0   		0:00.48 sshd             
#   14994 root          20    0       0          0          0       S   0.3      0.0   	0:00.24 kworker/2:1      
#   16909 be2321    20    0  157976   2524   1556    S   0.3      0.0   	0:00.22 top              
#      1      root          20    0  194444   7592   3988    S   0.0      0.0  		29:29.66 systemd          
#      2      root          20    0       0          0          0       S   0.0      0.0   	0:25.74 kthreadd         
#      3      root          20    0       0      	  0          0       S   0.0      0.0 		360:10.51 ksoftirqd/0      
#      8      root          rt      0       0          0          0       S   0.0      0.0   	0:04.47 migration/0      
#      9      root          20    0       0          0          0       S   0.0      0.0   	0:00.00 rcu_bh           
#     10     root          20    0       0          0          0       S   0.0      0.0 		328:07.49 rcu_sched        
#   11       root           rt     0       0          0          0       S   0.0      0.0   	1:07.28 watchdog/0       
#   12       root           rt     0       0          0          0       S   0.0      0.0   	1:06.21 watchdog/1       
#   13 	    root           rt     0       0          0          0       S   0.0      0.0   	0:13.42 migration/1      
#   14 	    root           20   0       0          0          0       S   0.0      0.0 		260:50.20 ksoftirqd/1      
#   16       root           0   -20      0          0          0       S   0.0      0.0   	0:00.00 kworker/1:0H     
#   17 	    root           rt     0       0          0          0       S   0.0      0.0   	1:00.48 watchdog/2       
#   18       root           rt     0       0          0          0       S   0.0      0.0   	0:08.19 migration/2      
#   19       root          20    0       0          0          0       S   0.0      0.0 		200:43.42 ksoftirqd/2      
#   21       root           0   -20      0          0          0       S   0.0      0.0   	0:00.00 kworker/2:0H     
#   22       root           rt     0       0          0          0       S   0.0      0.0   	0:59.45 watchdog/3       
#   23       root           rt     0       0          0          0       S   0.0      0.0   	0:06.02 migration/3      
#   24       root          20    0       0          0          0       S   0.0      0.0 		167:21.24 ksoftirqd/3      
#   26       root           0   -20      0          0          0       S   0.0      0.0   	0:00.00 kworker/3:0H     
#   27       root           rt     0       0          0          0       S   0.0      0.0   	1:02.19 watchdog/4       
#   28       root           rt     0       0          0          0       S   0.0      0.0   	0:02.05 migration/4      
#   29       root          20    0       0          0          0       S   0.0      0.0 		243:32.46 ksoftirqd/4      
#   31       root           0   -20      0          0          0       S   0.0      0.0   	0:00.00 kworker/4:0H     
#


# Q.29)
# It terminates a Process.
#  kill 14164
#
# [be2306@localhost OS]$ kill 14164
# -bash: kill: (14164) - Operation not permitted
#


# Q.30) It displays a list of previously executed commands
# history
#[be2306@localhost OS]$ history
#
# 535  cd ass2/dll/
#  536  ls
#  537  ./sender 
#  538  vi sender.c
#  539  cat sender.c
#  540  ls
#  541  vi sender2.c
#  542  gcc sender.c -o sender2
#  543  ./sender2
#  …………………….
# 1006  touch sample.txt
# 1007  ls
# 1008  more sample.txt
# 1009  vi sample.txt 
# 1010  clear
# 1011  vi story.txt
# 1012  clear
# 1013  more story.txt 
# 1014  vi story.txt 
# 1015  cat story.txt 
# 1016  rm story.txt 
# 1017  vi poem.txt
# 1018  more poem.txt 
# 1019  less poem.txt 
# 1020  clear
# 1021  head poem.txt 
# 1022  tail poem.txt
# 1023  top
# 1024  clear
# 1025  top
# 1026  kill 14762
# 1027  top
# 1028  kill 14164
# 1029  history



.
# Q.31) It estimates file space usage (of a file or directory).
# du 
#
# [be2306@localhost OS]$ du
# 8       .
#


# Q.32) It tests network connectivity to a host.
# ping 8.8.8.8
# [be2306@localhost OS]$ ping 8.8.8.8
# PING 8.8.8.8 (8.8.8.8) 56(84) bytes of data.
# 64 bytes from 8.8.8.8: icmp_seq=1 ttl=118 time=33.9 ms
# 64 bytes from 8.8.8.8: icmp_seq=2 ttl=118 time=34.0 ms
# 64 bytes from 8.8.8.8: icmp_seq=3 ttl=118 time=34.1 ms
# 64 bytes from 8.8.8.8: icmp_seq=4 ttl=118 time=34.2 ms
# 64 bytes from 8.8.8.8: icmp_seq=5 ttl=118 time=34.1 ms
# 64 bytes from 8.8.8.8: icmp_seq=6 ttl=118 time=34.2 ms
# 64 bytes from 8.8.8.8: icmp_seq=7 ttl=118 time=34.1 ms
# ^C
# --- 8.8.8.8 ping statistics ---
# 7 packets transmitted, 7 received, 0% packet loss, time 6007ms
# rtt min/avg/max/mdev = 33.994/34.128/34.281/0.137 ms






# Q.33) It counts lines, words, and characters in a file.
# wc poem.txt
# [be2306@localhost OS]$ wc poem.txt 
#16  83 470 poem.txt
#



# Q.34) It redirects the standard output of a command to a file, overwriting the file if it exists.
# >/>> 
#
# [be2306@localhost OS]$ ll > demo.txt
# [be2306@localhost OS]$ cat demo.txt 
# total 8
# -rw-r--r--. 1 be2306 ugyr23   0 Jul 24 14:08 demo.txt
# -rw-r--r--. 1 be2306 ugyr23 114 Jul 24 14:07 poem.txt
# -rw-r--r--. 1 be2306 ugyr23   1 Jul 24 13:06 sample.txt
#
#
#[be2306@localhost OS]$ echo "This is new text" >> demo.txt 
# [be2306@localhost OS]$ cat demo.txt 
# total 8
# -rw-r--r--. 1 be2306 ugyr23   0 Jul 24 14:08 demo.txt
# -rw-r--r--. 1 be2306 ugyr23 114 Jul 24 14:07 poem.txt
# -rw-r--r--. 1 be2306 ugyr23   1 Jul 24 13:06 sample.txt 
# This is new text



# Q.35)It takes the standard output of one command and uses it as the standard input for another command.
#  | 
# [be2306@localhost OS]$ ll -l | wc -l
# 4
#


