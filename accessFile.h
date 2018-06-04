/* Created by:  Vlad-Alexandru Onu, November 2016

this function opens the profile file upon the start-up of the shell
and it returns an error if the profile file does not exist */

FILE *openFile(char* file_path);

/* this function reads the content of the profile file line by line
and initializes the environment variables HOME and PATH
it also checks if the variables were assigned, otherwise an error is printed */

void readFile(char *file_profile, int bufferSize);