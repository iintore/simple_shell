#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_INPUT_LENGTH 100
#define MAX_ARGUMENTS 20

void executeCommand(char *input);

/**
 * main - Simple Shell 0.3
 *
 * Description:
 * This is a basic shell that handles command lines with arguments,
 * includes PATH support, and avoids forking if the command doesn't exist.
 *
 * Return: 0 on success, -1 on error.
 */
int main(void)
{
	char input[MAX_INPUT_LENGTH];

	while (1)
	{
		printf(":) ");
		fgets(input, sizeof(input), stdin);
		if (feof(stdin))
		{
			break;
		}
		input[strcspn(input, "\n")] = '\0';
		executeCommand(input);
	}
	return (0);
}
/**
 * executeCommand - Execute the particular command
 * @input: The command to be executed
 *
 * Description:
 * This function takes a command as input, checks if it exists in the PATH,
 * and then forks a process to execute the command.
 */
void executeCommand(char *input)
{
	char *arguments[MAX_ARGUMENTS];
	int argc = 0;
	char *path = getenv("PATH");
	char *command = strtok(input, " ");
	pid_t pid;

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
	pid = fork();

	if (pid == -1)
	{
		perror("Error: Unable to create a child process.");
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		argc = 0;
		arguments[argc] = strtok(input, " ");
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
		int status;

		wait(&status);
	}
}
