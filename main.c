#include "main.h"

int main() {
    char input[MAX_INPUT_LENGTH];

    while (1) {
        // Display prompt
        printf("SimpleShell> ");

        // Get user input
        fgets(input, MAX_INPUT_LENGTH, stdin);

        // Remove newline character
        input[strlen(input) - 1] = '\0';

        // Exit if user enters "exit"
        if (strcmp(input, "exit") == 0) {
            break;
        }

        // Fork a new process
        pid_t pid = fork();

        if (pid == 0) {
            // Child process
            // Execute the command
            execlp(input, input, (char *)NULL);

            // If execlp() fails, print an error message
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
