#include "function.h"
/*
   int setenv(const char *name, const char *value, int overwrite);

   DESCRIPTION
   The  setenv() function adds the variable name to the environment with the value value, if name does not already exist.  If name does
   exist in the environment, then its value is changed to value if overwrite is nonzero; if overwrite is zero, then the value  of  name
   is  not changed (and setenv() returns a success status).  This function makes copies of the strings pointed to by name and value (by
   contrast with putenv(3)).*/

int set_env(char **args)
{

	if (args[1] == NULL)
	{

		fprintf(stderr, "%s\n", "Usage: setenv <varible> <value>");
		return 1;
	}
	if (args[3] != NULL)
	{ // If more than 2 command-line arguments are passed.(Then error).
		fprintf(stderr, "%s\n", "Usage: setenv <varible> <value>[AT MAX 2 COMMAND-LINE ARGUMENTS ARE ALLOWED]");
		return 1;
	}
	if (getenv(args[1]) == NULL) // Creating the environment variable if it is not present.
		setenv(args[1], "", 1);

	if (args[2] == NULL)
		setenv(args[1], "", 1);
	else
		setenv(args[1], args[2], 1);

	return 1;
}
