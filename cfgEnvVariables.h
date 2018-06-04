/* Created by:  Vlad-Alexandru Onu, November 2016 

this function prints and returns the current working directory 
if the current working directory was not found it prints an error */

char *getCwd();

/* this function initializes the environment variables: HOME and PATH 
and it removes the new line character at the end of each of the variables */

void initEnvironmentVar(char **string);

/* this function checks if the environment variables HOME and PATH were assigned, 
otherwise an error is printed */

void checkAssignmentCorrectness();