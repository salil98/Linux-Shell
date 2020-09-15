#include "function.h"

char **split_cmd_fxn(char *line)
{
	int buffer_size = TOKEN_BUFFER_SIZE;
	int pos = 0;
	char **token_storage = malloc(buffer_size * sizeof(char *));
	char *token;
	char *saveptr1;

	if (token_storage == NULL)
	{
		fprintf(stderr, "Memory Allocation error\n");
		exit(EXIT_FAILURE);
	}

	token = strtok(line, CMD_DELIM);
	while (token != NULL)
	{
		token_storage[pos] = token;
		pos++;

		if (pos >= buffer_size)
		{
			buffer_size += TOKEN_BUFFER_SIZE;
			token_storage = realloc(token_storage, buffer_size * sizeof(char *));
			if (token_storage == NULL)
			{
				fprintf(stderr, "Memory Allocation error\n");
				exit(EXIT_FAILURE);
			}
		}

		token = strtok(NULL, CMD_DELIM);
	}

	token_storage[pos] = NULL;
	return token_storage;
}
char **split_pipe_fxn(char *line)
{
	int buffer_size = TOKEN_BUFFER_SIZE;
	int pos = 0;
	char **token_storage = malloc(buffer_size * sizeof(char *));
	char *token;
	char *saveptr1;

	if (token_storage == NULL)
	{
		fprintf(stderr, "Memory Allocation error\n");
		exit(EXIT_FAILURE);
	}

	token = strtok(line, "|");
	while (token != NULL)
	{
		token_storage[pos] = token;
		pos++;

		if (pos >= buffer_size)
		{
			buffer_size += TOKEN_BUFFER_SIZE;
			token_storage = realloc(token_storage, buffer_size * sizeof(char *));
			if (token_storage == NULL)
			{
				fprintf(stderr, "Memory Allocation error\n");
				exit(EXIT_FAILURE);
			}
		}

		token = strtok(NULL, "|");
	}

	token_storage[pos] = NULL;
	return token_storage;
}

//Used to separate arguments of a particluar command
char **split_line_fxn(char *line)
{
	int buffer_size = TOKEN_BUFFER_SIZE;
	int pos = 0;
	char **token_storage = malloc(buffer_size * sizeof(char *));
	char *token;
	char *saveptr1;

	if (token_storage == NULL)
	{
		fprintf(stderr, "Memory Allocation error\n");
		exit(EXIT_FAILURE);
	}

	token = strtok(line, TOKEN_DELIM);
	while (token != NULL)
	{
		token_storage[pos] = token;
		pos++;

		if (pos >= buffer_size)
		{
			buffer_size += TOKEN_BUFFER_SIZE;
			token_storage = realloc(token_storage, buffer_size * sizeof(char *));
			if (token_storage == NULL)
			{
				fprintf(stderr, "Memory Allocation error\n");
				exit(EXIT_FAILURE);
			}
		}

		token = strtok(NULL, TOKEN_DELIM);
	}

	token_storage[pos] = NULL;
	return token_storage;
}
