#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <libgen.h>
#include <time.h>
#include <dirent.h>
#include <fcntl.h>


#define MAX_LENGTH 10
#define MAX_ARGS 10
#define BUF_SIZE 258

// Helper functions for the menus

void get_last_modification_time(char *path){

    struct stat st;
    stat(path, &st);
    char date[10];

    strftime(date, 20, "%d-%m-%y", localtime(&(st.st_ctime)));
    printf("The file %s was last modified at %s\n", path, date);
    date[0] = 0;
}

void print_disk_count(char *path) {

    struct stat st;
    stat(path, &st);

    if (stat(path, &st) == 0) {
        unsigned long long disk_count = st.st_blocks / 2;
        printf("Hard disk count of file %s: %llu KB\n", path, disk_count);
    } else {
        perror("Error getting file stats");
    }
}

void access_rights(char *path){

    struct stat st;
    stat(path, &st);

    printf("Owner permissions: \n");
    if( st.st_mode & S_IRUSR )
        printf("Read : YES \n");
        else printf("Read : NO\n");
    if( st.st_mode & S_IWUSR )
        printf("Write : YES\n");
        else printf("Write : NO\n");
    if( st.st_mode & S_IXUSR )
        printf("Execute : YES\n");
        else printf("Execute : NO\n");
    
    printf("\n");

    printf("Group permissions: \n");
    if( st.st_mode & S_IRGRP )
        printf("Read : YES\n");
        else printf("Read : NO\n");
    if( st.st_mode & S_IWGRP )
        printf("Write : YES\n");
        else printf("Write : NO\n");
    if( st.st_mode & S_IXGRP )
        printf("Execute : YES\n");
        else printf("Execute : NO\n");

    printf("\n");

    printf("Others permissions: \n");
    if( st.st_mode & S_IROTH )
        printf("Read : YES\n");
        else printf("Read : NO\n");
    if( st.st_mode & S_IWOTH )
        printf("Write : YES\n");
        else printf("Write : NO\n");
    if( st.st_mode & S_IXOTH )
        printf("Execute : Yes\n");
        else printf("Execute : NO\n");

    printf("\n");

}

void count_c_files(char *path) {

    DIR *dir;
    struct dirent *ent;
    int count = 0;
    
    dir = opendir(path);
    if (dir == NULL) {
        perror("Error opening directory");
        exit(EXIT_FAILURE);
    }
    
    while ((ent = readdir(dir)) != NULL) {
        char filename[BUF_SIZE];
        snprintf(filename, BUF_SIZE, "%s/%s", path, ent->d_name);
        struct stat st;
        if (stat(filename, &st) == -1) {
            perror("stat");
            exit(EXIT_FAILURE);
        }
        if (S_ISREG(st.st_mode)) { 
            if (strcmp(ent->d_name + strlen(ent->d_name) - 2, ".c") == 0) {
                count++;
            }
        }
    }
    printf("The number of files with the .c extension is: %d\n", count);
    closedir(dir);
}

// Print the menus for REGULAR, SYMBOLIC and DIRECTORY

void print_menu_regular_file(char *path){

    struct stat st;
    stat(path, &st);
    char option[MAX_LENGTH];

    beginning :
    printf("\n");
    printf("~~~~~~~~~~ MENU ~~~~~~~~~~\n");
    printf("\nPlease select an option:\n");
        printf("-n NAME\n");//
        printf("-d SIZE\n");//
        printf("-h HARD DISK COUNT\n");//
        printf("-m TIME OF LAST MODIFICATION\n");//
        printf("-a ACCESS RIGHTS\n");//
        printf("-l CREATE SYMBOLIC LINK\n");//
        printf("-q QUIT\n");//

    printf("\n");
    scanf("%s", option);

    for(int i = 0; i < strlen(option); ++i){
        if(option[i] == '-'){
            continue;
        }
        else if (option[i] == 'n') {
        printf("You selected the NAME option.\n");
        char* name = basename(path);
        printf("The name of the file is: %s\n", name);
    }
    else if (option[i] == 'd') {
        printf("You selected the SIZE option.\n");
        if (stat(path, &st) == 0) {
            printf("File size: %ld bytes\n", st.st_size);
        } else printf("Error getting file size\n");
    }
    else if (option[i] == 'h') {
        printf("You selected the HARD DISCK COUNT option.\n");
        print_disk_count(path);
    }
    else if (option[i] == 'm') {
        printf("You selected the TIME OF LAST MODIFICATION option.\n");
        get_last_modification_time(path);
    }
    else if (option[i] == 'a') {
        printf("You selected the ACCESS RIGHTS option.\n");
        access_rights(path);
    }
    else if (option[i] == 'l') {
        printf("You selected the CREATE SYMBOLIC LINK option.\n");
        char symbolic[100];
        scanf("%s", symbolic);
        if (symlink(path, symbolic) == -1) {
           perror("symlink");
           exit(EXIT_FAILURE);
        }
    }
    else if (option[i] == 'q') {
        printf("You selected the QUIT option. \n");
        printf("Goodbye!! :D\n");
    }
    else if(option[i] != '-' || option[i] != 'n' || option[i] != 'd' || option[i] != 'h' ||
            option[i] != 'm' || option[i] != 'a' || option[i] != 'l' || option[i] != 'q' ) {
        printf("Invalid option. Please try again.\n");
        goto beginning;
        }
    }
    printf("\n");
}

void print_menu_symbolic_file(char *path){

    struct stat st;
    stat(path, &st);
    int ret;
    char option[MAX_LENGTH];

    beginning :
    printf("\n");
    printf("~~~~~~~~~~ MENU ~~~~~~~~~~\n");
    printf("\nPlease select an option:\n");
        printf("-n NAME\n");//
        printf("-d SIZE OF SYMBOLIC LINK\n");//
        printf("-t SIZE OF TARGET FILE\n");//
        printf("-a ACCESS RIGHTS\n");//
        printf("-l DELETE SYMBOLIC LINK\n");//
        printf("-q QUIT\n");//

    scanf("%s", option);
    printf("\n");

    for(int i = 0; i < strlen(option); ++i){
        if(option[i] == '-')
            continue;
        if (option[i] == 'n') {
        printf("You selected the NAME option.\n");
        char* name = basename(path);
        printf("The name of the file is: %s\n", name);
    }
    else if (option[i] == 'd') {
        printf("You selected the SIZE OF SYMBOLIC LINK option.\n");
        if (stat(path, &st) == 0) {
            printf("File size: %ld bytes\n", st.st_size);
        } else printf("Error getting file size\n");
    }
    else if (option[i] == 't') {
        printf("You selected the SIZE OF TARGET FILE option.\n");
        if (ret == -1){
            perror("lstat");
            exit(EXIT_FAILURE);
        }
        ret = stat(path, &st);

        if (ret == -1){
            perror("stat");
            exit(EXIT_FAILURE);
        }
        printf("Size of target file: %ld bytes\n", st.st_size);
    }
    else if (option[i] == 'a') {
        printf("You selected the ACCESS RIGHTS option.\n");
        access_rights(path);
    }
    else if (option[i] == 'l') {
        printf("You selected the DELETE SYMBOLIC LINK option.\n");

        if (unlink(path) == 0) {
            printf("File deleted successfully!\n");
        } else {
            printf("Error deleting file!\n");
            exit(EXIT_FAILURE);
        }
    }
    else if (option[i] == 'q') {
        printf("You selected the QUIT option.\n");
        printf("Goodbye!! :D \n");
    }
    else if(option[i] != '-' || option[i] != 'n' || option[i] != 'd' || option[i] != 'h' ||
            option[i] != 'm' || option[i] != 'a' || option[i] != 'l' || option[i] != 'q' ) {
            printf("Invalid option. Please try again.\n");
            goto beginning;
        }
    }
     
    printf("\n");
}

void print_menu_directory(char *path){

   struct stat st;
   stat(path, &st);
   char option[MAX_LENGTH];

   beginning :
   printf("\n");
   printf("~~~~~~~~~~ MENU ~~~~~~~~~~\n");
   printf("\nPlease select an option:\n");
        printf("-n NAME\n");//
        printf("-d SIZE\n");//
        printf("-a ACCESS RIGHTS\n");//
        printf("-c NUMBER OF FILES WITH THE .C EXTENTION\n");//
        printf("-q QUIT\n");//

    scanf("%s", option);

    for(int i = 0; i < strlen(option) ; ++i){
        if(option[i] == '-') continue;

        if(option[i] == 'n'){
            printf("You selected the name option.\n");
            char* name = basename(path);
            printf("The name of the file is: %s\n", name);
        }
        else if(option[i] == 'd'){
            printf("You selected the SIZE OF DIRECTORY option.\n");
            if(stat(path, &st) == 0){
                printf("File size: %ld bytes\n", st.st_size);
            } else printf("Error getting file size\n");
        }
        else if(option[i] == 'a'){
            printf("You selected the ACCESS RIGHTS option.\n");
            access_rights(path);
        }
        else if(option[i] == 'c'){
            printf("You selected the NUMBER OF FILES WITH THE .C EXTENTION option.\n");
            count_c_files(path);
        }
        else if(option[i] == 'q'){
            printf("You selected the QUIT option.\n");
            printf("Goodbye!! :D \n");
        }
        else if(option[i] != '-' || option[i] != 'n' || option[i] != 'd' || option[i] != 'a' ||
                option[i] != 'c' || option[i] != 'q'){
            printf("Invalid option. Please try again.\n");
            goto beginning;
        }
    }
    printf("\n");
}

// Function where the menu handling happens

void print_file_info(char *path) {

    struct stat st;
    stat(path, &st);
    char type;
    
    if (lstat(path, &st) == -1) {
        perror(path);
        exit(EXIT_FAILURE);
    }
    
    if (S_ISREG(st.st_mode)) {
        type = 'R';
    } else if (S_ISLNK(st.st_mode)) {
        type = 'L';
    } else if (S_ISDIR(st.st_mode)) {
        type = 'D';
    } else {
        type = '-';
    }
    
    printf("%s - %s\n", path, (type == 'R') ? "REGULAR FILE" :
           ((type == 'L') ? "SYMBOLIC LINK" : (type == 'D') ? 
           "DIRECTORY" : "OTHER"));

    if(type == 'R'){
        print_menu_regular_file(path);

    }
    else if(type == 'L'){
        print_menu_symbolic_file(path);
    }
    else if(type == 'D'){
        print_menu_directory(path);
    }
}

// Helper functions for the 2nd child process

void write_result_to_file(char *path, int score) {
    
    int fd = open("grades.txt", O_WRONLY | O_CREAT, 0644);
    if (fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    // Write the result to the file descriptor
    char buffer[256];
    int n = snprintf(buffer, sizeof(buffer), "%s: %d\n", path, score);
    if (write(fd, buffer, n) != n) {
        perror("write");
    }

    close(fd);
}


void count_lines(char *path){
    
    int num_lines = 0;
    char buffer[1000];
    ssize_t bytes_read;

    int fd = open(path, O_RDONLY);
    if (fd < 0) {
        printf("Error opening file %s\n", path);
        exit(EXIT_FAILURE);
    }

    while ((bytes_read = read(fd, buffer, sizeof(buffer))) > 0) {
        for (int i = 0; i < bytes_read; ++i) {
            if (buffer[i] == '\n') {
                num_lines++;
            }
        }
    }

    close(fd);
    printf("File %s has %d lines\n", path, num_lines);
}

void create_file(char *path) {

    char filename[strlen(path) + 11]; 
    sprintf(filename, "%s_file.txt", path);

    int fd = open(filename, O_WRONLY | O_CREAT, 0644);
    if (fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    close(fd);
}

void change_permissions(char *path) {

    struct stat st;
    stat(path, &st);

    if (lstat(path, &st) == -1) {
        perror("lstat");
        exit(EXIT_FAILURE);
    }

    mode_t permissions = S_IRWXU | S_IWGRP;
    if (chmod(path, permissions) == -1) {
        perror("chmod");
        exit(EXIT_FAILURE);
    }
    printf("Changed the symbolic file's permissions\n");
}

// Function where the file type handling happens

void run_script(char *path){

    struct stat st;
    stat(path, &st);
    size_t len = strlen(path);
    char type;

    if (lstat(path, &st) == -1) {
        perror(path);
        exit(EXIT_FAILURE);
    }
    
    if (S_ISREG(st.st_mode)) {
        type = 'R';
    } else if (S_ISLNK(st.st_mode)) {
        type = 'L';
    } else if (S_ISDIR(st.st_mode)) {
        type = 'D';
    } else {
        type = '-';
    }

    if(type == 'R'){
        // if file has .c extension
        if (len >= 2 && strcmp(path + len - 2, ".c") == 0){
            // compute score...
            char cmd[256];
            snprintf(cmd, sizeof(cmd), "./script.sh %s", path);

            // Open the pipe for reading the output of the script
            FILE *pipe_fp = popen(cmd, "r");
                if (pipe_fp == NULL) {
                    perror("popen");
                    exit(EXIT_FAILURE);
                }

            // Read the output of the script
            char buffer[256];
            int num_warnings = 0, num_errors = 0;
            while (fgets(buffer, sizeof(buffer), pipe_fp) != NULL) {
                    if (strstr(buffer, "warning")) {
                        num_warnings++;
                    }
                    if (strstr(buffer, "error")) {
                        num_errors++;
                    }
                printf("%s", buffer);
            }

            // Close the pipe
            pclose(pipe_fp);

            // Compute the score based on the number of errors and warnings
            int score;
            if (num_errors == 0 && num_warnings == 0) {
                score = 10;
            } else if (num_errors > 0) {
                    score = 1;
                } else if (num_warnings > 10) {
                        score = 2;
                    } else {
                        score = 2 + 8 * (10 - num_warnings) / 10;
                        }

            // Write the result to the grades.txt file
            write_result_to_file(path, score);
        }
        else{
            // If file is regular but not a .c file
            printf("File %s is NOT a .c file\n", path);
            count_lines(path);
        }

    }
    else if(type == 'L'){
        change_permissions(path);
    }
    else if(type == 'D'){
        create_file(path);
    }

}

// Functions that represent what each child process is going to do

void child1(char *path) {

    print_file_info(path);
    exit(11);
}

void child2(char *path) {

    run_script(path);
    exit(22);
}

int main(int argc, char* argv[]) {
    
    for (int i = 1; i < argc; ++i) {
       
        pid_t pid1, pid2;

        // Create the first child process
        pid1 = fork();
        if (pid1 == 0) {
            //The first child process
            child1(argv[i]);
            exit(EXIT_SUCCESS);
        } else if (pid1 < 0) {
            
            printf("Error creating first child process\n");
            exit(EXIT_FAILURE);
        }

        // Create the second child process
        pid2 = fork();
        if (pid2 == 0) {
            //The second child process
            child2(argv[i]);
            exit(EXIT_SUCCESS);
        } else if (pid2 < 0) {
            printf("Error creating second child process\n");
            exit(EXIT_FAILURE);
        }

        // Wait for both child processes to finish
        int status1, status2;
        waitpid(pid1, &status1, 0);
        printf("The process with PID %d has ended with the exit code %d\n\n", pid1, WEXITSTATUS(status1));

        waitpid(pid2, &status2, 0);
        printf("The process with PID %d has ended with the exit code %d\n\n", pid2, WEXITSTATUS(status2));

    }

    return 0;
}