#include "function.h"
int fg(char **args)
{

    if (args[1] == NULL)
    {
        fprintf(stderr, "Usage: fg <jobid>\n");
        return 0;
    }
    pid_t wpid;
    int job_id = atoi(args[1]);
    printf("PID[%d]\n", backgrund_process[job_id].pid);
    int status;
    if (backgrund_process[job_id].state == 0)
        backgrund_process[job_id].state = 1;
    else if (backgrund_process[job_id].state == -3)
    {
        kill(backgrund_process[job_id].pid, SIGCONT);
        backgrund_process[job_id].state = -1;
    }

    do
    {
        wpid = waitpid(backgrund_process[job_id].pid, &status, WUNTRACED);
    } while (!WIFEXITED(status) && !WIFSIGNALED(status) && !WIFSTOPPED(status));

    return 1;
}