#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>

int main(int argc, char **argv) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s file1 file2 ...\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    pid_t pid;
    int score = 0;

    for (int i = 1; i < argc; i++) {
        pid = fork();

        if (pid == -1) {
            perror("fork");
            exit(EXIT_FAILURE);
        }

        if (pid == 0) {
            // Child process
            char *file = argv[i];

            // Check if the file is a regular file with .c extension
            if (access(file, F_OK) == -1 || access(file, R_OK) == -1) {
                exit(EXIT_FAILURE);
            }

            char *ext = strrchr(file, '.');
            if (ext == NULL || strcmp(ext, ".c") != 0) {
                exit(EXIT_FAILURE);
            }

            // Execute the script and send the output to the parent process
            int pipefd[2];
            if (pipe(pipefd) == -1) {
                perror("pipe");
                exit(EXIT_FAILURE);
            }

            pid_t pid2 = fork();
            if (pid2 == -1) {
                perror("fork");
                exit(EXIT_FAILURE);
            }

            if (pid2 == 0) {
                // Child process
                close(pipefd[0]); // Close read end of the pipe

                // Redirect stdout to the write end of the pipe
                if (dup2(pipefd[1], STDOUT_FILENO) == -1) {
                    perror("dup2");
                    exit(EXIT_FAILURE);
                }

                // Execute the script
                if (execlp("./script.sh", "./script.sh", file, NULL) == -1) {
                    perror("execlp");
                    exit(EXIT_FAILURE);
                }
            } else {
                // Parent process
                close(pipefd[1]); // Close write end of the pipe

                // Read the output from the script
                char buf[1024];
                int num_read = read(pipefd[0], buf, 1023);
                buf[num_read] = '\0';

                // Compute the score based on the output
                int errors = 0, warnings = 0;
                char *ptr = buf;

                while (*ptr != '\0') {
                    if (strncmp(ptr, "error:", 6) == 0) {
                        errors++;
                    } else if (strncmp(ptr, "warning:", 8) == 0) {
                        warnings++;
                    }
                    ptr = strchr(ptr, '\n');
                    if (ptr == NULL) {
                        break;
                    }
                    ptr++;
                }

                if (errors == 0 && warnings == 0) {
                    score += 10;
                } else if (errors >= 1) {
                    score += 1;
                } else if (warnings > 10) {
                    score += 2;
                } else {
                    score += 2 + (8 * (10 - warnings)) / 10;
                }

                // Write the result to the grades.txt file
                char *grade_str;
                vsprintf(&grade_str, "%s: %d\n", file, score);

                FILE *fp = fopen("grades.txt", "a");
                if (fp == NULL) {
                    perror("fopen");
                    exit(EXIT_FAILURE);
                }

               
