// Christopher Hui
#include "shell.h"

char *updateHistory[4] = {"\0", "\0", "\0", "\0"};
int count = 0;

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

    int count = 0;

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

    // Allocate memory and store the command
    if (count < 4)
    {
        updateHistory[count] = malloc(strlen(line));
        strcpy(updateHistory[count], line);
        count++;
    }
    // Restart the count
    else
    {
        count = count % 4;
    }

    return line;
}

int execute(char *args)
{
    // All commands executable in the shell
    char *commandList[4] = {"tree*", "list*", "path*", "exit*"};

    // Store the size of the updated history
    int size = sizeof(updateHistory) / sizeof(char *);

    // String compare user input with command list to execute the file
    if (strcmp(args, commandList[0]) == 0)
    {
        run_tree();
    }
    else if (strcmp(args, commandList[1]) == 0)
    {
        run_list();
    }
    else if (strcmp(args, commandList[2]) == 0)
    {
        run_path();
    }
    else if (strcmp(args, commandList[3]) == 0)
    {
        run_exit(updateHistory, size);
    }

    return 1;
}
