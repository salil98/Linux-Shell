#include "function.h"

/*
   int unsetenv(const char *name);

   DESCRIPTION
   The unsetenv() function deletes the variable name from the environment.  If name does not exist in the environment, then  the  func‐
   tion succeeds, and the environment is unchanged.

   The unsetenv() function returns zero on success, or -1 on error, with errno set to indicate the cause of the error.

 */

int unset_env(char **args)
{

	if (args[1] == NULL)
	{
		fprintf(stderr, "Usage: unsetenv <varible>\n");
		return 1;
	}
	if (args[3] != NULL)
	{
		fprintf(stderr, "%s\n", "Usage:unsetenv <varible> ");
		return 1;
	}
	if (unsetenv(args[1]) != 0)
		perror("Error: ");

	return 1;
}
