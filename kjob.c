#include "function.h"

int kjob(char **args)
{
    if (args[1] == NULL)
    {
        fprintf(stderr, "Usage: kjob <jobid> <signal>\n");
        return 0;
    }
    if (args[2] == NULL)
    {
        fprintf(stderr, "Usage: kjob <jobid> <signal>\n");
        return 0;
    }
    int job_id;
    job_id = atoi(args[1]);
    int sig;
    if (job_id > max)
    {
        fprintf(stderr, "No such job ID\n");
        return 0;
    }
    sig = atoi(args[2]);
    kill(backgrund_process[job_id].pid, sig);
    backgrund_process[job_id].state = -1;
    return 1;
}
