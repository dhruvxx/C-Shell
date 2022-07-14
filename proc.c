#include "headers.h"
#include "proc.h"

void fexit() {
	int status;
	pid_t pid = waitpid(-1, &status, WNOHANG);
	if (pid > 0) 
	{
		for (int i = 0; i < jobs; i++) {
			if (WIFEXITED(status)) {
				if (jobinfo[i].pid == pid) {
					if (WEXITSTATUS(status)) {
						printf("\n%s exited abnormally with pid %lld\n", jobinfo[i].name, jobinfo[i].pid);
					}
					else {
						printf("\n%s exited normally with pid %lld\n", jobinfo[i].name, jobinfo[i].pid);
					}
					char host[100000], user[100000];
					gethostname(host, 100000); getlogin_r(user, 100000);
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
					if (i >= 0) 
					{
						for (long long k = i; k < jobs - 1; k++) {
							jobinfo[k].pid = jobinfo[k + 1].pid;
							strcpy(jobinfo[k].name, jobinfo[k + 1].name);
						}
						jobs--;
					}
					else {
						perror("Error");
					}
				}
			}
		}
	}
	else if (pid == 0) 
	{
		for (int i = 0; i < jobs; i++) {
			if (WIFEXITED(status)) {
				if (jobinfo[i].pid == pid) {
					if (WEXITSTATUS(status)) {
						printf("\n%s exited abnormally with pid %lld\n", jobinfo[i].name, jobinfo[i].pid);
					}
					else {
						printf("\n%s exited normally with pid %lld\n", jobinfo[i].name, jobinfo[i].pid);
					}
					char host[100000], user[100000];
					gethostname(host, 100000); getlogin_r(user, 100000);
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
					if (i >= 0) 
					{
						for (long long k = i; k < jobs - 1; k++) {
							jobinfo[k].pid = jobinfo[k + 1].pid;
							strcpy(jobinfo[k].name, jobinfo[k + 1].name);
						}
						jobs--;
					}
					else {
						perror("Error");
					}
				}
			}
		}
	}
	else {
		return;
	}
}