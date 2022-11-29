// By Christopher Hui
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

void shell_loop();
char *read_line(void);
int execute(char *args);

char *updateHistory[4];

int main(int argc, char *argv[])
{
    // Run the shell environment
    shell_loop();
    return 0;
}

void shell_loop()
{
    // Store the command input
    char *args;

    // Exit status
    int status;

    do
    {
        printf("@ ");

        // Run read line function
        args = read_line();

        // Run execute function
        status = execute(args);
    } while (status);

    // Free allocated memory
    free(args);
}

char *read_line(void)
{
    // Stores the user input
    char *line;

    // Buffer size is determined by input
    size_t bufsize = 0;

    // Reads in the input
    if (getline(&line, &bufsize, stdin) == -1)
    {
        printf("Could not allocate memory for buffer");
        exit(1);
    }

    // Length of line
    size_t length = strlen(line);

    // Remove extra character attach to the end with termination character
    if (line[length - 1] == '\n')
    {
        line[length - 1] = '\0';
    }

    int count = 0;

    if (count < 4)
    {
        updateHistory[count] = line;
        count++;
    }
    else
    {
        count = count % 4;
    }

    return line;
}

int execute(char *args)
{
    // Create parent process
    pid_t pid;

    // Fork the parent process to create a child process
    pid = fork();

    // All commands executable in the shell
    char *commandList[4] = {"tree*", "list*", "path*", "exit*"};

    // Checks fork is unsuccessful
    if (pid < 0)
    {
        printf("Fork unsuccessful");
        return 1;
    }
    // Child process
    else if (pid == 0)
    {
        // String compare user input with command list to execute the file
        if (strcmp(args, commandList[0]) == 0)
        {
            execlp("./tree", args, (char *)NULL);
        }
        else if (strcmp(args, commandList[1]) == 0)
        {
            execlp("./list", args, (char *)NULL);
        }
        else if (strcmp(args, commandList[2]) == 0)
        {
            execlp("./path", args, (char *)NULL);
        }
        else if (strcmp(args, commandList[3]) == 0)
        {
            execv("./exit", updateHistory);
        }

        // Wait until child process completes
        wait(NULL);

        return 1;
    }
