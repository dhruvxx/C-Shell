## Linux Shell using C Programming Language

### Structure

The file main.c contains the main body implemented in `C`. It displays the `hostname`, `username` and `current directory`, it also supports `~`, as a subsitute for home directory. In this case, the home directory is the directory the shell files are stored in. All the headers are stored in the `headers.h` file along with individual header files for every .c file (individual command files). The prompt function is also present in the main.c file.

### Running the shell:

```bash
$ cd <2019115008>
$ make
$ ./shell
```
To exit, type `exit` or `quit` in the shell prompt.

### File Structure

Each command is coded in a different file named after the command. Each file has it's corresponding .c and .h files.


### Functions:

- The prompt (coded in main.c) displays the `host name` and the `user name` similar to a regular shell.

- `main:` runs in a while loop till an "exit" or "quit" command is given which then proceeds to exit from the shell. Inside the while loop, the inputs are taken. Each input taken is tokenized and then further passed to their respective command execution files (named after the command).

- `pwd:` The `pwd` command displays the present working directory using the `getcwd()` function, from the file `pwd.c`.

- `cd:` The cd command changes into a directory using the chdir() system call. It also supports `., .., - and ~` as arguments.

- `echo:` The echo command prints the arguments (tokenized).

- `ls:` The `ls` command supports flags `-l`, `-a` and combinations of the two. It displays the directories and files along with their details. With zero arguments, `.` or `~`, it displays for the current directory. With `..` it displays for the parent directory. Given multiple arguments, it displays the name and the contents sequentially. Flag booleans are collected and the list of directories are also stored. Displays the files and file permissions according to the flag.

- `pinfo:` Pinfo accesses the the files stat (reads the current status and the memory usage) and exec (using readlink) and thus provides information regarding the process.

- Fore and back Processes: The shell also supports running both background and foreground processes differentiated by the character `&`. `proc.c` and `execute.c` files handle these processes. 2 arrays `jobnames` and `jobpid` store the names and process ids of ongoing background processes. 

- `quit:` The quit command is used to exit the shell. It takes no additional parameters and occurs within the file main.c.

- `sig:` this command takes the job number of a running pid and sends the signal corresponding to signal number to that process.

- `Piping & Redirection:` The shell also supports `piping`, `redirection` and any combination of the two using `>, <, >> and |`. This is done using the `dup2` and `pipe` commands from c.

- The shell supports signal handling using `CTRL+C` to terminate a foreground process using `SIGINT` , `CTRL+Z` to send it to the background in a suspended state sending`SIGTSTP` signals and `CTRL+D` to exit your shell.

- The `jobs` command displays all the background jobs in the shell.

- `bg` and `fg` commands bring a foreground process to background by sending a `SIGCONT` signal. In case of `fg`, the functioning is paused until the program finishes execution.