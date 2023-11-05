#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_INPUT_LENGTH 100
#define MAX_ARGUMENTS 20

/**
 * main - Simple Shell 0.2
 *
 * Description:
 * This program implements a basic shell that handles command lines with arguments.
 * It displays a prompt, waits for user input, and executes the given command
 * with its arguments.
 *
 * Return: 0 on success, -1 on error.
 */
int main(void)
{
    char input[MAX_INPUT_LENGTH];     /* Stores user input */
    char *arguments[MAX_ARGUMENTS];   /* Stores command and arguments */
    int argc;                         /* Argument count */

    while (1)
    {
        printf("#simple_shell$ ");    /* Display shell prompt */
        fgets(input, sizeof(input), stdin);  /* Read user input */

        if (feof(stdin))
        {
            printf("\n");
            break;  /* Exit on Ctrl+D (EOF) */
        }

        /* Remove the newline character from the input */
        input[strcspn(input, "\n")] = '\0';

        pid_t pid = fork();  /* Create a child process */

        if (pid == -1)
        {
            perror("fork");  /* Handle fork error */
            exit(EXIT_FAILURE);
        }
        else if (pid == 0)
        {
            /* Child process */
            argc = 0;
            arguments[argc] = strtok(input, " ");  /* Split input into tokens */

            while (arguments[argc] != NULL)
            {
                argc++;
                arguments[argc] = strtok(NULL, " ");
            }
            arguments[argc] = NULL;

            execvp(arguments[0], arguments);  /* Execute the command with arguments */
            perror(arguments[0]);  /* Handle execution error */
            exit(EXIT_FAILURE);
        }
        else
        {
            /* Parent process */
            int status;
            wait(&status);  /* Wait for child process to complete */
        }
    }

    return 0;  /* Return 0 on success */
}
