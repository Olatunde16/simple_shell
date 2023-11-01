#include "main.h"

int main() {
    char input[MAX_INPUT_LENGTH];
    char *args[MAX_ARGS];
    int num_args;

    while (1) {
        // Display prompt
        printf("Simple-Shell (PID: %d)> ", getpid());

        // Get user input
        fgets(input, MAX_INPUT_LENGTH, stdin);

        // Remove newline character
        input[strlen(input) - 1] = '\0';

        // Exit if user enters "exit"
        if (strcmp(input, "exit") == 0) {
            break;
        }

	// Tozkenize the input into arguments
	char *token = strtok(input, " ");
	num_args = 0;

	while (token != NULL){
		args[num_args++] = token;
		token = strtok(NULL, " ");
	}

	// Add a NULL pointer to the end of the args array (execvp required)
	args[num_args] = NULL;

        // Fork a new process
        pid_t pid = fork();

        if (pid == 0) {
            // Child process
            // Execute the command
            execvp(args[0], args);

            // If execvp() fails, print an error message
            perror("Command not found");
            exit(1);
        } else if (pid > 0) {
            // Parent process
            // Wait for the child process to complete
            wait(NULL);
        } else {
            // Fork failed
            perror("Fork failed");
        }
    }

    return 0;
}
