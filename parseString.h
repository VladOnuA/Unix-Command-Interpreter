/* Created by:  Vlad-Alexandru Onu, November 2016 

this function parses a string and returns an array of strings
each string contains one word from the input/initial string
we assume that the format of the string read from the profile 
file is: HOME=somePath or PATH=somePath without any spaces */

char **parseInputString(char *inputString, char separators[], int bufferSize,int type);