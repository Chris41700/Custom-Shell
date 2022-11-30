// By Elijah Estimada
#include "shell.h"

void run_tree()
{
    int check;
    char *dirname = "dir0";

    // Make directory dir0
    check = mkdir(dirname, 0777);

    // Create directory was successful
    if (!check)
    {
        printf("Directory dir0 was created\n");
    }
    // Failed to create directory
    else
    {
        perror("Unable to create directory\n");
        exit(1);
    }

    printf("Change directory to dir0\n");

    // Change directory to dir0
    chdir("dir0");

    printf("Creating t1.txt, t2.txt, t3.txt\n");

    // Create t1.txt
    FILE *t1 = fopen("t1.txt", "wb");

    // Close the file
    fclose(t1);

    // Create t2.txt
    FILE *t2 = fopen("t2.txt", "wb"); // Create t2.txt

    // Close the file
    fclose(t2);

    // Create t3.txt
    FILE *t3 = fopen("t3.txt", "wb"); // Create t3.txt

    // Close the file
    fclose(t3);

    dirname = "dir1";

    // Make empty dir1
    check = mkdir(dirname, 0777);

    // Create directory was successful
    if (!check)
    {
        printf("Directory dir1 was created\n");
    }
    // Failed to create directory
    else
    {
        perror("Unable to create directory\n");
        exit(1);
    }
}
