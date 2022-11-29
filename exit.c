// By Oscar Jara
#include "shell.h"

void run_exit(char *updateHistory[], int size)
{
    printf("Printing the command history...\n");

    // Print every command in command history
    for (int i = 0; i < size; i++)
    {
        printf("%s\n", updateHistory[i]);
    }

    // Create a parent process
    pid_t pid;

    // Fork a process
    pid = fork();

    // Argument list for ls -l
    char *arg_list[] = {
        "ls",
        "-l",
        NULL};

    // Forking was unsuccessful
    if (pid < 0)
    {
        perror("Forked Failed\n");
        exit(1);
    }
    // Child process
    else if (pid == 0)
    {
        // Display detailed list of all content in current directory
        execvp("ls", arg_list);
    }
    else
    {
        // Waits for child process to terminate
        waitpid(pid, NULL, 0);
        printf("\nHit the return key to terminate the shell\n"); // prints

        // Get character from keyboard
        char ch = getchar();

        // Terminate the shell when the return key is entered
        if (ch == '\n')
        {
            exit(1);
        }
    }
}
