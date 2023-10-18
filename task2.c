#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void) {
    char *command = NULL;
    size_t len = 0;
    ssize_t read;

    while (1) {
        printf("simple_shell$ ");

        // Read a line of input
        read = getline(&command, &len, stdin);

        // Check for end of file (Ctrl+D)
        if (read == -1) {
            free(command);
            printf("\n");
            break;
        }

        // Remove trailing newline character
        if (command[read - 1] == '\n') {
            command[read - 1] = '\0';
        }

        // Execute the command
        if (access(command, X_OK) == 0) {
            pid_t pid = fork();

            if (pid == 0) {
                execlp(command, command, NULL);
                perror("Error");
                exit(EXIT_FAILURE);
            } else if (pid < 0) {
                perror("Fork failed");
            } else {
                wait(NULL);
            }
        } else {
            printf("Error: Command not found\n");
        }
    }

    return 0;
}

