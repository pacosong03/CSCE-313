/****************
LE2: Introduction to Unnamed Pipes
****************/
#include <unistd.h> // pipe, fork, dup2, execvp, close
using namespace std;

int main () {
    // lists all the files in the root directory in the long format
    char* cmd1[] = {(char*) "ls", (char*) "-al", (char*) "/", nullptr};
    // translates all input from lowercase to uppercase
    char* cmd2[] = {(char*) "tr", (char*) "a-z", (char*) "A-Z", nullptr};

    // TODO: add functionality
    // Create pipe
    int fd[2];
    pid_t pid;
    if(pipe(fd) == -1) {
        return 1;
    }

    // Create child to run first command
    pid = fork();


    if(pid == 0) {
        // In child, redirect output to write end of pipe
        dup2(fd[1], 1);

        // Close the read end of the pipe on the child side.
        close(fd[0]);

        // In child, execute the command
        execvp(cmd1[0], cmd1);

    } else if (pid < 0) {
        //return if the process needs to be terminated
        return 1;
    }

    // Create another child to run second command
    pid = fork();


    if(pid == 0) {
        // In child, redirect input to the read end of the pipe
        dup2(fd[0], 0);

        // Close the write end of the pipe on the child side.
        close(fd[1]);

        // Execute the second command.
        execvp(cmd2[0], cmd2);
        
    } else if (pid < 0){
        return 1;
    }


    // Reset the input and output file descriptors of the parent.
    return 0;
}
