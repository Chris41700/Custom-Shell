#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

void shell_loop();
char *read_line(void);
int execute(char *args);

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

        free(args);
    } while (status);
}

char *read_line(void)
{
    char *line;
    size_t bufsize = 0;
    getline(&line, &bufsize, stdin);
    return line;
}

int execute(char *args)
{
    pid_t pid;
    int status;

    pid = fork();

    if (pid < 0)
    {
        printf("Fork unsuccessful");
        return 1;
    }

    if (pid == 0)
    {
        if (strcmp(args, "tree*"))
        {
            execl("tree", args, NULL);
        }
        else if (strcmp(args, "list*"))
        {
            execl("list", args, NULL);
        }
        else if (strcmp(args, "path*"))
        {
            execl("path", args, NULL);
        }
        else if (strcmp(args, "exit*"))
        {
            execl("exit", args, NULL);
        }
    }

    waitpid(pid, &status, WUNTRACED);

    return 1;
}
