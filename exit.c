#include "shell.h"

void run_exit(char *updateHistory[], int size)
{
    printf("Printing the command history...\n");

    for (int i = 0; i < size; i++)
    {
        printf("%s\n", updateHistory[i]);
    }

    pid_t pid;    // declaring process identifie
    pid = fork(); // fork a child process

    if (pid < 0)
    {
        // Error occurred
        perror("Forked Failed\n");
        exit(1);
    }
    else if (pid == 0)
    { // child for pid
        // Child
        char *arg_list[] = {
            "ls",
            "-l",
            NULL};

        execvp("ls", arg_list); // Execute ls -l
    }
    else
    {

        waitpid(pid, NULL, 0);                                   // waits only for terminated chiildren
        printf("\nHit the return key to terminate the shell\n"); // prints
        char ch = getchar();                                     // Waits for return

        if (ch == '\n')
        {
            exit(0);
        }
    }
}
