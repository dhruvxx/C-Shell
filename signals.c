#include "headers.h"
#include "signals.h"

void back (char * command) {
    command = strtok(NULL, " ");
    pid_t pid;
    if (command == NULL) {
        printf("No job number given\n");
    }
    else {
        pid = atoi(command);
        if (pid > jobs || pid < 1) {
            printf("Invalid job number\n");
        }
        else {
            kill(jobinfo[pid - 1].pid, SIGTTIN);
            kill(jobinfo[pid - 1].pid, SIGCONT);
            running.pid = processid;
            strcpy(running.name, "shell");
        }
    }
    return;
}

void fore (char * command) {
    command = strtok(NULL, " ");
    pid_t pid;
    if (command == NULL) {
        printf("No job number given\n");
    }
    else {
        pid = atoi(command);
        if (pid > jobs || pid < 1) {
            printf("Invalid job number\n");
        }
        else {
            signal(SIGTTIN, SIG_IGN);
            signal(SIGTTOU,SIG_IGN);
            tcsetpgrp(STDIN_FILENO, jobinfo[pid - 1].pid);
            strcpy(running.name, jobinfo[pid - 1].name);
            running.pid = jobinfo[pid - 1].pid;
            kill(jobinfo[pid - 1].pid, SIGCONT);
            int k = pid - 1;;
            jobs--;
            for (int i = k; i < jobs; i++) {
                jobinfo[i].pid = jobinfo[i + 1].pid;
                strcpy(jobinfo[i].name, jobinfo[i + 1].name);
            }
            waitpid(-1, NULL, WUNTRACED);
            signal(SIGTSTP, ctrlz);
            tcsetpgrp(STDIN_FILENO,getpgrp());
            signal(SIGTTIN,SIG_DFL);
            signal(SIGTTOU,SIG_DFL);
        }
    }
}

void ctrlz () {
    pid_t PID = running.pid;
    if (PID == processid) {
        signal(SIGTSTP, ctrlz);
        printf("\n");
        size_t size = 10000;
        char host[size], user[size];
        gethostname(host, size);
        getlogin_r(user, size);
        long long int i;
        size_t size = 1000000, currentdirsize, inputsize, homedirsize = strlen(hdn);
        char currentdir[size], dirname[size];
        getcwd(currentdir, size);
        currentdirsize = strlen(currentdir);
        if (strstr(currentdir, hdn)) {
            strcpy(dirname, "~");
            for (i = homedirsize; i < currentdirsize; i++) {
                dirname[i - homedirsize + 1] = currentdir[i];
                
            }
            dirname[i - homedirsize + 1] = '\0';
        }
        else {
            strcpy(dirname, currentdir);
        }
        printf("\r<\033[1;32m%s@%s\033[0m:\033[1;34m%s\033[0m>", user, host, dirname);
        fflush(stdout);
        return;
    }
    else {
        kill(running.pid, SIGTTIN);
        kill(running.pid, SIGTSTP);
        jobinfo[jobs].pid = running.pid;
        strcpy(jobinfo[jobs].name, running.name);
        jobs++;
        running.pid = processid;
        strcpy(running.name, "shell\0");
        signal(SIGTSTP, ctrlz);
        return;
    }
}

void ctrlc () {
    pid_t PID = getpid();
    if (PID == processid) {
        signal(SIGINT, ctrlc);
        printf("\n");
        size_t size = 10000;
        char host[size], user[size];
        gethostname(host, size);
        getlogin_r(user, size);
        long long int i;
        size_t size = 1000000, currentdirsize, inputsize, homedirsize = strlen(hdn);
        char currentdir[size], dirname[size];
        getcwd(currentdir, size);
        currentdirsize = strlen(currentdir);
        if (strstr(currentdir, hdn)) {
            strcpy(dirname, "~");
            for (i = homedirsize; i < currentdirsize; i++) {
                dirname[i - homedirsize + 1] = currentdir[i];
                
            }
            dirname[i - homedirsize + 1] = '\0';
        }
        else {
            strcpy(dirname, currentdir);
        }
        printf("\r<\033[1;32m%s@%s\033[0m:\033[1;34m%s\033[0m>", user, host, dirname);
        fflush(stdout);
        return;
    }
    else if (running.pid != processid) {
        kill(running.pid, SIGINT);
        running.pid = processid;
        strcpy(running.name, "shell\0");
        signal(SIGINT, ctrlc);
        return;
    }
}