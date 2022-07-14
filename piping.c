#include "headers.h"
#include "echo.h"
#include "cd.h"
#include "pwd.h"
#include "pinfo.h"
#include "execute.h"
#include "proc.h"
#include "sig.h"
#include "jobs.h"
#include "signals.h"
#include "piping.h"
#include "redirection.h"

int checkpipe (char * commands) {
   if (strstr(commands, "|")) {
       return 1;
   }
   return 0;
}
 
 
void pipes (char * commands) {
   int count = 0;
   char * args[1000];
   while ((strtok(commands, "|")) != NULL) {
       args[count] = strtok(commands, "|");
       count++;
       char * tok = strtok(commands, "|");
       tok = strtok(NULL, "|");
   }
   for (int i = 0; i < count; i++) {
       int pid, change, pipearr[2];
       pipe(pipearr);
       pid = fork();
       if (pid == 0) {
           dup2(change, 0);
           int j = i + 1;
           if (args[j] != NULL) {
               dup2(pipearr[1], 1);
           }
           close(pipearr[0]);
		   size_t size = 100000;
		   char currentdir[size];
		   if (checkpipe(args[i])) {
		       pipes(args[i]);
		   }
		   if (redir(args[i])) {
		       red(args[i]);
		       printf("Done\n");
		       fflush(stdout);
		   }
		   char * commands = strtok(args[i], " ");
		   if (strcmp(commands, "echo") == 0) {
		       commands = strtok(NULL, " ");
		       echo(commands);
		   }
		   else if (strcmp(commands, "pwd") == 0) {
		       pwd();
		   }
		   else if (strcmp(commands, "cd") == 0) {
		       commands = strtok(NULL, " ");
		       cd(commands, hdn);
		   }
		   else if (strcmp(commands, "ls") == 0) {
		       commands = strtok(NULL, " ");
		       ls(commands, hdn);
		   }
		   else if (strcmp(commands, "pinfo") == 0) {
		       commands = strtok(NULL, " ");
		       pinfo(commands, hdn);
		   }
		   else if (strcmp(commands, "quit") == 0) {
		       // sig();
		       exit(EXIT_SUCCESS);
		   }
		   else if (strcmp(commands, "bg") == 0) {
		       back(commands);
		   }
		   else if (strcmp(commands, "fg") == 0) {
		       fore(commands);
		   }
		   else if (strcmp(commands, "sig") == 0) {
		       sig(commands);
		   }
		   else if (strcmp(commands, "jobs") == 0) {
		       job();
		   }
		   else {
		       execute(commands);
		   }
           exit(0);
       }
       else if (pid > 0) {
           wait(NULL);
           close(pipearr[1]);
           change = pipearr[0];
       }
       else {
           perror("Error: Fork Failed\n");
       }
   }
}
 