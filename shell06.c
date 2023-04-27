#include <stdlib.h>
#include <unistd.h>

/**
 * _getline - reads a line from the standard input
 *
 * Return: On success return pointer to line error returns NULL
 */
char *_getline(void)
{
	static char buffer[1024];
	static size_t buffer_pos;
	static ssize_t bytes_read;
	char *line = NULL;
	size_t line_size = 0;

	while (1)
	{
		if (buffer_pos >= bytes_read)
		{
			bytes_read = read(STDIN_FILENO, buffer, sizeof(buffer));
			buffer_pos = 0;

			if (bytes_read == -1)
				return (NULL);
			else if (bytes_read == 0)
				return (line);
		}

		if (line_size == 0)
		{
			line_size = 128;
			line = malloc(line_size);
			if (!line)
				return (NULL);
		}

		if (buffer[buffer_pos] == '\n')
		{
			line[line_size - 1] = '\0';
			return (line);
		}

		line[line_size - 1] = buffer[buffer_pos];
		buffer_pos++;
		line_size++;

		if (line_size >= 2048)
		{
			line_size *= 2;
			char *new_line = realloc(line, line_size);

			if (!new_line)
			{
				free(line);
				return NULL;
			}
			line = new_line;
		}
	}
}
