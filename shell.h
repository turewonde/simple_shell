#ifndef SHELL_H
#define SHELL_H
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include <sys/stat.h>

void loop();
char *read_line();
char **split_line(char *);
int dash_exit(char **);
int dash_execute(char **);

#endif
