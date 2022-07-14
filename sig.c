#include "headers.h"
#include "sig.h"

void sig (char * command) {
    char space[2] = " ";
    int signal;
    pid_t pid;
    if (strtok(NULL, space)) {
        pid = atoi(command);
    }
    else {
        printf("No process ID given\n");
        return;
    }
    if (strtok(NULL, space)) {
        signal = atoi(command);
    }
    else {
        printf("No kill signal given\n");
        return;
    }
    kill(pid, signal);
    for (int i = 0; i < jobs; i++) 
    {
        if (jobinfo[i].pid == pid) {
            jobinfo[i].pid = 0;
            jobinfo[i].name[0] = '\0';
            if (i >= 0) {
                for (long long k = i; k < jobs - 1; k++) {
                    jobinfo[k].pid = jobinfo[k + 1].pid;
                    strcpy(jobinfo[k].name, jobinfo[k + 1].name);
                }
            jobs--;
            }
            else {
                perror("Error");
            }
            break;
        }
    }
}