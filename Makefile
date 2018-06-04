all: shell.c accessFile.c cfgEnvVariables.c parseString.c processCommand.c 
	gcc -Wall -g -o shell shell.c parseString.c cfgEnvVariables.c  accessFile.c processCommand.c