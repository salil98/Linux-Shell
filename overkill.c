#include "function.h"

int overkill(char **args)
{
    int i;
    i = 1;
    while (i <= max)
    {
        int temm;
        temm = backgrund_process[i].state;
        if (temm == 0)
        {
            int temm1;
            temm1 = backgrund_process[i].pid;
            kill(temm1, 15);
            backgrund_process[i].state = -2;
        }
        else if (temm == -3)
        {
            int temm1;
            temm1 = backgrund_process[i].pid;
            kill(temm1, 15);
            backgrund_process[i].state = -2;
        }
        i++;
    }
    max = 0;
    return 1;
}
