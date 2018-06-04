#include <string.h>
#include <stdlib.h>
#include "parseString.h"

char **parseInputString(char *inputString, char separators[], int bufferSize,int type){
    char **words = malloc(bufferSize);
    char *p = strtok(inputString,separators);
    int NoOfWords = 0;
    while(p){
        words[NoOfWords] = strdup(p);
        NoOfWords++;
        p = strtok(NULL,separators);
    }
    if(type==1){
    	words[NoOfWords] = NULL;
    }
    return words;
}