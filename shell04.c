#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

#define BUFFER_SIZE 1024

void prompt(void);
int execute(char **args);

int main(void)
{
	char *buffer;
	size_t bufsize = BUFFER_SIZE;
	char **args;
	int status;

	buffer = (char *)malloc(bufsize * sizeof(char));
	if (buffer == NULL)
	{
		perror("malloc failed");
		exit(EXIT_FAILURE);
	}

	do     {
		prompt();

		if (getline(&buffer, &bufsize, stdin) == -1)
		{
			printf("\n");
			break;
		}

		args = malloc(sizeof(char *) * BUFFER_SIZE);
		if (args == NULL)
		{
			perror("malloc failed");
			exit(EXIT_FAILURE);
		}

		char *token = strtok(buffer, " \n");
		int i = 0;

		while (token != NULL)
		{
			args[i++] = token;
			token = strtok(NULL, " \n");
		}
		args[i] = NULL;

		if (strcmp(args[0], "exit") == 0)
		{
			exit(EXIT_SUCCESS);
		}

		status = execute(args);

		free(args);
	} while (status);

	free(buffer);

	return (EXIT_SUCCESS);
}

void prompt(void)
{
	printf("$ ");
}

int execute(char **args)
{
	pid_t pid;
	int status;

	pid = fork();
	if (pid == -1)
	{
		perror("fork failed");
		exit(EXIT_FAILURE);
	} else if (pid == 0)
	{
		if (execvp(args[0], args) == -1)
		{
			printf("%s: command not found\n", args[0]);
			exit(EXIT_FAILURE);
		}
	} else
	{
		do {
			waitpid(pid, &status, WUNTRACED);
		} while (!WIFEXITED(status) && !WIFSIGNALED(status));
	}

	return (1);
}
