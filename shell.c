#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "accessFile.h"
#include "parseString.h"
#include "cfgEnvVariables.h"
#include "processCommand.h"

#define PATH_MAX 4096

char *PATH, *HOME;

/* this function is the starting point of the whole shell */
void startShell(char* cwd, int bufferSize){
	while(1){
		char *inputString = malloc(bufferSize);
		fgets(inputString,bufferSize,stdin);
		strtok(inputString,"\n");
        //check if the user inputed an empty command
    	if(strcmp(inputString,"\n")==0){
            //print the current working directory and wait the next command
    		cwd=getCwd();
    		continue;
    	}
        char **arguments = malloc(bufferSize);
    	if(strcmp(inputString,"exit")!=0){
    		if(inputString[0] == '$'){
    			arguments = parseInputString(inputString, "$=", bufferSize,0);
    		    initEnvironmentVar(arguments);
    		 	printf("The environment variable HOME is: %s\n", HOME);
    			printf("The environment variable PATH is: %s\n", PATH);
    		}
    		else if(PATH != NULL){
    			//parse the input command
    		    arguments = parseInputString(inputString," /\t\v\n\f\r\a", bufferSize,1);
    		    //run the input command
    		    runCommand(arguments, bufferSize);
            }
            else{
                printf("cannot execute the command: variable PATH was not assigned\n");
            }
    	}
    	else{
            //the user enters the exit command
    		break;
    	}
		cwd=getCwd();
		free(inputString);
		free(arguments);
	}
}

int main(void) {
    int bufferSize = sizeof(char)*(PATH_MAX);
    //get the current working directory
    char *cwd = malloc(bufferSize/2);
    cwd = getCwd();
    //set the path of the profile file
    char* file_profile = strncat(cwd,"/profile",sizeof("/profile"));
    //read the environment variables from the profile file
    readFile(file_profile, bufferSize);
    //start the shell and wait for input from the user
    startShell(cwd, bufferSize);
	return EXIT_SUCCESS;
}