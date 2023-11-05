#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main() {
    char* input;
    char command[256];
    char* path = getenv("PATH")

	    if (path != NULL) {
        char* token = strtok(path, ":");
        while (token != NULL) {
            char full_path[512];
            snprintf(full_path, sizeof(full_path), "%s/%s", token, command);

            if (access(full_path, X_OK) == 0) {
                // Command found in the PATH
                snprintf(command, sizeof(command), "%s", full_path);
                break;
            }

            token = strtok(NULL, ":");
        }
    }

    // Execute the command if found, otherwise print an error
    if (access(command, X_OK) == 0) {
        system(command);
    } else {
        printf("Command not found or not executable.\n");
    }

    return 0;
}
