This is a simplified Unix command interpreter in C, similar to bash or csh in purpose, but trimmed down to the bare minimum.
1. Upon start-up, the shell should get the current working directory, read the file profile from that directory and configure the environment variables HOME and PATH as specified in that file. For example,
     PATH=/bin:/usr/bin:/usr/local/bin
     HOME=/home/os
sets the home directory to be /home/os and sets the search path to comprise the sequence /bin, /usr/bin and /usr/local/bin of directories. It is permissible for the variables to be assigned in either order and for their values to be replaced by subsequent assignments. Variable expansion has not been implemented. An error is reported if profile does not exist or if either variable is not assigned.

2. As a command prompt to the user, the shell displays the full path of the current working directory followed by >. When the user types a command and hits enter, the shell reads the input. The first word on the line should be interpreted as the name of the program to run and the rest of the line should be interpreted as the arguments to give to the program. For example, if the user types ls –l /tmp , then the shell should run the program ls and give it the arguments -l and /tmp . The output should be the same as if the user had typed this into a regular Unix shell. To achieve this, the shell searches through the directories listed in PATH until it finds the named program. It then forks and executes the program (using execv). 

3. When the program completes, the user is presented with the prompt again, so he or she can enter another command.

4. The shell has the capability to handle assignment to HOME and PATH from the command line (e.g., $HOME=/home/os2), and to act upon the cd command by changing the working directory as specified (or to the HOME directory by default).