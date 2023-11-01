#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

#define MAX_INPUT_LENGTH 1024
#define MAX_ARGS 64

int execute_command(char *args[]) {
    pid_t pid = fork();

    if (pid == 0) {
        // Child process
        execvp(args[0], args);
        perror("Command not found");
        exit(1);
    } else if (pid > 0) {
        // Parent process
        int status;
        wait(&status);
        return WEXITSTATUS(status);
    } else {
        perror("Fork failed");
        return -1;
    }
}

int main() {
    char input[MAX_INPUT_LENGTH];
    char *args[MAX_ARGS];
    int num_args;

    while (1) {
        // Display prompt
        printf("SimpleShell (PID: %d)> ", getpid());

        // Get user input
        fgets(input, MAX_INPUT_LENGTH, stdin);

        // Remove newline character
        input[strlen(input) - 1] = '\0';

        // Exit if user enters "exit"
        if (strcmp(input, "exit") == 0) {
            break;
        }

        // Tokenize the input into arguments
        char *token = strtok(input, " ");
        num_args = 0;

        while (token != NULL) {
            args[num_args++] = token;
            token = strtok(NULL, " ");
        }

        // Add a NULL pointer to the end of the args array (required by execvp)
        args[num_args] = NULL;

        // Check for logical operators
        int result = execute_command(args);

        // Handle && and ||
        if (result == 0 && strstr(input, "&&") != NULL) {
            // Execute the next command only if the previous one succeeded
            token = strtok(input, "&&");
            token = strtok(NULL, "&&");
            if (token != NULL) {
                num_args = 0;
                token = strtok(token, " ");
                while (token != NULL) {
                    args[num_args++] = token;
                    token = strtok(NULL, " ");
                }
                args[num_args] = NULL;
                result = execute_command(args);
            }
        } else if (result != 0 && strstr(input, "||") != NULL) {
            // Execute the next command only if the previous one failed
            token = strtok(input, "||");
            token = strtok(NULL, "||");
            if (token != NULL) {
                num_args = 0;
                token = strtok(token, " ");
                while (token != NULL) {
                    args[num_args++] = token;
                    token = strtok(NULL, " ");
                }
                args[num_args] = NULL;
                result = execute_command(args);
            }
        }
    }

    return 0;
}
