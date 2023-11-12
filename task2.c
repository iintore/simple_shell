#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_INPUT_LENGTH 100
#define MAX_ARGUMENTS 20

void displayPrompt(void);
void getInput(char *input);
void parseInput(char *input, char **arguments, int *argc);
void executeCommand(char **arguments);

/**
 * main - accepts and processes in puts
 * Return: int
 */
int main(void)
{
char input[MAX_INPUT_LENGTH];
char *arguments[MAX_ARGUMENTS];
int argc;

while (1)
{
displayPrompt();
getInput(input);

if (feof(stdin))
printf("\n");
break; /* Exit on Ctrl+D (EOF) */
}

input[strcspn(input, "\n")] = '\0';

pid_t pid = fork();

if (pid == -1)
{
perror("fork");
exit(EXIT_FAILURE);
}
else if (pid == 0)
{
/* Child process */
argc = 0;
parseInput(input, arguments, &argc);
executeCommand(arguments);
}
else
{
/* Parent process */
int status;
wait(&status);
}
return (0);
}

/**
 * displayPrompt - displays shell $
 * Return: northing
 */
void displayPrompt(void)
{
printf("shell$ ");
}

/**
 * getInput - accepts user commands
 * @input: user inputs
 * Return: northing
 */
void getInput(char *input)
{
fgets(input, sizeof(input), stdin);
}

/**
 * parseInput - shell parsing
 * @input: user input
 * @arguments: user args
 * @argc: shell arguments
 * Return: no return
 */
void parseInput(char *input, char **arguments, int *argc)
{
*argc = 0;
arguments[*argc] = strtok(input, " ");

while (arguments[*argc] != NULL)
{
(*argc)++;
arguments[*argc] = strtok(NULL, " ");
}

arguments[*argc] = NULL;
}

/**
 * executeCommand - find and execute executable files
 * @arguments: user executable commands
 * Return: Execurion
 */
void executeCommand(char **arguments)
{
execvp(arguments[0], arguments);
perror(arguments[0]);
exit(EXIT_FAILURE);
}
