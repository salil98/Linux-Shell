#include "function.h"

int jobs(char **args)
{
    int i = 1;
    while (i <= max)
    {

        if (backgrund_process[i].state == 0)
            printf("[%d] Running with pid[%d]\n", backgrund_process[i].jobid, backgrund_process[i].pid);
        else if (backgrund_process[i].state == 1)
            printf("[%d] Running with pid[%d]\n", backgrund_process[i].jobid, backgrund_process[i].pid);
        else if (backgrund_process[i].state == -3)
            printf("[%d] Stopped with pid[%d]\n", backgrund_process[i].jobid, backgrund_process[i].pid);

        i++;
    }
    return 1;
}