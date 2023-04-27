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

/**
 * shell_cd - Change the current working directory
 * @args: Arguments
 *
 * Return: Always 1.
 */
int shell_cd(char **args)
{
	char *new_dir;

	if (args[1] == NULL || strcmp(args[1], "~") == 0)
	{
		new_dir = getenv("HOME");
	}
	else if (strcmp(args[1], "-") == 0)
	{
		new_dir = getenv("OLDPWD");
	}
	else
	{
		new_dir = args[1];
	}

	if (chdir(new_dir) != 0)
	{
		perror("cd failed");
		return (1);
	}

	setenv("OLDPWD", getenv("PWD"), 1);
	setenv("PWD", getcwd(NULL, 0), 1);

	return (1);
}
