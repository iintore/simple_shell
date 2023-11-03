#ifndef CUSTOM_SHELL_H
#define CUSTOM_SHELL_H

/* Required header files */
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <errno.h>
#include <fcntl.h>
#include <signal.h>
#include <limits.h>

/* Prototypes for functions in the change_dir.c file */
void move_up_directory(data_shell *data);
void move_to_directory(data_shell *data);
void move_to_previous(data_shell *data);
void move_to_home(data_shell *data);
#endif
