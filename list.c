#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])
{
    // Create a parent process
    pid_t pid;

    //
    char fileBuffer[1024];
    int arr[2]; /* creating a pipe of two ends to read and write */

    pipe(arr); /*call pipe*/

    pid = fork(); /* fork a child process */

    if (pid < 0)
    { /* check for error */
        fprintf(stderr, "Fork Failed.");
        return 1;
    }
    else if (pid == 0)
    { /* child process */
        printf("Clearing the screen...\n");
        sleep(3);
        system("clear"); // clear the screen

        printf("List the contents of the current directory:\n");

        dup2(arr[1], 1); /* duplicate the writing end of pipe */

        close(arr[0]);                  /* close reading end of pipe */
        close(arr[1]);                  /* close writing end of pipe */
        execlp("ls", "ls", "-l", NULL); /* execute ls -l command to list files */
    }
    else
    {
        waitpid(pid, NULL, 0); /* wait for child process to end */

        ssize_t readBytes = read(arr[0], &fileBuffer, sizeof(fileBuffer));

        if (readBytes == -1)
        {
            printf("Read was unsuccessful!");
            exit(1);
        }

        int fileBufferLength = strlen(fileBuffer) - 1;
        fileBuffer[strlen(fileBufferLength - 1)] = '\0';

        close(arr[0]); /* close reading end of pipe */
        close(arr[1]); /* close writing end of pipe */

        char *filename = "t1.txt";

        FILE *fp = fopen(filename, "w");

        if (fp == NULL)
        {
            printf("Error opening the file %s", filename);
            return -1;
        }

        printf("Writing to t1.txt...\n");

        for (int i = 0; i < strlen(fileBuffer); i++)
        {
            fputc(fileBuffer[i], fp);
        }

        fclose(fp);

        int file = rename("t1.txt", "tree.txt");
        if (file == 0)
        {
            printf("The file is renamed successfully.\n");
        }
        else
        {
            printf("The file could not be renamed.\n");
        }
    }

    return 0;
}