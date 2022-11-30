#include "shell.h"

char *updateHistory[4] = {"\0", "\0", "\0", "\0"};
int count = 0;

int main(int argc, char *argv[])
{
    shell_loop();
    return 0;
}

void shell_loop()
{
    char *args;
    int status;

    do
    {
        printf("@ ");
        args = read_line();
        status = execute(args);
    } while (status);

    free(args);
}

char *read_line(void)
{
    char *line;
    size_t bufsize = 0;

    if (getline(&line, &bufsize, stdin) == -1)
    {
        printf("Could not allocate memory for buffer");
        exit(1);
    }

    size_t length = strlen(line);

    if (line[length - 1] == '\n')
    {
        line[length - 1] = '\0';
    }

    if (count < 4)
    {
        updateHistory[count] = malloc(strlen(line));
        strcpy(updateHistory[count], line);
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
    char *commandList[4] = {"tree*", "list*", "path*", "exit*"};
    int size = sizeof(updateHistory) / sizeof(char *);

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
