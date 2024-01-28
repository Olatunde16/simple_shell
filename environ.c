#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

// Declaration for the environment variables
extern char **environ;

int main() {
    // Print environment variables
    char **env = environ;
    while (*env != NULL) {
        printf("%s\n", *env);
        env++;
    }

    return 0;
}
