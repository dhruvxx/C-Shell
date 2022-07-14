#include "headers.h"
#include "execute.h"

void execute (char * commands) {
    char temp[10000], space[2] = " ";
    strcpy(temp, commands);
    int i = 0;
    char * commandslist[50];
    while (commands) {
        commandslist[i] = commands;
        i++;
        commands = strtok(NULL, space);
    }
    commandslist[i] = NULL;
    if (strstr(commandslist[i - 1], "&")) 
    {
        pid_t PGID = fork();
        if (PGID == 0) {
            setpgid(0, 0);
            if (execvp(commandslist[0], commandslist) == -1) {
                perror("Error");
                return;
            }
            fflush(stdout);
            exit(EXIT_SUCCESS);
        }
        else if (PGID > 0) {
            jobinfo[jobs].pid = PGID;
            strcpy(jobinfo[jobs].name, commandslist[0]);
            jobs = jobs + 1; 
        }
        else {
            perror("Error");
        }
    }
    else {
        pid_t pid;
        int status;
        pid = fork();
        if (pid == 0) 
        {
            if (execvp(commandslist[0], commandslist) < 0) {
                perror("Error");
            }
            exit(EXIT_SUCCESS);
        } 
        else if (pid < 0) {
            perror("Error");
        } 
        else {
            strcpy(running.name, commandslist[0]);
            running.pid = pid;
            waitpid(pid, &status, WUNTRACED);
            fflush(stdout);
        }
    }
}