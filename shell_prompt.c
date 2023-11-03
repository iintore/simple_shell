#include <stdio.h>
#include <stdlib.h>
/**
 * main - prompts $ to the terminal
 * @td: user input
 * @argv: commandline argument
 * Return: Always (0)
 */

int main(int td, char **argv)
{
	 char *prompt = "$ ";
	 char *l_ptr;
	 size_t n = 0;
	(void)td;
	(void)argv;
	printf("%s", prompt);
	getline(&l_ptr, &n, stdin);
	printf("%s\n", l_ptr);
	free(l_ptr);
	return (0);
}
