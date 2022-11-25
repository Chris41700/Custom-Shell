#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
    printf("Clearing the screen...");
    sleep(3);

    system("clear"); // clear the screen
    pid_t pid;
    int arr[2]; /* creating a pipe of two ends to read and write */

    pipe(arr); /*call pipe*/

    pid = fork(); /* fork a child process */

    if (pid < 0)
    { /* check for error */
        fprintf(stderr, "Fork Failed.");
        return 1;
    }
    else if (pid == 0)
    {                                   /* child process */
        close(arr[0]);                  /* close reading end of pipe */
        dup2(arr[1], 1);                /* duplicate the writing end of pipe */
        close(arr[1]);                  /* close writing end of pipe */
        execlp("ls", "ls", "-l", NULL); /* execute ls -l command to list files */
    }
    else
    {
        close(arr[0]); /* close reading end of pipe */
        close(arr[1]); /* close writing end of pipe */

        waitpid(pid, NULL, 0); /* wait for child process to end */

        char *filename = "t1.txt";

        FILE *fp = fopen(filename, "w");

        if (fp == NULL)
        {
            printf("Error opening the file %s", filename);
            return -1;
        }

        int file = rename("t1.txt", "tree.txt");
        if (file == 0)
        {
            printf("The file is renamed successfully.");
        }
        else
        {
            printf("The file could not be renamed.");
        }
    }

    return 0;
}