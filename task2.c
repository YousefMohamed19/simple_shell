#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_COMMAND_LENGTH 100

void executeCommand(char* command) {
    if (system(command) == -1) {
        perror("Error executing command");
    }
}

int main() {
    char command[MAX_COMMAND_LENGTH];

    while (1) {
        printf("#cisfun$ ");
        if (fgets(command, MAX_COMMAND_LENGTH, stdin) == NULL) {
            printf("\n");
            break; // End of file condition (Ctrl+D)
        }

        // Remove trailing newline character
        command[strcspn(command, "\n")] = '\0';

        if (strcmp(command, "exit") == 0) {
            break;
        }

        executeCommand(command);
    }

    return 0;
}

