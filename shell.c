#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

void shellLoop();
char *read_line(void);

int main(int argc, char *argv[])
{
    shellLoop();
    return 0;
}

void shellLoop()
{
    char *line;
    char **args;
    int status;

    do
    {
        printf("@ ");
        line = read_line();
        status = execute(args);

        if (args[0] != NULL)
        {
            execute(args);
        }

        free(line);
        free(args);
    } while (status)
}

char *read_line(void)
{
    char *line;
    size_t bufsize = 0;
    getline(&line, &bufsize, stdin);
    return line;
}
