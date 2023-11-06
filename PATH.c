#include "main.h"

char *get_command_path(char *command) {
    char *path = getenv("PATH");
    char *path_copy = strdup(path);
    char *token = strtok(path_copy, ":");

    while (token != NULL) {
        char *command_path = malloc(strlen(token) + strlen(command) + 2);
        sprintf(command_path, "%s/%s", token, command);

        if (access(command_path, X_OK) == 0) {
            free(path_copy);
            return command_path;
        }

        free(command_path);
        token = strtok(NULL, ":");
    }

    free(path_copy);
    return NULL;
}

int execute_command(char *args[]) {
    char *command_path = get_command_path(args[0]);

    if (command_path == NULL) {
        printf("Command '%s' not found\n", args[0]);
        return -1;
    }

    pid_t pid = fork();

    if (pid == 0) {
        execv(command_path, args);
        perror("Execution failed");
        free(command_path);
        exit(1);
    } else if (pid > 0) {
        int status;
        wait(&status);
        free(command_path);
        return WEXITSTATUS(status);
    } else {
        perror("Fork failed");
        free(command_path);
        return -1;
    }
}

int main() {
    char input[MAX_INPUT_LENGTH];
    char *args[MAX_ARGS];
    int num_args;

    while (1) {
        printf("SimpleShell> ");

        fgets(input, MAX_INPUT_LENGTH, stdin);

        input[strlen(input) - 1] = '\0';

        if (strcmp(input, "exit") == 0) {
            break;
        }

        char *token = strtok(input, " ");
        num_args = 0;

        while (token != NULL) {
            args[num_args++] = token;
            token = strtok(NULL, " ");
        }

        args[num_args] = NULL;

        if (args[0] != NULL && access(args[0], X_OK) == 0) {
            int result = execute_command(args);
            if (result == -1) {
                printf("Failed to execute command\n");
            }
        } else {
            printf("Command '%s' not found\n", args[0]);
        }
    }

    return 0;
}
