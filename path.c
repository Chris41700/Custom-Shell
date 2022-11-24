//By Patrick Lisiecki
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
int main() {
    //Create process id for identifying child process
    pid_t process;

    //Create file descriptor array for pipe
    int link[2];

    //Call pipe
    pipe(link);

    //Buffer to read from pipe
    char pipeBuffer[1024];
    char fileBuffer[1024];
    char finalResult[1024];

    //Fork a process
    process = fork();

    //Fork was unsuccessful
    if (process == -1) {
        printf("Error forking process!");
        exit(1);
    }
    //Child process returns a 0
    else if (process == 0) {
        //Print to terminal
        printf("Getting current working directory...\n");

        //Connect write end of the pipe to the file number of stdout
        dup2(link[1], STDOUT_FILENO);

        //Execute command that returns current working directory
        execlp("pwd", "pwd", NULL);

        //Close both ends of pipe
        close(link[0]);
        close(link[1]);

        //Process terminates
        exit(0);
    }
    //Parent process
    else {
        //Close write end of pipe
        close(link[1]);

        //Read from pipe into buffer
        ssize_t readBytes = read(link[0], &pipeBuffer, sizeof(pipeBuffer));

        if (readBytes == -1) {
            printf("Read was unsuccessful!");
            exit(1);
        }
        else {
            int pipeBufferLength = strlen(pipeBuffer);
            pipeBuffer[pipeBufferLength - 1] = '\0';
            //Print the output to the terminal
            printf("Current directory: %s\n", pipeBuffer);
        }

        //Close read end of pipe
        close(link[0]);

        //Open t2.txt in write mode
        FILE* pathPtr;
        pathPtr = fopen("t2.txt", "w");

        //Check for error opening file
        if (pathPtr == NULL) {
            printf("Error opening t2.txt!");
            exit(1);
        }
        else {
            printf("\nWriting current directory to file...")
            //Print the current working directory to the file
            for (int x = 0; x < strlen(pipeBuffer); x++) {
                fputc(pipeBuffer[x], pathPtr);
            }
        }

        //Close file
        fclose(pathPtr);

        //Change the name of t2.txt to path.txt
        //Works using the current directory the text file is in
        //execlp("mv", "mv", "*path of file*", "path.txt", NULL);

        printf("\nRenaming file to path.txt...");

        //Renaming t2.txt using rename function
        int renameToPath = rename("t2.txt", "path.txt");

        if (renameToPath != 0) {
            printf("Error renaming file to path.txt!");
            exit(1);
        }

        //Open tree.txt in read mode
        FILE* treePtr;
        treePtr = fopen("tree.txt", "r");

        if (treePtr == NULL) {
            printf("Error opening tree.txt!");
            exit(1);
        }
        else {
            printf("\nReading from tree.txt...\n");
            //Read from file into buffer
            fread(&fileBuffer, sizeof(char), sizeof(fileBuffer), treePtr);

            int fileBufferLength = strlen(fileBuffer);
            fileBuffer[fileBufferLength - 1] = '\0';

            //Check to make sure file was read correctly
            printf("\nTree.txt: %s\n", fileBuffer);
        }

        //Close file
        fclose(treePtr);

        //Concatenate output from current working directory and output from tree.txt
        strcat(finalResult, pipeBuffer);
        strcat(finalResult, fileBuffer);

        //Print concatenation to check
        printf("\nFinal result: %s\n", finalResult);

        //Open t3.txt in write mode
        FILE* logPtr;
        logPtr = fopen("t3.txt", "w");

        if (logPtr == NULL) {
            printf("Error opening t3.txt!");
            exit(1);
        }
        else {
            printf("\nWriting to t3.txt...");
            //Write the concatenated output to t3.txt
            for (int x = 0; x < strlen(finalResult); x++) {
                fputc(finalResult[x], logPtr);
            }
        }

        //Close file
        fclose(logPtr);

        printf("\nRenaming file to log.txt...");

        //Rename t3.txt to log.txt
        int renameToLog = rename("t3.txt", "log.txt");

        if (renameToLog != 0) {
            printf("Error renaming t3.txt!");
            exit(1);
        }

        printf("\nDeleting files...");

        //Execute remove command for tree.txt and path.txt
        execlp("rm", "rm", "tree.txt", "path.txt", NULL);

        //Parent must wait for child process to terminate
        wait(NULL);
    }

    return 0;
}
