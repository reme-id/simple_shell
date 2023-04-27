#include "shell.h"

/**
 * shell_env - Print the current environment
 * @args: Arguments
 *
 * Return: Always 0.
 */
int shell_env(char **args)
{
	char **envp = environ;

	while (*envp)
	{
		printf("%s\n", *envp);
		envp++;
	}
	return (0);
}
