// By Khadijah Akter
#include "shell.h"

void run_list()
{
    // Create a parent process
    pid_t pid;

    // Create a file buffer to store ls -l
    char fileBuffer[1024];

    // Create a pipe to read and write
    int arr[2];

    // Calls pipe
    pipe(arr);

    // Fork a process
    pid = fork();

    // Fork was unsuccessful
    if (pid < 0)
    {
        perror("Fork failed\n");
        exit(1);
    }
    // Child process
    else if (pid == 0)
    {
        printf("Clearing the screen...\n");

        // Sleep for 3 seconds
        sleep(3);

        // Clear the screen
        system("clear");

        printf("List the contents of the current directory\n");

        // Duplicate the writing end of pipe
        dup2(arr[1], 1);

        // Display detailed list of all content in current directory
        execlp("ls", "ls", "-l", (char *)NULL);

        // Close reading end of pipe
        close(arr[0]);

        // Close writing end of pipe
        close(arr[1]);
    }
    // Parent process
    else
    {
        // Wait for child process to terminate
        waitpid(pid, NULL, 0);

        // Change directory to dir0
        chdir("dir0");

        // Read from pipe into file buffer
        ssize_t readBytes = read(arr[0], &fileBuffer, sizeof(fileBuffer));

        // Read was unsuccessful
        if (readBytes == -1)
        {
            perror("Read was unsuccessful\n");
            exit(1);
        }

        // Display file buffer to terminal
        printf(fileBuffer);

        // Replace last character with termination character
        fileBuffer[strlen(fileBuffer) - 1] = '\0';

        // Close reading end of pipe
        close(arr[0]);

        // Close writing end of pipe
        close(arr[1]);

        char *filename = "t1.txt";

        // Open t1.txt in write mode
        FILE *fp = fopen(filename, "w");

        // Check for error opening file
        if (fp == NULL)
        {
            perror("Error opening file\n");
            exit(1);
        }

        printf("\nWriting to t1.txt...\n");

        // Print the detailed list of all content to the file
        for (int i = 0; i < strlen(fileBuffer); i++)
        {
            fputc(fileBuffer[i], fp);
        }

        // Close the file
        fclose(fp);

        // Reename t1.txt to tree.txt
        int file = rename("t1.txt", "tree.txt");

        // File renamed successful
        if (file == 0)
        {
            printf("The file is renamed successfully.\n");
        }
        // File renamed unsuccessful
        else
        {
            printf("The file could not be renamed.\n");
        }
    }
}
