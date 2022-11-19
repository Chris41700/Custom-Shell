#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>

int main() {
    pid_t childOne, childTwo;

    //Process prints the current directory
    switch (childOne = fork()) {
        case -1:
            printf("Error creating first child process!");
            break;
        case 0:
            execlp("pwd", "pwd", NULL);
            exit(0);
        default:
    }

    //Printing the output of "pwd" to "t2.txt"

    //Process changes the name of "t2.txt" to "path.txt"
    switch (childTwo = fork()) {
        case -1:
            printf("Error creating second child process!");
            break;
        case 0:
            //Works using the current directory that the text file is in
            //Might change
            execlp("mv", "mv", "/home/lisiecki/Path/t2.txt", "path.txt", NULL);
            exit(0);
        default:
    }

    //Wait for all children processes
    if (childOne >= 0) {
        wait(NULL);
    }

    if (childTwo >= 0) {
        wait(NULL);
    }

    return 0;
}