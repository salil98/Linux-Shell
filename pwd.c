#include "function.h"

int pwd(char **args)
{
	size_t size = 1024;

	while (1)
	{
		char *buffer = (char *)malloc(size);

		if (buffer != NULL)
		{
			if (getcwd(buffer, size) == buffer)
			/*  
		The getcwd() function copies an absolute pathname of the current working directory to the array 
		pointed  to  by  cwd(here in our case buffer). On  success,  it returns  a pointer to a string containing the pathname of 
		the current working directory. On failure, these functions return NULL.
	*/
			{
				printf("%s\n", buffer);
				free(buffer);
				return 1;
			}

			else if (errno == ERANGE)
			{
				size *= 2;
				free(buffer);
			}
		}

		else if (buffer == NULL)
		{
			fprintf(stderr, "Memory Allocation error\n");
			exit(EXIT_FAILURE);
		}
	}
	return 1;
}
char *Get_Current_Directory(char **args)
{
	size_t size = 1024;

	while (1)
	{
		char *buffer = (char *)malloc(size);

		if (buffer != NULL)
		{
			if (getcwd(buffer, size) == buffer)
			/*  
		The getcwd() function copies an absolute pathname of the current working directory to the array 
		pointed  to  by  cwd(here in our case buffer). On  success,  it returns  a pointer to a string containing the pathname of 
		the current working directory. On failure, these functions return NULL.
	*/
			{
				return buffer;
				free(buffer);
			}

			else if (errno == ERANGE)
			{
				size *= 2;
				free(buffer);
			}
		}

		else if (buffer == NULL)
		{
			fprintf(stderr, "Memory Allocation error\n");
			exit(EXIT_FAILURE);
		}
	}
}
