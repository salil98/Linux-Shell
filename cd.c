#include "function.h"

int cd(char **args)
{
	char current_working_directory[1024];
	getcwd(current_working_directory, sizeof(current_working_directory));
	int x = 0;

	if (args[1] == NULL)
	{
		strcpy(previous, current_working_directory);
		x = chdir(home); //
		return 1;
	}
	else if ((strcmp(args[1], "~") == 0) || (strcmp(args[1], "~/") == 0))
	{
		strcpy(previous, current_working_directory);
		x = chdir(home);
		return 1;
	}
	else if ((strcmp(args[1], "-")) == 0)
	{
		x = chdir(previous);
		printf("%s\n", previous);
		strcpy(previous, current_working_directory);
		return 1;
	}
	strcpy(previous, current_working_directory);
	x = chdir(args[1]);
	if (x < 0)
		perror("Error: ");
	background_fxn();
	return 1;
}
