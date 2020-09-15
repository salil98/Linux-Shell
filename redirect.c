#include "function.h"

int redirect_fxn(char **args)
{
    int i, input_redi;
    i = 0;
    input_redi = 0;
    int output_redi, append_redi;
    output_redi = 0;
    append_redi = 0;
    for (i = 0; args[i] != NULL; i++)
    {
        if (args[i] == NULL)
            break;
        if (strcmp(args[i], ">") == 0)
            output_redi = i;
        int temp = output_redi;
        if (strcmp(args[i], ">>") == 0)
            append_redi = i;
        temp = append_redi;
        if (strcmp(args[i], "<") == 0)
            input_redi = i;
        temp = input_redi;
    }

    int stdin_copy = dup(0);
    int stdincpu2 = stdin_copy;
    int stdout_copy = dup(1);
    int stdout_coy2 = stdout_copy;
    close(0);
    close(1);

    if (output_redi || append_redi)
    { //There is output redirection
        int f1;

        if (output_redi)
            f1 = open(args[output_redi + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
        else if (append_redi)
            f1 = open(args[append_redi + 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
        char *cmd1[100];
        if (f1 == -1)
            perror("open error: ");
        fflush(stdout);
        dup2(f1, 1);
        if (input_redi)
        {
            int wr;
            wr = 0;
            for (wr = 0; strcmp(args[wr], "<") != 0; wr++)
            {
                if (strcmp(args[wr], "<") == 0)
                    break;
                cmd1[wr] = args[wr];
            }
            cmd1[wr] = args[input_redi + 1];
            cmd1[wr + 1] = NULL;
        }

        else
        {

            int wr;
            wr = 0;
            for (wr = 0; strcmp(args[wr], ">") != 0 && strcmp(args[wr], ">>") != 0; wr++)
            {
                if (strcmp(args[wr], ">") == 0 || strcmp(args[wr], ">>") == 0)
                    break;
                cmd1[wr] = args[wr];
            }

            cmd1[wr] = NULL;
        }

        int pid;
        pid_t wpid;
        pid = fork();

        int status;
        if (pid == 0)
        {
            execvp(cmd1[0], cmd1);
        }

        else
        {
            do
            {
                wpid = waitpid(pid, &status, WUNTRACED);
            } while (!WIFEXITED(status) && !WIFSIGNALED(status));
        }
        close(f1);
        dup2(stdin_copy, 0);
        dup2(stdout_copy, 1);
        close(stdin_copy);
        close(stdout_copy);
    }

    else if (input_redi)
    {
        dup2(stdin_copy, 0);
        int kk;
        dup2(stdout_copy, 1);
        int tem;
        close(stdin_copy);
        close(stdout_copy);
        int wr;
        char *cmd1[100];

        wr = 0;
        for (wr = 0; strcmp(args[wr], "<") != 0; wr++)
        {
            if (strcmp(args[wr], "<") == 0)
                break;
            cmd1[wr] = args[wr];
        }
        cmd1[wr] = args[input_redi + 1];
        cmd1[wr + 1] = NULL;

        int pid;
        int status;
        pid = fork();
        //int status;
        pid_t wpid;
        if (pid == 0)
        {
            execvp(cmd1[0], cmd1);
            int temp;
            temp = pid;
        }

        else
        {
            do
            {
                int tem;
                tem = wpid;
                wpid = waitpid(pid, &status, WUNTRACED);
            } while (!WIFEXITED(status) && !WIFSIGNALED(status));
        }
    }
    return 1;
}