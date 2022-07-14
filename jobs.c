#include "headers.h"
#include "jobs.h"

void job () {
    char filename[100000], info[100000], status[10000], space[2] = " ";
    for (int i = 0; i < jobs; i++) {
        sprintf(filename, "/proc/%lld/stat", jobinfo[i].pid);
        if (fopen(filename, "r")) {
            fgets(info, 100000, fopen(filename, "r"));
            char * token = strtok(info, " ");
            for (int x = 0; x < 2; x++) {
                token = strtok(NULL, " ");
            }
            while (strlen(token) != 1) {
                token = strtok(NULL, " ");
            }
            if (strcmp(token, "-r") == 0) {
                if(strcmp(status, "Running") == 0)
                    printf("[%d] %s %s [%lld]\n", i + 1, status, jobinfo[i].name, jobinfo[i].pid);
            }
            else if (strcmp(token, "-s") == 0) {
                if(strcmp(status, "Stopped") == 0)
                    printf("[%d] %s %s [%lld]\n", i + 1, status, jobinfo[i].name, jobinfo[i].pid);
            }
        }
        printf("[%d] %s %s [%lld]\n", i + 1, status, jobinfo[i].name, jobinfo[i].pid);
    }
    if (jobs == 0) {
        printf("No jobs running\n");
    }
}