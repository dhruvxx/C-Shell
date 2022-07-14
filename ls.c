#include "headers.h"
#include "ls.h"

void lslistall (char * dirname, char * homedir) {
	char file[10000], time[50];
	struct stat st;
	struct dirent ** namelist;
	DIR * directory;
	long long n = scandir(dirname, &namelist, NULL, alphasort);
	if (n >= 0) {
		while (n--) {
			strcpy(file, dirname);
			strcat(file, "/");
			if (namelist[n]->d_name[0] == '~') {
                long long int x;
                char temp1[100000];
                strcpy(temp1, homedir);
                size_t n = strlen(namelist[n]->d_name), h = strlen(homedir);
                for (x = 1; x < n; x++) {
                    temp1[h + x - 1] = namelist[n]->d_name[x];
                }
                temp1[h + x - 1] = '\0';
                char * tempptr = temp1;
                char * temp = tempptr;
				strcat(file, temp);
			}
			else {
				strcat(file, namelist[n]->d_name);
			}
			if (stat(file, &st) == -1) {
				perror("Error");
			}
			else {
				char permissions[25] = "----------\0";
				int i = 0;
				if (S_ISDIR(st.st_mode)) permissions[i] = 'd';
				i++;
				if (st.st_mode & S_IRUSR) permissions[i] = 'r';
				i++;
				if (st.st_mode & S_IWUSR) permissions[i] = 'w';
				i++;
				if (st.st_mode & S_IXUSR) permissions[i] = 'x';
				i++;
				if (st.st_mode & S_IRGRP) permissions[i] = 'r';
				i++;
				if (st.st_mode & S_IWGRP) permissions[i] = 'w';
				i++;
				if (st.st_mode & S_IXGRP) permissions[i] = 'x';
				i++;
				if (st.st_mode & S_IROTH) permissions[i] = 'r';
				i++;
				if (st.st_mode & S_IWOTH) permissions[i] = 'w';
				i++;
				if (st.st_mode & S_IXOTH) permissions[i] = 'x';
				
				long long int links = st.st_nlink;
				
				struct passwd * p = getpwuid(st.st_uid);
				struct group * g = getgrgid(st.st_gid);
				char * uid = p->pw_name, * gid = g->gr_name;
				strftime(time, 50, "%h %e %H:%M", localtime(&st.st_mtime));
				
				printf("%s %3lld %10s %10s %6lld  %s %s\n", permissions, links, uid, gid, st.st_size, time, namelist[n]->d_name);
			}
		}
	}
	else {
		perror("Error");
	}
}
void lslist (char * dirname, char * homedir) {
	char file[10000], time[50];
	struct stat st;
	struct dirent ** namelist;
	DIR * directory;
	long long n = scandir(dirname, &namelist, NULL, alphasort);
	if (n >= 0) {
		while (n--) {
			strcpy(file, dirname);
			strcat(file, "/");
			if (namelist[n]->d_name[0] == '~') {
                long long int x;
                char temp1[100000];
                strcpy(temp1, homedir);
                size_t n = strlen(namelist[n]->d_name), h = strlen(homedir);
                for (x = 1; x < n; x++) {
                    temp1[h + x - 1] = namelist[n]->d_name[x];
                }
                temp1[h + x - 1] = '\0';
                char * tempptr = temp1;
                char * temp = tempptr;
				strcat(file, temp);
			}
			else {
				strcat(file, namelist[n]->d_name);
			}
			if (stat(file, &st) == -1) {
				perror("Error");
			}
			else {
				if (strcmp(namelist[n]->d_name, ".") == 0 || strcmp(namelist[n]->d_name, "..") == 0) {
					continue;
				}
				char permissions[25] = "----------\0";
				int i = 0;
				if (S_ISDIR(st.st_mode)) permissions[i] = 'd';
				i++;
				if (st.st_mode & S_IRUSR) permissions[i] = 'r';
				i++;
				if (st.st_mode & S_IWUSR) permissions[i] = 'w';
				i++;
				if (st.st_mode & S_IXUSR) permissions[i] = 'x';
				i++;
				if (st.st_mode & S_IRGRP) permissions[i] = 'r';
				i++;
				if (st.st_mode & S_IWGRP) permissions[i] = 'w';
				i++;
				if (st.st_mode & S_IXGRP) permissions[i] = 'x';
				i++;
				if (st.st_mode & S_IROTH) permissions[i] = 'r';
				i++;
				if (st.st_mode & S_IWOTH) permissions[i] = 'w';
				i++;
				if (st.st_mode & S_IXOTH) permissions[i] = 'x';
				
				long long int links = st.st_nlink;
				
				struct passwd * p = getpwuid(st.st_uid);
				struct group * g = getgrgid(st.st_gid);
				char * uid = p->pw_name, * gid = g->gr_name;
				strftime(time, 50, "%h %e %H:%M", localtime(&st.st_mtime));
				
				printf("%s %3lld %10s %10s %6lld  %s %s\n", permissions, links, uid, gid, st.st_size, time, namelist[n]->d_name);
			}
		}
	}
	else {
		perror("Error");
	}
}

void ls (char * commands, char * homedir) {
    bool aflag = 0, lflag = 0;
    char * dirnames[1000];
    long long int i = 0;
    if (commands == NULL) {
        DIR * directory;
        struct dirent * current;
        if (directory = opendir(".")) {
        while ((current = readdir(directory)) != NULL) {
            if (current->d_name[0] != '.') {
                printf("%s\n", current->d_name);
            }
        }
        closedir(directory);
        }
        else {
            perror("Error");
        }
    }
    else {
        while (commands) {
            if (commands[0] == '-') {
                if (strstr(commands, "a")) {
                    aflag = 1;
                }
                if (strstr(commands, "l")) {
                    lflag = 1;
                }
            }
            else {
                dirnames[i] = commands;
                i++;
            }
            commands = strtok(NULL, " ");
        }
        if (!lflag && !aflag) {
            if (i == 0) {
                DIR * directory;
                struct dirent * current;
                if (directory = opendir(".")) {
                while ((current = readdir(directory)) != NULL) {
                    if (current->d_name[0] != '.') {
                        printf("%s\n", current->d_name);
                    }
                }
                closedir(directory);
                }
                else {
                    perror("Error");
                }
            }
            else if (i == 1) {
                if (dirnames[0][0] == '~') {
                    long long int x;
                    char temp1[100000];
                    strcpy(temp1, homedir);
                    size_t n = strlen(dirnames[0]), h = strlen(homedir);
                    for (x = 1; x < n; x++) {
                        temp1[h + x - 1] = dirnames[0][x];
                    }
                    temp1[h + x - 1] = '\0';
                    char * tempptr = temp1;
                    char * temp = tempptr;
                    DIR * directory;
                    struct dirent * current;
                    if (directory = opendir(temp)) {
                    while ((current = readdir(directory)) != NULL) {
                        if (current->d_name[0] != '.') {
                            printf("%s\n", current->d_name);
                        }
                    }
                    closedir(directory);
                    }
                    else {
                        perror("Error");
                    }
                }
                else {
                    DIR * directory;
                    struct dirent * current;
                    if (directory = opendir(dirnames[0])) {
                    while ((current = readdir(directory)) != NULL) {
                        if (current->d_name[0] != '.') {
                            printf("%s\n", current->d_name);
                        }
                    }
                    closedir(directory);
                    }
                    else {
                        perror("Error");
                    }
                }
            }
            else if (i > 1) {
                for (long long int x = 0; x < i; x++) {
                    if (dirnames[x][0] == '~') {
                        long long int x;
                        char temp1[100000];
                        strcpy(temp1, homedir);
                        size_t n = strlen(dirnames[x]), h = strlen(homedir);
                        for (x = 1; x < n; x++) {
                            temp1[h + x - 1] = dirnames[x][x];
                        }
                        temp1[h + x - 1] = '\0';
                        char * tempptr = temp1;
                        char * temp = tempptr;
                        printf("\033[1;34m%s:\033[0m\n", temp);
                        DIR * directory;
                        struct dirent * current;
                        if (directory = opendir(temp)) {
                        while ((current = readdir(directory)) != NULL) {
                            if (current->d_name[0] != '.') {
                                printf("%s\n", current->d_name);
                            }
                        }
                        closedir(directory);
                        }
                        else {
                            perror("Error");
                        }
                    }
                    else {
                        printf("\033[1;34m%s:\033[0m\n", dirnames[x]);
                        DIR * directory;
                        struct dirent * current;
                        if (directory = opendir(dirnames[x])) {
                        while ((current = readdir(directory)) != NULL) {
                            if (current->d_name[0] != '.') {
                                printf("%s\n", current->d_name);
                            }
                        }
                        closedir(directory);
                        }
                        else {
                            perror("Error");
                        }
                    }
                    printf("\n\n");
                }
            }
        }
        if (lflag && aflag) {
            if (i == 0) {
                lslistall(".", homedir);
            }
            else if (i == 1) {
                if (dirnames[0][0] == '~') {
                    long long int x;
                    char temp1[100000];
                    strcpy(temp1, homedir);
                    size_t n = strlen(dirnames[0]), h = strlen(homedir);
                    for (x = 1; x < n; x++) {
                        temp1[h + x - 1] = dirnames[0][x];
                    }
                    temp1[h + x - 1] = '\0';
                    char * tempptr = temp1;
                    char * temp = tempptr;
                    lslistall(temp, homedir), homedir;
                }
                else {
                    lslistall(dirnames[0], homedir);
                }
            }
            else if (i > 1) {
                for (long long int x = 0; x < i; x++) {
                    if (dirnames[x][0] == '~') {
                        long long int x;
                        char temp1[100000];
                        strcpy(temp1, homedir);
                        size_t n = strlen(dirnames[x]), h = strlen(homedir);
                        for (x = 1; x < n; x++) {
                            temp1[h + x - 1] = dirnames[x][x];
                        }
                        temp1[h + x - 1] = '\0';
                        char * tempptr = temp1;
                        char * temp = tempptr;
                        printf("\033[1;34m%s:\033[0m\n", temp);
                        lslistall(temp, homedir);
                    }
                    else {
                        printf("\033[1;34m%s:\033[0m\n", dirnames[x]);
                        lslistall(dirnames[x], homedir);
                    }
                    printf("\n\n");
                }
            }
        }
    }
}