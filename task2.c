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
 * Descriptption:
 * It displays a prompt, waits for user input, and execute
 *
 * Return: 0 on success, -1 on error.
 */
int main(void)
{
	char input[MAX_INPUT_LENGTH];
	char *arguments[MAX_ARGUMENTS];
	int argc;

	while (1)
	{
		printf("shell$ ");
		fgets(input, sizeof(input), stdin);
		if (feof(stdin))
		{
			printf("\n");
			break;  /* Exit on Ctrl+D (EOF) */
		}
		input[strcspn(input, "\n")] = '\0';
		pid_t pid = fork();

		if (pid == -1)
		{
			perror("fork");
			exit(EXIT_FAILURE);
		}
		else
			if (pid == 0)
		{
			/* Child process */
			argc = 0;
			arguments[argc] = strtok(input, " ");
			while (arguments[argc] != NULL)
			{
				argc++;
				arguments[argc] = strtok(NULL, " ");
			}
			arguments[argc] = NULL;
			execvp(arguments[0], arguments);
			perror(arguments[0]);
			exit(EXIT_FAILURE);
		}
		else
		{
			/* Parent process */
			int status;

			wait(&status);
		}
	}
	return (0);
}

