#include <stdio.h>
#include <unistd.h>

#define MAX_INPUT_LENGTH 1024

char *custom_getline() {
    static char buffer[MAX_INPUT_LENGTH];
    static size_t pos = 0;
    static size_t size = 0;

    while (1) {
        // Check if we need to read more data into the buffer
        if (pos >= size) {
            size_t bytesRead = read(STDIN_FILENO, buffer, sizeof(buffer));
            if (bytesRead <= 0) {
                return NULL; // End of input or error
            }
            size = bytesRead;
            pos = 0;
        }

        // Look for a newline character
        while (pos < size && buffer[pos] != '\n') {
            pos++;
        }

        if (pos < size) { // Found a newline character
            buffer[pos] = '\0'; // Replace newline with null terminator
            char *line = buffer;
            pos++;
            return line;
        } else if (size == sizeof(buffer) - 1) { // Line too long, split it
            buffer[size] = '\0'; // Add null terminator
            char *line = buffer;
            pos = size;
            size = 0; // Force reading new input
            return line;
        }
    }
}

int main() {
    while (1) {
        printf("SimpleShell> ");
        char *line = custom_getline();

        if (line == NULL) {
            printf("Exiting...\n");
            break;
        }

        printf("You entered: %s\n", line);
    }

    return 0;
}
