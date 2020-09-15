#include "function.h"

int pipe_fxn(char **args)
{
	int i;
	i = 0;
	int k;
	k = 0;
	int noofcmd = 0;
	char cmd[1111];
	int wpid;
	int stdin_copy = dup(0);
	int stdout_copy = dup(1);
	int status;

	int piid = fork();
	if (piid == 0)
	{
		while (args[i])
		{
			while (args[i])
			{
				if (strcmp(args[i], "|") == 0)
					break;
				int n;
				int j;
				j = 0;
				int ttt;

				n = strlen(args[i]);
				ttt = 0;
				while (j < n)
				{
					cmd[k++] = args[i][j];
					j++;
					ttt++;
				}

				cmd[k++] = ' ';
				i++;
			}
			int tttt = i + 1;
			if (args[tttt])
				cmd[k++] = '|';

			i++;
		}
		cmd[k] = '\0';
		i = 0;
		char **pipargs = split_pipe_fxn(cmd);
		char **args2;
		while (pipargs[i])
			i++;
		noofcmd = i;
		i = 0;

		while (pipargs[i] && i < noofcmd - 1)
		{
			args2 = split_line_fxn(pipargs[i]);
			int g;
			int flag1;
			g = 0;
			flag1 = 0;
			int flag2, flag3;
			flag3 = 0;
			flag2 = 0;
			for (g = 0; args2[g] != NULL; g++)
			{
				if (args2[g] == NULL)
					break;
				if (strcmp(args2[g], "<") == 0)
					flag1 = g;
				if (strcmp(args2[g], ">") == 0)
					flag2 = g;
				if (strcmp(args2[g], ">>") == 0)
					flag3 = g;
			}

			if (flag2 || flag3)
			{
				int in;
				in = open(args2[flag1 + 1], O_RDONLY);
				dup2(in, STDIN_FILENO);
				close(in);
				return 1;
			}
			else
			{
				int pd[2];
				pipe(pd);
				int pid;
				pid = fork();
				if (pid == 0)
				{
					dup2(pd[1], 1);
					if (!flag1)
					{
						execvp(args2[0], args2);
					}
					else
					{
						if (execlp(args2[0], args2[0], args2[2], NULL) == -1)
							kill(getpid(), SIGTERM);
					}
				}
				dup2(pd[0], 0);
				close(pd[1]);
			}
			i++;
		}
		args2 = split_line_fxn(pipargs[i]);
		int flag1, g;
		g = 0;
		int flag2, flag3;
		flag2 = 0;
		flag3 = 0;
		flag1 = 0;

		while (args2[i] != NULL)
		{
			if (strcmp(args2[i], ">") == 0)
				flag2 = i;
			if (strcmp(args2[i], ">>") == 0)
				flag3 = i;
			i++;
		}

		if (flag2 || flag3)
		{
			int f1;
			if (flag2)
				g = flag2;
			else
				g = flag3;
			int wr;
			if (flag3)
				f1 = open(args2[g + 1], O_WRONLY | O_CREAT | O_APPEND, 0644);

			else if (flag2)
				f1 = open(args2[g + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);

			char *cmd1[6];
			wr = 0;
			for (wr = 0; strcmp(args2[wr], ">") != 0 && strcmp(args2[wr], ">>") != 0; wr++)
			{
				if (strcmp(args2[wr], ">") == 0 || strcmp(args2[wr], ">>") == 0)
					break;
				cmd1[wr] = args2[wr];
			}
			cmd1[wr] = NULL;

			close(1);
			dup2(f1, 1);
			int pid;
			pid_t wpid;
			pid = fork();
			int status;
			if (pid == 0)
				if (execvp(cmd1[0], cmd1) == -1)
					kill(getpid(), SIGTERM);

				else
				{
					do
					{
						wpid = waitpid(pid, &status, WUNTRACED);
					} while (!WIFEXITED(status) && !WIFSIGNALED(status));
				}
			close(f1);
		}
		else
		{
			if (execvp(args2[0], args2) != -1)
			{
				int tempp;
				tempp = status;
			}
			if (execvp(args2[0], args2) == -1)
			{
				int ccc;
				kill(getpid(), SIGTERM);
				ccc = status;
			}
		}
		exit(0);
	}
	else
	{

		do
		{
			wpid = waitpid(piid, &status, WUNTRACED);
		} while (!WIFEXITED(status) && !WIFSIGNALED(status));
	}
	dup2(stdin_copy, 0);
	dup2(stdout_copy, 1);
	close(stdin_copy);
	close(stdout_copy);
	return 1;
}
