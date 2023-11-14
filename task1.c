#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_COMMAND_LENGTH 100

/**
 * main - Simple Shell
 *
 * Description:
 * This program implements a basic shell. It displays a prompt, waits for
 * user input, and executes the given command.
 *
 * Return: 0 on success, -1 on error.
 */
int main(void)
{
	char input[MAX_COMMAND_LENGTH];

	while (1)
	{
		pid_t pid;

		printf("#cisfun$ ");
		fgets(input, sizeof(input), stdin);
		if (feof(stdin))
		{
			printf("\n");
			break;
		}
		/* Remove the newline character from the input */
		input[strcspn(input, "\n")] = '\0';

		pid = fork();

		if (pid == -1)
		{
			perror("fork");
			exit(EXIT_FAILURE);
		}
		else if (pid == 0)
		{
			/* Child process */
			execlp(input, input, NULL);
			perror(input);
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
