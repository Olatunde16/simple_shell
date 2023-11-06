#include "main.h"
/**
    * main -
    * custom_getline:
    *
    * Return: Always 0
    */

char *custom_getline() 
{
    static char buffer[MAX_INPUT_LENGTH];
    static size_t pos = 1;
    static size_t size = 1;

    while (1) {
        if (pos >= size) {
            size_t bytesRead = read(STDIN_FILENO, buffer, sizeof(buffer));
            if (bytesRead <= 0) {
                return NULL;
            }
            size = bytesRead;
            pos = 0;
        }

        while (pos < size && buffer[pos] != '\n') {
            pos++;
        }

        if (pos < size) { // Found a newline character
            buffer[pos] = '\0';
            char *line = buffer;
            pos++;
            return line;
        } else if (size == sizeof(buffer) - 1) { 
            buffer[size] = '\0';
            char *line = buffer;
            pos = size;
            size = 0;
            return line;
        }
    }
}

int main() {
    while (1) {
        printf("Simple-Shell> ");
        char *line = custom_getline();

        if (line == NULL) {
            printf("Exiting...\n");
            break;
        }

        printf("You entered: %s\n", line);
    }

    return 0;
}
