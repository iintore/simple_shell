#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_INPUT_LENGTH 100
#define MAX_ARGUMENTS 20

/**
 * main - Simple Custom Shell 0.5
 *
 * Description:
 * This is a basic custom shell that handles command lines with arguments,
 * includes PATH support, avoids forking if the command doesn't exist,
 * implements the exit built-in command to exit the shell gracefully,
 * and adds the env built-in command to print the current environment.
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
        printf("$ ");    /* Display the custom shell prompt */

        /* Read user input */
        fgets(input, sizeof(input), stdin);

        if (feof(stdin))
        {
            break;  /* Exit on Ctrl+D (EOF) */
        }

        /* Remove the newline character from the input */
        input[strcspn(input, "\n")] = '\0';

        /* Check if the command is "exit" to exit the custom shell */
        if (strcmp(input, "exit") == 0)
        {
            printf("Murabeho!\n");  /* Display a unique farewell message */
            break;  /* Exit the custom shell gracefully */
        }

        /* Check if the command is "env" to print the environment */
        if (strcmp(input, "env") == 0)
        {
            extern char **environ;  /* Access the environment variables */

            char **env = environ;
            while (*env)
            {
                printf("%s\n", *env);
                env++;
            }
            continue;  /* Skip the fork for the "env" command */
        }

        // Check if the command exists in the PATH
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
            wait(&status);  /* Wait for the child process to complete */
        }
    }

    return 0;  /* Return 0 on success */
}
