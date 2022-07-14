#include "headers.h"
#include "redirection.h"

int redir (char * commands) {
   if (strstr(commands, "<") && strstr(commands, ">>")) {
       return 1;
   }
   else if (strstr(commands, ">>")) {
       return 2;
   }
   else if (strstr(commands, "<") && strstr(commands, ">")) {
       return 3;
   }
   else if (strstr(commands, "<")) {
       return 4;
   }
   else if (strstr(commands, ">")) {
       return 5;
   }
   else {
       return 0;
   }
}
 
void red (char * commands) 
{
   int count = 0, f, s, fpin, fpout;
   int re = redir(commands);
   char * ip[10000], * op[10000];
   char * info[10000];
   char * opf, * ipf;
   op[0] = commands;
   if (re == 0) {
       return;
   }
   if (re != 4 && re != 0) {
       op[0] = strtok(commands, ">");
       op[1] = strtok(NULL, ">");
       if (op[1] == NULL) {
           printf("Invalid output file\n");
           return;
       }
       opf = strtok(op[1], " ");
   }
   ip[0] = op[0];
   if (re == 1 || re == 3 || re == 4) {
       ip[0] = strtok(ip[0], "<");
       ip[1] = strtok(NULL, "<");
       if (ip[1] == NULL) {
           printf("No input file given\n");
           return;
       }
       ipf = strtok(ip[1], " ");
       if (access(ipf, F_OK) == -1) {
           printf("Invalid input file\n");
           return;
       }
   }
   ip[0] = strtok(ip[0], " ");
   while (ip[0]) {
       info[count] = ip[0];
       count++;
       ip[0] = strtok(NULL, " ");
   }
   info[count] = NULL;
   if (re != 4 && re != 0) {
       if (opf == NULL) {
           printf("No output file given\n");
           return;
       }
   }
   if (fork() == 0) {
       if (re == 1 || re == 3 || re  == 4) {
           if (fpin = open(ipf, O_RDONLY) >= 0) {
               dup2(fpin, 0);
               close(fpin);
           }
           else {
               perror("Error");
           }
       }
       if (re != 4 && re > 0) {
           if (re == 1 || re == 2) {
               fpout = open(opf, O_WRONLY | O_APPEND | O_CREAT, 0644);
           }
           else if (re == 3 || re == 5) {
               fpout = open(opf, O_WRONLY | O_TRUNC | O_CREAT, 0644);
           }
           if (fpout < 0) {
               perror("Error");
           }
               dup2(fpout, 1);
               close(fpout);
       }
       int e = execvp(info[0], info);
       if (e == -1) {
           perror("Error");
       }
       exit(0);
   }
   else if (fork() > 0) {
       return;
   }
   else {
       printf("Error forking\n");
       return;
   }
   return;
}