// Group Name: Incognito Mode
// Leader: Christopher Hui
// Group Members: Elijah Estimada, Khadijah Akter, Patrick Lisiecki, Oscar Jara

#ifndef SHELL_H
#define SHELL_H

#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void shell_loop();
char *read_line(void);
int execute(char *args);
void run_list();
int run_path();
void run_exit(char *updateHistory[], int size);

#endif
