// By Elijah Estimada
#include "shell.h"

void run_tree()
{
    // Fork a process
    int fid = fork();

    // Child Process
    if (fid == 0)
    {
        printf("Making directory dir0\n");

        // Make dir0
        mkdir("dir0", 0777);
    }
    // Fork was unsuccessful
    if (fid < 0)
    {
        perror("Forked Failed\n");
        exit(1);
    }
    // Parent Process
    else
    {
        // Wait for child process to terminate
        wait(NULL);

        printf("Change directory to dir0\n");

        // Change directory to dir0
        chdir("dir0");

        printf("Creating t1.txt, t2.txt, t3.txt\n");

        // Create t1.txt
        FILE *t1 = fopen("t1.txt", "wb");

        // Close the file
        fclose(t1);

        // Create t2.txt
        FILE *t2 = fopen("t2.txt", "wb"); // Create t2.txt

        // Close the file
        fclose(t2);

        // Create t3.txt
        FILE *t3 = fopen("t3.txt", "wb"); // Create t3.txt

        // Close the file
        fclose(t3);

        printf("Make directory dir1\n");

        // Make empty dir1
        mkdir("dir1", 0777);
    }
}
