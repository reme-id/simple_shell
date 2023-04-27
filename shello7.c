#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

#define BUFFER_SIZE 1024

int main(void)
{
	char args[100][BUFFER_SIZE];
	char buffer[BUFFER_SIZE];
	int status, i;

	while (1)
	{
		printf("$ ");
		if (!fgets(buffer, BUFFER_SIZE, stdin))
		{
			break;
		}
		if (buffer[0] == '\n')
		{
			continue;
		}
		int arg_count = 0;
		int buffer_i = 0;
		while (buffer_i < BUFFER_SIZE && buffer[buffer_i] != '\n') 
		{
			while (buffer[buffer_i] == ' ' || buffer[buffer_i] == '\t')
			{
				buffer_i++;
			}
		if (buffer[buffer_i] != '\n' && buffer[buffer_i] != '\0')
		{
			int arg_i = 0;
				while (buffer[buffer_i] != ' ' && buffer[buffer_i] != '\t' && buffer[buffer_i] != '\n' && buffer[buffer_i] != '\0')
				{
					args[arg_count][arg_i] = buffer[buffer_i];
					arg_i++;
					buffer_i++;
				}
				args[arg_count][arg_i] = '\0';
				arg_count++;
			}
		}
		args[arg_count][0] = '\0';
		pid_t pid = fork();
		if (pid == 0) {
			if (execvp(args[0], args) == -1)
		{
			perror("Error");
		}
		exit(EXIT_FAILURE);
		}
		else if (pid < 0)
		{
			perror("Error");
		}
		else
		{
			waitpid(pid, &status, 0);
		}
	}
	return 0;
}
