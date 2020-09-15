#include "function.h"

int pinfo(char **args)
{
	char *pinfo_pid;
	char *cmd1 = (char *)malloc(1024 * sizeof(char));
	if (!cmd1)
		fprintf(stderr, "Memory Allocation error\n");
	char *cmd2 = (char *)malloc(1024 * sizeof(char));
	if (!cmd2)
		fprintf(stderr, "Memory Allocation error\n");
	char *cmd3 = (char *)malloc(1024 * sizeof(char));
	if (!cmd3)
		fprintf(stderr, "Memory Allocation error\n");
	char exec_path[1024];
	char **args1, **args2;
	int curr_pid;
	if (args[1] != NULL)
	{
		curr_pid = atoi(args[1]);
		if (kill(curr_pid, 0))
		{
			fprintf(stderr, "Invalid PID\n");
			return 1;
		}
	}
	else
		curr_pid = getpid(); // As pinfo is not a forked process its pid is same as the parent i.e .out

	printf("pid -- %d\n", curr_pid);
	sprintf(cmd1, "ps -o stat= -p %d", curr_pid);
	args1 = split_line_fxn(cmd1);
	sprintf(cmd2, "ps -o vsz= -p %d", curr_pid);
	args2 = split_line_fxn(cmd2);
	sprintf(cmd3, "/proc/%d/exe", curr_pid);
	printf("Process Status -- ");
	fflush(stdout);
	execute_func(args1);
	printf("Memory -- ");
	fflush(stdout);
	execute_func(args2);
	int p = readlink(cmd3, exec_path, sizeof(exec_path));
	exec_path[p] = '\0';
	printf("Executable Path -- %s\n", exec_path);
	return 1;
}
