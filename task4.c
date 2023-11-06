#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_INPUT_LENGTH 100
#define MAX_ARGUMENTS 20

/**
 * main - Simple Shell 0.4
 *
 * Description:
 * This is a basic shell that handles command lines with arguments,
 * includes PATH support, avoids forking if the command doesn't exist,
 * and implements the exit built-in command to exit the shell gracefully.
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
        printf(":) ");    /* Display shell prompt */

        /* Read user input */
        fgets(input, sizeof(input), stdin);

        if (feof(stdin))
        {
            break;  /* Exit on Ctrl+D (EOF) */
        }

        /* Remove the newline character from the input */
        input[strcspn(input, "\n")] = '\0';

        /* Check if the command is "exit" to exit the shell */
        if (strcmp(input, "exit") == 0)
        {
            printf("Murabeho!\n");  /* Display a farewell message */
            break;  /* Exit the shell gracefully */
        }

        // Check if the command exists in PATH
        char *path = getenv("PATH");
        char *command = strtok(input, " ");

        if (access(command, X_OK) == 0)
        {
            strcpy(input, command);
        }
        else if (path != NULL)
        {
            char *path_token = strtok(path, ":");
            while (path_token != NULL)
            {
                char cmd_path[MAX_INPUT_LENGTH];
                snprintf(cmd_path, sizeof(cmd_path), "%s/%s", path_token, command);
                if (access(cmd_path, X_OK) == 0)
                {
                    strcpy(input, cmd_path);
                    break;
                }
                path_token = strtok(NULL, ":");
            }
        }

        pid_t pid = fork();  /* Create a child process */

        if (pid == -1)
        {
            perror("Error: Unable to create a child process.");
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

            if (execvp(arguments[0], arguments) == -1)
            {
                perror("Execution error");
                exit(EXIT_FAILURE);
            }
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
