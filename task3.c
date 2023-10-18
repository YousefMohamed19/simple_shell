#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

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

        // Tokenize the command and arguments
        char *args[10];  // Assuming max 10 arguments
        char *token = strtok(command, " ");
        int arg_count = 0;

        while (token != NULL) {
            args[arg_count++] = token;
            token = strtok(NULL, " ");
        }
        args[arg_count] = NULL;

        // Execute the command
        if (access(args[0], X_OK) == 0) {
            pid_t pid = fork();

            if (pid == 0) {
                execvp(args[0], args);
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

