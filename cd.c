#include "headers.h"
#include "cd.h"

void path_change(char temp[], char * commands, char * homedir)
{
    long long int x;
    strcpy(temp, homedir);
    size_t n = strlen(commands), h = strlen(homedir);
    for (x = 1; x < n; x++) {
        temp[h + x - 1] = commands[x];
    }
    temp[h + x - 1] = '\0';
    if (chdir(temp)) {
        perror("Error");
    }
}

void cd (char * commands, char * homedir) {
    int var = 10000;
    int var1;
    bool changed;
    char temp1[var], old[10000];
    if ((commands == NULL) || (strcmp("~", commands) == 0) || (strcmp(".", commands) == 0)) 
    {
        getcwd(temp1, var);
        strcpy(old, temp1);
        if(chdir(homedir)) {
            perror("Error");
        }
    }
    else if (commands[0] == '~') {
        changed = 1;
        getcwd(temp1, var);
        strcpy(old, temp1);
        long long int x;
        char temp[100000];
        path_change(temp, commands, homedir);
    }
    else if (strcmp(commands, "-") == 0) {
        long long int i;
        char dirname[var];
        size_t currentdirsize = strlen(old), homedirsize = strlen(hdn);
        if (changed == 0) {
            printf("%s\n", hdn);
        }
        else if (strstr(old, hdn)) {
            strcpy(dirname, "~");
            for (i = homedirsize; i < currentdirsize; i++) {
                dirname[i - homedirsize + 1] = old[i];
                
            }
            dirname[i - homedirsize + 1] = '\0';
            printf("%s\n", dirname);
        }
        else {
            strcpy(var1, old);
            strcpy(dirname, var1);
            printf("%s\n", dirname);
        }
        if (chdir(old)) {
            perror("Error");
        }
    }
    else {
        changed = 1;
        getcwd(temp1, var);
        strcpy(var1, temp1);
        strcpy(old, var1);
        if (chdir(commands)) {
            perror("Error");
        }
    }
}