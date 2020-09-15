#include "function.h"

int sigpid;

char *builtin_str[] = {"cd", "pwd", "echo", "ls", "pinfo", "clock", "setenv", "unsetenv", "jobs", "overkill", "kjob", "fg", "bg"};

int (*builtin_func[])(char **) =
	{
		&cd, &pwd, &echo, &ls, &pinfo, &fclock, &set_env, &unset_env, &jobs, &overkill, &kjob, &fg, &bg};

int num_builtins()
{
	return sizeof(builtin_str) / sizeof(char *);
}
char cntt[100];

void back_process(int pid, char *str)
{
	backgrund_process[++max].pid = pid;
	backgrund_process[max].command = str;
	backgrund_process[max].jobid = max;
	backgrund_process[max].state = 0;
	printf("The process %s with pid %d has started in the background\n", str, pid);
	printf("[%d] %d\n", backgrund_process[max].jobid, pid);
	return;
}
void SIGINT_handler(int signal_num)
{
	int k = 0;
	if (sigpid)
	{
		if (kill(sigpid, SIGINT))
		{
			return;
		}
		k = 1;
	}
	if (!k)
	{
		signal(signal_num, SIG_IGN); // The signal is ignored.
		printf("\n");
		print_prompt();
		fflush(stdout);
		signal(signal_num, SIGINT_handler);
	}
}

void SIGTSTP_handler(int signal_num)
{
	int k = 0;

	if (sigpid)
	{
		if (kill(sigpid, SIGTSTP) == 0)
		{
			backgrund_process[++max].pid = sigpid;
			backgrund_process[max].command = cntt;
			backgrund_process[max].jobid = max;
			backgrund_process[max].state = -3;
			printf("[%d] Stopped %s[%d]\n", backgrund_process[max].jobid, backgrund_process[max].command, backgrund_process[max].pid);
			loop();

			return;
		}
		k = 1;
	}
	else
	{
		printf("\n");
		print_prompt();
	}
	if (!k)
	{

		signal(signal_num, SIG_IGN);		 // The signal is ignored.
		fflush(stdout);						 // Flushes the output
		signal(signal_num, SIGTSTP_handler); //Again it checks for signal
	}
}

void background_fxn()
{
	pid_t wpid;
	int status, i;
	char pidnumber[1000];

	while ((wpid = waitpid(-1, &status, WNOHANG)) > 0) // Checks for the child processes which have changed there status.
	{
		if (WIFEXITED(status) == 0)
		//returns true if the child terminated normally, that is, by calling exit(3) or _exit(2), or by returning from main().
		{
			for (i = 1; i <= max; i++)
			{
				if (backgrund_process[i].pid == wpid)
				{
					printf("[%d]+	Done with pid %d\n", backgrund_process[i].jobid, wpid);
					backgrund_process[i].state = -1;
				}
			}
			loop();
		}

		if (WIFSIGNALED(status) == 0)
		//returns true if the child process was terminated by a signal.
		{
			for (i = 1; i <= max; i++)
			{
				if (backgrund_process[i].pid == wpid)
				{
					printf("[%d]+	Done with pid %d\n", backgrund_process[i].jobid, wpid);
					backgrund_process[i].state = -1;
				}
			}
			loop();
		}
	}
	return;
}

//  Checks if the child process to be started is a foreground process or background process and executs accordingly
void child_process(char **args)
{
	pid_t pid;
	pid_t wpid;
	int status, i, x;
	i = 0;
	x = 0;

	for (i = 0; args[i] != NULL; i++)
	{
		if (strcmp(args[i], "&") == 0)
		{
			args[i] = NULL;
			x = 1;
			break;
		}
	}

	if (strcmp(args[0], "cd") == 0 || strcmp(args[0], "pinfo") == 0 || strcmp(args[0], "setenv") == 0 || strcmp(args[0], "unsetenv") == 0 || strcmp(args[0], "fg") == 0)
	{
		i = 0;
		while (i < num_builtins())
		{
			if (strcmp(args[0], builtin_str[i]) == 0)
			{
				(*builtin_func[i])(args);
				background_fxn();
				return;
			}
			i++;
		}
	}
	else
	{

		pid = fork();
		if (pid < 0)
			fprintf(stderr, "Error forking\n");
		else if (pid == 0)
		{
			for (i = 0; i < num_builtins(); i++)
			{
				if (strcmp(args[0], builtin_str[i]) == 0)
				{
					(*builtin_func[i])(args);
					background_fxn();
					exit(0);
				}
			}

			if (x == 1)
				exit(EXIT_SUCCESS);
		}
		else
		{
			if (x == 1)
			{
				back_process(pid, args[0]);
			}

			else //If process is a foreground process
			{
				do
				{
					wpid = waitpid(pid, &status, WUNTRACED);
				} while (!WIFEXITED(status) && !WIFSIGNALED(status));
			}
			background_fxn();
		}
	}
}

int launch_func(char **args)
{
	pid_t pid;
	int status, i, x;
	i = 0;
	pid_t wpid;

	x = 0;
	for (i = 0; args[i] != NULL; i++)
	{
		if (args[i] == NULL)
			break;
		if (strcmp(args[i], "&") == 0)
		{
			args[i] = NULL;
			x = 1;
			break;
		}
	}
	pid = fork();
	if (pid < 0)
		fprintf(stderr, "Error forking\n");
	else if (pid == 0)
	{

		if (execvp(args[0], args) == -1)
			fprintf(stderr, "%s : Command not Found\n", args[0]);
		else
			exit(EXIT_SUCCESS);
	}
	else
	{
		if (x == 1)
		{
			back_process(pid, args[0]);
		}
		else
		{
			sigpid = pid;
			do
			{
				wpid = waitpid(pid, &status, WUNTRACED);
			} while (!WIFEXITED(status) && !WIFSIGNALED(status));
			sigpid = 0;
			strcpy(cntt, args[0]);
		}
		background_fxn();
	}
	return 1;
}

int execute_func(char **args)
{
	if (args[0] == NULL)
		return 1;
	int i;
	i = 0;
	int pipe_flag = 0;
	for (i = 0; args[i] != NULL; i++)
	{
		if (args[i] == NULL)
			break;
		if (strcmp(args[i], "|") == 0)
			pipe_flag = 1;
	}
	i = 0;
	int redirect_flag = 0;
	for (i = 0; args[i] != NULL; i++)
	{
		if (args[i] == NULL)
			break;
		if ((strcmp(args[i], ">") == 0) || (strcmp(args[i], "<") == 0) || (strcmp(args[i], ">>") == 0))
		{
			redirect_flag = 1;
		}
	}

	if (pipe_flag)
	{
		pipe_fxn(args);
		return 1;
	}
	if (redirect_flag)
	{
		redirect_fxn(args);
		return 1;
	}

	for (int i = 0; i < num_builtins(); i++)
	{
		if (strcmp(args[0], builtin_str[i]) == 0)
		{
			child_process(args);
			return 1;
		}
		else if (strcmp(args[0], "quit") == 0)
			exit(0);
	}
	return launch_func(args);
}
