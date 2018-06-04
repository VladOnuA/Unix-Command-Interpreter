#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "cfgEnvVariables.h"

#define PATH_MAX 4096

extern char *PATH, *HOME;

char *getCwd(){
    char buffer[PATH_MAX + 1];
	char *cwd = getcwd(buffer, PATH_MAX + 1);
    if(cwd != NULL){
        //print the current working directory followed by >
        printf("%s>", cwd);
    }
    else{
    	perror("The current working directory was not found");
    	return NULL;
    }
    return cwd;
}

void initEnvironmentVar(char **string){
	if(string[1] != NULL){
        printf("%s aici\n", string[1]);
		if(strcmp(string[0],"HOME") == 0){
			HOME = string[1];
			//remove the newline character from the end of the string
			strtok(HOME,"\n");
		}
		else if(strcmp(string[0],"PATH") == 0){
			PATH = string[1];
			//remove the newline character from the end of the string
			strtok(PATH,"\n");
		}
	}
}

void checkAssignmentCorrectness(){
	//report an error if either environment variable is not assigned
	if(HOME == NULL || PATH == NULL){
		perror("Error: HOME or PATH variables were not assigned");
	}
}
