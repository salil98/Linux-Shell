#include "function.h"

int echo(char **args)
{
	if (args[1] == NULL)
	{
		printf("\n");
		return 1;
	}
	int i = 1;
	/* This part takes care if the argument starts with " or '*/
	if (args[i][0] == '\"' || args[i][0] == '\'') // If argument starts with " or '
	{
		int len = strlen(args[i]);
		if (args[i][len - 1] == '\"' || args[i][len - 1] == '\'')
			for (int j = 1; j < len - 1; j++)
				printf("%c", args[i][j]); // If the argument ends with " or '
		else
			for (int j = 1; j < len; j++)
				printf("%c", args[i][j]);
		printf(" "); // space

		i++;

		while (args[i] != NULL)
		{
			int len = strlen(args[i]);
			if (args[i][len - 1] == '\"' || args[i][len - 1] == '\'')
				for (int j = 0; j < len - 1; j++)
					printf("%c", args[i][j]);
			else
				printf("%s ", args[i]);
			i++;
		}
	}

	else
	{
		while (args[i] != NULL)
		{
			if (args[i][0] == '$')
			{

				if (getenv(args[i] + 1) != NULL)
					printf("%s", getenv(args[i] + 1));
				else
					printf(" ");
			}
			else
				printf("%s ", args[i]);
			i++;
		}
	}
	printf("\n");
	return 1;
}
