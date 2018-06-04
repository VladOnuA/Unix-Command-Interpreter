#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include "parseString.h"
#include "processCommand.h"

#define PATH_MAX 4096

extern char *HOME, *PATH;

char *findCommand(char **arguments, int bufferSize){
	int index = 0;
    int found = 0;
	char *file_name = NULL;
	char **paths = (char**)malloc(bufferSize);
	paths = parseInputString(strdup(PATH),":",bufferSize,1);
	DIR *dir;
	struct dirent *dp = NULL;
	while(paths[index] != NULL && found == 0){
		dir = opendir(paths[index]);
		if(dir == NULL){
			printf("%s: directory not found: check the PATH variable\n", paths[index]);
		}
		else{
			while ((dp=readdir(dir)) != NULL && found == 0) {
				if(strcmp(dp->d_name, arguments[0]) == 0){
					file_name = paths[index];
					strcat(file_name,"/");
					strcat(file_name,dp->d_name);
                    found = 1;
				 }
			 }
             closedir(dir);
		 }
		 index++;
	}
    free(paths);
    if(found == 1){
        return file_name;
    }
    return NULL;
}

int executeCommand(char **arguments, char *file_name){
	int status;
	pid_t processID;
	//create a new process, which becomes the child process of the caller
	processID = fork();
	//the creation of a child process was unsuccessful
	if(processID < 0) {
		printf("Error: fork failed\n");
	}
	else if(processID == 0) {
		if(execv(file_name, arguments) == -1) {
			//printf("%s: command not found\n", arguments[0]);
		}
		exit(EXIT_FAILURE);
	}
	else {
		// Parent process
		do{
			waitpid(processID, &status, WUNTRACED);
		}while (!WIFEXITED(status) && !WIFSIGNALED(status));
	}
	return 1;
}

void runCommand(char **arguments, int bufferSize){
	//check if the inputed command is change directory
    if(strcmp(arguments[0],"cd") == 0){
        if(arguments[1] == NULL){
            chdir(HOME);
        }
        else{
            int test = 1;
            int index = 1;
            char buffer[PATH_MAX + 1];
        	char *cwdir = getcwd(buffer, PATH_MAX + 1);
            while(arguments[index] != NULL && test == 1){
                if(chdir(arguments[index]) != 0 && test == 1){
                    test = 0;
                    printf("%s: No such file or directory\n", arguments[index]);
                    chdir(cwdir);
                }
                index++;
            }
        }
    }
    else if(strcmp(arguments[0],".") == 0 || strcmp(arguments[0],"..") == 0){
    	printf("%s: permission denied\n", arguments[0]);
    }
    else{
        char *file_name = malloc(sizeof(char)*1024);
        file_name = findCommand(arguments, bufferSize);
        if(file_name != NULL){
            executeCommand(arguments,file_name);
        }
        else{
        	printf("%s: command not found\n", arguments[0]);
        }
    }
}
