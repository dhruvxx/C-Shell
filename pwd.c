#include "headers.h"
#include "pwd.h"

void pwd () {
	size_t size = 100000;
    char dir[size];
    getcwd(dir, size);
    printf("%s\n", dir);
}