/* Created by:  Vlad-Alexandru Onu, November 2016

this function finds the command that the user is looking for.
In order to achieve this, it parses the PATH variable and then it searches through all 
the directories in PATH for that specific command. 
If the function finds the command, it returns the path of the executable file; 
i.e: if the command is ls the return value  will be /bin/ls, otherwise it returns a null string */

char *findCommand(char **arguments, int bufferSize);

/* this function forks and executes the command inputed by the user 
it creates a new process, which becomes the child process of the caller */

int executeCommand(char **arguments, char *file_name);

/* this function is the caller of the above functions find and execute
if the command is change directory, the code implements the command using chdir function
if the command is "." or ".." it prints that the access is denied (not proper commands)
else it calls the find function and if the result of it is not NULL it calls executeCommand function */

void runCommand(char **arguments, int bufferSize);