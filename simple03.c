#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

int execute_command(char **args);

/**
 * main - Simple UNIX command interpreter
 *
 * Return: Always 0
 */
int main(void)
{
	char *line = NULL;
	char *args[1024];
	size_t bufsize = 0;
	ssize_t nread;
	int status;

	while (1)
	{
		printf("$ ");
		nread = getline(&line, &bufsize, stdin);

		if (nread == -1)
		{
			putchar('\n');
			break;
		}

		args[0] = strtok(line, " \n");
		if (args[0] == NULL)
			continue;

		int i = 1;

		while ((args[i] = strtok(NULL, " \n")) != NULL)
			i++;
		args[i] = NULL;

		status = execute_command(args);
		if (status == 2)
			printf("Error: command not found\n");
		else if (status == 3)
			printf("Error: could not create child process\n");
	}

	free(line);

	return (0);
}

/**
 * execute_command - Execute a command with arguments
 * @args: The command and arguments
 *
 * Return: 0 success, 1 on failure, 2 on not found, 3 on error
 */

int execute_command(char **args)
{
	pid_t pid;
	int status;
	char *cmd;
	char *path = getenv("PATH");
	char *dir;
	char *token;

	if (path == NULL)
		return (2);

	token = strtok(path, ":");
	while (token != NULL)
	{
		dir = malloc(strlen(token) + strlen(args[0]) + 2);
		sprintf(dir, "%s/%s", token, args[0]);
		if (access(dir, F_OK) == 0)
		{
			cmd = dir;
			break;
		}
		free(dir);
		token = strtok(NULL, ":");
	}

	if (cmd == NULL)
		return (2);

	pid = fork();
	if (pid == -1)
	{
		free(cmd);
		return (3);
	}
	else if (pid == 0)
	{
		execve(cmd, args, environ);
		_exit(EXIT_FAILURE);
	}
	else
	{
		do {
			waitpid(pid, &status, WUNTRACED);
		} while (!WIFEXITED(status) && !WIFSIGNALED(status));
	}

	free(cmd);

	return (0);
}
