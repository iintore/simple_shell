#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_INPUT_LENGTH 512
#define MAX_ARGUMENTS 20

void removeNewline(char *str)
{
    /* Remove the newline character from the input */
str[strcspn(str, "\n")] = '\0';
}

void searchExecutablePath(char *input, char *cmd_path)
{
char *path = getenv("PATH");
char *path_token = strtok(path, ":");

while (path_token != NULL)
{
strncpy(cmd_path, path_token, MAX_INPUT_LENGTH - 1);
cmd_path[MAX_INPUT_LENGTH - 1] = '\0';  /* Null-terminate the string */
strncat(cmd_path, "/", MAX_INPUT_LENGTH - strlen(cmd_path) - 1);
strncat(cmd_path, input, MAX_INPUT_LENGTH - strlen(cmd_path) - 1);

if (access(cmd_path, X_OK) == 0) {
strcpy(input, cmd_path);
break;
}
path_token = strtok(NULL, ":");
}
}

void executeCommand(char *input, char *arguments[]) {
int argc = 0;
arguments[argc] = strtok(input, " ");  /* Split input into tokens */
while (arguments[argc] != NULL) {
argc++;
arguments[argc] = strtok(NULL, " ");
}
arguments[argc] = NULL;

if (execvp(arguments[0], arguments) == -1) {
perror("Execution error");
exit(EXIT_FAILURE);
}
}

int main(void)
{
int status;
char cmd_path[MAX_INPUT_LENGTH]; /* use a larger buffer size */
char input[MAX_INPUT_LENGTH];
char *arguments[MAX_ARGUMENTS];
pid_t pid;

while (1) {
printf(":) ");
fgets(input, sizeof(input), stdin);

if (feof(stdin)) {
break;  /* Exit on Ctrl+D (EOF) */
}
removeNewline(input);

/* Check if the command is "exit" to exit the shell */
if (strcmp(input, "exit") == 0)
{
printf("Murabeho!\n");  /* Display a farewell message */
break;  /* Exit the shell gracefully */
}

if (access(input, X_OK) == 0) {
            /* If the command is executable within the current directory */
}
else
{
searchExecutablePath(input, cmd_path);
}
pid= fork();  /* Create a child process */

if (pid == -1)
{
perror("Error: Unable to create a child process.");
exit(EXIT_FAILURE);
}
else if (pid == 0)
{
/* Child process */
executeCommand(input, arguments);
}
else
{
/* Parent process */
waitpid(pid, &status, 0);  /* Wait for child process to complete */
}
}
return 0;  /* Return 0 on success */
}
