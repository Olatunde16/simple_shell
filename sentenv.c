#include <stdio.h>
#include <stdlib.h>
#include "main.h"

void execute_command(char *args[]) 
{
	pid_t pid = fork();

    if (pid == 0) {
        execvp(args[0], args);
        perror("Command not found");
        exit(1);
    } else if (pid > 0) {
        int status;
        wait(&status);

        if (WIFEXITED(status)) {
            printf("Child process exited with status %d\n", WEXITSTATUS(status));
        }
    } else {
        perror("Fork failed");
    }
}

void execute_commands_from_file(const char *filename) 
{
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        return;
    }

    char line[MAX_INPUT_LENGTH];

    while (fgets(line, sizeof(line), file) != NULL) {
        line[strlen(line) - 1] = '\0';

        if (line[0] == '#' || line[0] == '\0') {
            continue;
          
        }

        char *args[MAX_ARGS];
        int num_args = 0;
        char *token = strtok(line, " ");

        while (token != NULL) {
            args[num_args++] = token;
            token = strtok(NULL, " ");
        }

        args[num_args] = NULL;

        if (strcmp(args[0], "setenv") == 0) {
            if (num_args == 3) {
                if (setenv(args[1], args[2], 1) != 0) {
                    fprintf(stderr, "Error setting environment variable: %s\n", args[1]);
                }
            } else {
                fprintf(stderr, "Usage: setenv VARIABLE VALUE\n");
            }
        } else if (strcmp(args[0], "unsetenv") == 0) {
            if (num_args == 2) {
                if (unsetenv(args[1]) != 0) {
                    fprintf(stderr, "Error unsetting environment variable: %s\n", args[1]);
                }
            } else {
                fprintf(stderr, "Usage: unsetenv VARIABLE\n");
            }
        } else {
            execute_command(args);
        }
    }

    fclose(file);
}

int main(int argc, char *argv[]) {
    if (argc == 2) {
        execute_commands_from_file(argv[1]);
    } else if (argc > 2) {
        printf("Usage: %s [filename]\n", argv[0]);
        return 1;
    } else {
        char input[MAX_INPUT_LENGTH];

        while (1) {
            printf("simple_shell> ");

            if (fgets(input, MAX_INPUT_LENGTH, stdin) == NULL) {
                printf("\nExiting...\n");
                break;
            }

            input[strlen(input) - 1] = '\0';

            if (input[0] == '#' || input[0] == '\0') {
                continue;
            }

            char *args[MAX_ARGS];
            int num_args = 0;
            char *token = strtok(input, " ");

            while (token != NULL) {
                args[num_args++] = token;
                token = strtok(NULL, " ");
            }

            args[num_args] = NULL;

            if (strcmp(args[0], "setenv") == 0) {
                if (num_args == 3) {
                    if (setenv(args[1], args[2], 1) != 0) {
                        fprintf(stderr, "Error setting environment variable: %s\n", args[1]);
                    }
                } else {
                    fprintf(stderr, "Usage: setenv VARIABLE VALUE\n");
                }
            } else if (strcmp(args[0], "unsetenv") == 0) {
                if (num_args == 2) {
                    if (unsetenv(args[1]) != 0) {
                        fprintf(stderr, "Error unsetting environment variable: %s\n", args[1]);
                    }
                } else {
                    fprintf(stderr, "Usage: unsetenv VARIABLE\n");
                }
            } else {
                execute_command(args);
            }
        }
    }

    return 0;
}
