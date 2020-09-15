#include "function.h"

char *read_line(void)
{
	int bufsize = LSH_RL_BUFSIZE;
	int position = 0, c;
	char *buffer = malloc(sizeof(char) * bufsize);

	if (buffer == NULL)
	{
		fprintf(stderr, "Memory Allocation error\n");
		exit(EXIT_FAILURE);
	}
	else if (buffer != NULL)
	{

		while (1)
		{

			c = getchar(); // Reading a character.

			// If we hit EOF, replace it with a null character and return.
			if (c == EOF || c == '\n')
			{
				buffer[position] = '\0';
				return buffer;
			}
			else
				buffer[position] = c;
			position++;

			if (position >= bufsize)
			{
				bufsize += LSH_RL_BUFSIZE;
				buffer = realloc(buffer, bufsize); // If we have exceeded the buffer, reallocate.
				if (buffer == NULL)
				{
					fprintf(stderr, "Memory Allocation error\n");
					exit(EXIT_FAILURE);
				}
			}
		}
	}
}
