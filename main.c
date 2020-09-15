#include "function.h"

int print_prompt()
{

	char hostname[1024];
	gethostname(hostname, 1024);				 // GETTING HOSTNAME
	char *Current_Dir = Get_Current_Directory(); // GETTING ABSOLUTE PATH OF CURRENT DIRECTORY
	char *path;
	int Current_Dir_Size = strlen(Current_Dir);
	int Home_Dir_Size = strlen(home);
	// IF SIZE OF CURRENT DIRECTORY IS GREATER THAN OR EQUAL TO HOME DIRECTORY SIZE THEN PATH
	// WILL BE RELATIVE TO HOME ELSE IT WILL BE ABSOLUTE
	if (Current_Dir_Size >= Home_Dir_Size)
		path = (Home_Dir_Size + Current_Dir);
	else
		path = Current_Dir;

	printf("<%s@%s:~%s> ", getenv("USER"), hostname, path);
	return 1;
}
void loop()
{
	while (1)
	{
		print_prompt();

		int j = 0;
		int k = 0;
		char **args;
		char *line = read_line();
		if (feof(stdin))
		{
			printf("Ctrl+ D\n");
			fflush(stdout);
			fflush(stderr);
			exit(0);
		}

		args = split_cmd_fxn(line);
		while (args[j])
		{
			char **args2 = split_line_fxn(args[j]);
			j++;
			k = execute_func(args2);
		}
		free(line);
		free(args);
	}
}

int main()
{
	if (signal(SIGINT, SIGINT_handler) == SIG_ERR)
	{
		printf("SIGINT install error\n");
		exit(1);
	}

	signal(SIGTSTP, SIGTSTP_handler);
	getcwd(home, sizeof(home));
	strcpy(previous, home);
	loop();
	return 0;
}
