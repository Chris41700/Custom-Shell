#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
    printf("Printing the command history...\n");

    int count = 0;
    while (count < 4)
    {
        printf(argv[count]);
        count++;
    }

    pid_t pid;    // declaring process identifie
    pid = fork(); // fork a child process

    if (pid < 0)
    {
        // Error occurred
        fprintf(stderr, "Fork Failed");
        return 1;
    }
    else if (pid == 0)
    {   // child for pid
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

        if (ch == "\n")
        {
            exit(0);
        }
    }

    return 0;
}
