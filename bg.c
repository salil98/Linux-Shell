#include "function.h"

int bg(char **args)
{
    if (args[1] == NULL)
    {
        fprintf(stderr, "Usage: bg <jobid>\n");
        return 0;
    }

    pid_t wpid;
    int jo_id = atoi(args[1]);
    if (backgrund_process[jo_id].state == -3)
    {
        if (kill(backgrund_process[jo_id].pid, 25))
        {
            perror("");
        }
        else
        {
            backgrund_process[jo_id].state = 0;
            perror("");
        }
    }
}