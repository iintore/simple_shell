#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_INPUT_LENGTH 512
#define MAX_ARGUMENTS 20

/**
 * main - Simple Shell 0.4
 *
 * Description:
 * This is a basic shell that handles command lines with args.
 *
 * Return: 0 on success, -1 on error.
 */
int main(void)
{
	int status;
	char cmd_path[MAX_INPUT_LENGTH]; /*use a larger buffer size*/
	char input[MAX_INPUT_LENGTH];
	char *arguments[MAX_ARGUMENTS];
	int argc;
	char *path = getenv("PATH");
	pid_t pid;
	
	while (1)
	{
		printf(":) ");
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

		if (access(input, X_OK) == 0)
		{
			/* If the command is executable within the current directory */
		}
		else if (path != NULL)
{
    char *path_token = strtok(path, ":");

    while (path_token != NULL)
    {
        strncpy(cmd_path, path_token, sizeof(cmd_path) - 1);
        cmd_path[sizeof(cmd_path) - 1] = '\0';  /* Null-terminate the string */
        strncat(cmd_path, "/", sizeof(cmd_path) - strlen(cmd_path) - 1);
        strncat(cmd_path, input, sizeof(cmd_path) - strlen(cmd_path) - 1);

        if (access(cmd_path, X_OK) == 0)
        {
            strcpy(input, cmd_path);
            break;
        }
        path_token = strtok(NULL, ":");
    }
}


		pid = fork();  /* Create a child process */
		
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
			waitpid(pid, &status, 0);  /* Wait for child process to complete */
		}
	}
	return (0);  /* Return 0 on success */
}
