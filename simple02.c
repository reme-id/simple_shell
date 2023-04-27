#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#define BUFFER_SIZE 1024

int main(void)
{
	char *args[100];
	char buffer[BUFFER_SIZE];
	int status, i;

	while (1)
	{
		printf("$ ");
		if (!fgets(buffer, BUFFER_SIZE, stdin))
			break;

		if (buffer[0] == '\n')

			continue;

		int arg_count = 0;

		args[arg_count] = strtok(buffer, " \n");
		while (args[arg_count] != NULL)
		{
			arg_count++;
			args[arg_count] = strtok(NULL, " \n");
		}
		args[arg_count] = NULL;
		pid_t pid = fork();

		if (pid == 0)
		{
			if (execvp(args[0], args) == -1)
				perror("Error");
			exit(EXIT_FAILURE);
		} else if (pid < 0)
		{
			perror("Error");
		} else
		{
			waitpid(pid, &status, 0);
		}
	}
	return (0);
}
