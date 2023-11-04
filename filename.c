#include "main.h"

void execute_command(char *args[]) 
{
    pid_t pid = fork();

    if (pid == 0) 
    {
        execvp(args[0], args);
        perror("Command not found");
        exit(1);
    } 
    
    else if (pid > 0) 
    {
        int status;
        wait(&status);

        if (WIFEXITED(status)) 
        {
            printf("Child process exited with status %d\n", WEXITSTATUS(status));
        }
    } 
    
    else 
    {
        perror("Fork failed");
    }
}

void execute_commands_from_file(const char *filename) 
{
    FILE *file = fopen(filename, "r");
    if (file == NULL) 
    {
        perror("Error opening file");
        return;
    }

    char line[MAX_INPUT_LENGTH];

    while (fgets(line, sizeof(line), file) != NULL) 
    {
        line[strlen(line) - 1] = '\0';

        char *args[MAX_ARGS];
        int num_args = 0;
        char *token = strtok(line, " ");

        while (token != NULL) 
        {
            args[num_args++] = token;
            token = strtok(NULL, " ");
        }

        args[num_args] = NULL;

        execute_command(args);
    }

    fclose(file);
}

int main(int argc, char *argv[]) 
{
    if (argc == 2) 
    {
        execute_commands_from_file(argv[1]);
    } 
    
    else if (argc > 2) 
    {
        printf("Usage: %s [filename]\n", argv[0]);
        return 1;
    } 
    
    else 
    {
        char input[MAX_INPUT_LENGTH];

        while (1) 
        {
            printf("simple_shell> ");

            if (fgets(input, MAX_INPUT_LENGTH, stdin) == NULL) 
            {
                printf("\nExiting...\n");
                break;
            }

            input[strlen(input) - 1] = '\0';

            char *args[MAX_ARGS];
            int num_args = 0;
            char *token = strtok(input, " ");

            while (token != NULL) 
            {
                args[num_args++] = token;
                token = strtok(NULL, " ");
            }

            args[num_args] = NULL;

            execute_command(args);
        }
    }

    return 0;
}
