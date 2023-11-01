#include "main.h"

int pid = my_fork();
if(pid == -1){
	printf("failed\n"); // We failed - bail out.
}
else if(pid > 0){ // Let the parent wait
	int status;
	waitpid(pid, &status, 0);
}
else{ // child
	execvp(command, argument);
}
