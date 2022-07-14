#include "headers.h"
#include "pinfo.h"


void pinfo (char * commands, char * homedir) {
    long long int processid;
    char filename[10000], state[5], info[100000], space[2] = " ";
    if (commands == NULL) {
        processid = getpid();
    }
    else {
        processid = atoi(commands);
    }
    sprintf(filename, "/proc/%lld/stat", processid);
    if (fopen(filename, "r")) {
        fgets(info, 1000000, fopen(filename, "r"));
        char * token = strtok(info, space);
        for (int x = 0; x < 2; x++) {
            token = strtok(NULL, space);
        }
        while (strlen(token) > 1 || (strlen(token) < 1)) {
            token = strtok(NULL, space);
        }
        strcpy(state, token);
        if (processid) {
            printf("pid -- %lld\n", processid);
        }
        printf("Process Status -- %s\n", state);
        for (int x = 0; x < 20; x++) {
            token = strtok(NULL, space);
        }
        long long int memory = atoi(token);
        printf("Virtual Memory -- %lld\n", memory);
        fclose(fopen(filename, "r"));
    }
    else {
        printf("Invalid Process\n");
        return;
    }
    sprintf(filename, "/proc/%lld/exe", processid);
    if (fopen(filename, "r")) {
        fgets(info, 1000000, fopen(filename, "r"));
        if (readlink(filename, info, 1000000) != -1) {
            info[readlink(filename, info, 1000000)] = '\0'; 
            if (strstr(info, homedir)) {
                char temp[100000];
                strcpy(temp, "~");
                size_t n = strlen(homedir);
                long long int x;
                for (x = n; x < readlink(filename, info, 1000000); x++) {
                    temp[x - n + 1] = info[x];
                }
                temp[x - n + 1] = '\0';
                printf("Executable Path -- %s\n", temp);
            }
            else {
                printf("Executable Path -- %s\n", info);
            }
        }
        fclose(fopen(filename, "r"));
    }
    else {
        printf("Executable Path not available\n");
        return;
    }
}