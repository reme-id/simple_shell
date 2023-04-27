#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define BUFFER_SIZE 1024

/**
 * main - Entry point
 *
 * Return: Always 0 (Success)
 */
int main(void)
{
	char *buffer = NULL;
	size_t bufsize = BUFFER_SIZE;
	ssize_t nread;
	char *args[2];

	while (1)
	{
		buffer = (char *)malloc(bufsize * sizeof(char));
		if (buffer == NULL)
		{
			perror("malloc");
			exit(EXIT_FAILURE);
		}


		printf("$ ");
		nread = getline(&buffer, &bufsize, stdin);
		if (nread == -1)
		{
			printf("\n");
			free(buffer);
			exit(EXIT_SUCCESS);
		}

		args[0] = buffer;
		args[1] = NULL;

		if (execve(args[0], args, NULL) == -1)

			perror("execve");

		free(buffer);
	}

	return (0);
}
