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

int main () 
{
	jobs = 0;
	long long int i = 0;
	size_t size = 1000000, homedirsize, currentdirsize, inputsize;
	getcwd(hdn, 1000000);
	char login[size], hostname[size], homedir[size], currentdir[size], input[size], dirname[size], old[10000];
	char * ptr = input, * commands, * commandslist[10000];
	gethostname(hostname, size);
	getlogin_r(login, size);
	getcwd(homedir, size);
	processid = getpid();
	homedirsize = strlen(homedir);
	running.pid = processid;
	strcpy(running.name, "shell\0");
	strcpy(old, hdn);
	while (1) 
	{
		signal(SIGCHLD, fexit);
		signal(SIGINT, ctrlc);
		signal(SIGTSTP, ctrlz);
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
	    printf("\r<\033[1;32m%s@%s\033[0m:\033[1;34m%s\033[0m>", login, hostname, dirname);
		inputsize = getline(&ptr, &size, stdin);
		if(inputsize < 0)
		{
			exit(0);
			printf("YO");
		}
		input[inputsize - 1] = '\0';
		commands = strtok(input, ";");
		i = 0;
		while (commands) {
			commandslist[i] = commands;
			i++;
			commands = strtok(NULL, ";");
		}
		for (long long j = 0; j < i; j++) 
		{
		    size_t size = 100000;
		    char currentdir[size];
		    if (checkpipe(commandslist[j])) {
		        pipes(commandslist[j]);
		        continue;
		    }
		    if (redir(commandslist[j])) {
		        red(commandslist[j]);
		        printf("Done\n");
		        fflush(stdout);
		        continue;
		    }
		    char * commands = strtok(commandslist[j], " ");
		    // if(inputsize < 0)
		    // {
		    // 	sig();
		    // 	exit(0);
		    // }
		    if (strstr(commands, "echo")) {
		        commands = strtok(NULL, " ");
		        echo(commands);
		    }
		    else if (strstr(commands, "pwd")) {
		        pwd();
		    }
		    else if (strstr(commands, "cd")) {
		        commands = strtok(NULL, " ");
		        cd(commands, homedir);
		    }
		    else if (strstr(commands, "ls")) {
		        commands = strtok(NULL, " ");
		        ls(commands, homedir);
		    }
		    else if (strstr(commands, "pinfo")) {
		        commands = strtok(NULL, " ");
		        pinfo(commands, homedir);
		    }
		    else if (strstr(commands, "exit") || strstr(commands, "quit")) 
		    {
		        exit(0);
		    }
		   	// else if (getline(&ptr, &size, stdin) < 0) //Ctrl D
		   	// {
		   	// 	exit(0);
		   	// }
		    else if (strstr(commands, "bg")) {
		        commands = strtok(NULL, " ");
			    pid_t pid;
			    if (commands == NULL) {
			        printf("No job number given\n");
			    }
			    else {
			        pid = atoi(commands);
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
		    }
		    else if (strstr(commands, "fg")) {
		        commands = strtok(NULL, " ");
			    pid_t pid;
			    if (commands == NULL) {
			        printf("No job number given\n");
			    }
			    else {
			        pid = atoi(commands);
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
		    else if (strstr(commands, "sig")) {
		        sig(commands);
		    }
		    else if (strstr(commands, "jobs")) {
		        job();
		    }
		    else {
		        execute(commands);
		    }
		}
	}
}