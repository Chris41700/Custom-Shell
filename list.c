#include "shell.h"

void run_list()
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
        perror("Fork failed\n");
        exit(1);
    }
    else if (pid == 0)
    { /* child process */
        printf("Clearing the screen...\n");
        sleep(3);
        system("clear"); // clear the screen

        printf("List the contents of the current directory\n");

        dup2(arr[1], 1); /* duplicate the writing end of pipe */

        execlp("ls", "ls", "-l", (char *)NULL); /* execute ls -l command to list files */

        close(arr[0]); /* close reading end of pipe */
        close(arr[1]); /* close writing end of pipe */
    }
    else
    {
        waitpid(pid, NULL, 0); /* wait for child process to end */

        ssize_t readBytes = read(arr[0], &fileBuffer, sizeof(fileBuffer));

        if (readBytes == -1)
        {
            perror("Read was unsuccessful\n");
            exit(1);
        }

        printf(fileBuffer);

        fileBuffer[strlen(fileBuffer) - 1] = '\0';

        close(arr[0]); /* close reading end of pipe */
        close(arr[1]); /* close writing end of pipe */

        char *filename = "t1.txt";

        FILE *fp = fopen(filename, "w");

        if (fp == NULL)
        {
            perror("Error opening file\n");
            exit(1);
        }

        printf("\nWriting to t1.txt...\n");

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
}
