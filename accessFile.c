#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "accessFile.h"
#include "parseString.h"
#include "cfgEnvVariables.h"

FILE *openFile(char* file_path){
    //open the profile file at the specified path
    FILE *FILE_PROFILE = fopen(file_path, "r");
    //check if the profile file exists at the specified path
    if(FILE_PROFILE == NULL){
        //print an error message if it doesn't exist
    	perror("Error: profile file does not exist");
    	return NULL;
    }
    return FILE_PROFILE;
}

void readFile(char *file_profile, int bufferSize){
	//open the profile file
	FILE *PROFILE = openFile(file_profile);
    if(PROFILE != NULL) {
        char *Line = malloc(bufferSize);
        char **string = malloc(bufferSize);
        //read the profile file line by line and parse each line 
        while(1){
            //if we finished to read all the lines from the profile file then stop reading
            if(fgets(Line,bufferSize,PROFILE) == NULL){
                break;
            }
            string = parseInputString(Line,"=",bufferSize,0);
            initEnvironmentVar(string);
        }
        checkAssignmentCorrectness();
        //deallocate the block of memory
        free(Line);
        free(string);
    }
}
