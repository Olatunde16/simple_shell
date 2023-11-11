#include "main.h"

void tokenize_input(char *input, char *args[]) {
    int num_args = 0;
    char *token = input;
    
    while (*token != '\0') {
        while (*token == ' ' || *token == '\t' || *token == '\n') {
            *token = '\0';
            token++;
        }

        args[num_args++] = token;

        while (*token != '\0' && *token != ' ' && *token != '\t' && *token != '\n') {
            token++;
        }
    }

    args[num_args] = NULL;
}

int execute_command(char *args[]) {
    pid_t pid = fork();

    if (pid == 0) {
        execvp(args[0], args);

        perror("Command not found");

        exit(1);
    } else if (pid > 0) {
        int status;
        wait(&status);

        return WEXITSTATUS(status);
    } else {
        perror("Fork failed");
        return -1;
    }
}

int main(void) {
    char input[MAX_INPUT_LENGTH];
    char *args[MAX_ARGS];

    while (1) {
        printf("SimpleShell> ");

        fgets(input, MAX_INPUT_LENGTH, stdin);

        input[strlen(input) - 1] = '\0';

        if (strcmp(input, "exit") == 0) {
            break;
        }

        tokenize_input(input, args);

        int result = execute_command(args);

        if (result == -1) {
            printf("Command not found\n");
        }
    }

    return 0;
}
