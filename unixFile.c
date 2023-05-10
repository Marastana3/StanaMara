#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include<sys/wait.h>
#include <unistd.h>
#include <libgen.h>
#include <time.h>
#include <dirent.h>

#define _DEFAULT_SOURCE
#define MAX_LENGTH 10

void get_last_modification_time(char *path){
    struct stat st;
    stat(path, &st);
    char date[10];
    strftime(date, 20, "%d-%m-%y", localtime(&(st.st_ctime)));
    printf("The file %s was last modified at %s\n", path, date);
    date[0] = 0;
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
        exit(1);
    }
    
    while ((ent = readdir(dir)) != NULL) {
        if (ent->d_type == DT_REG) { 
            if (strcmp(ent->d_name + strlen(ent->d_name) - 2, ".c") == 0) {
                count++;
            }
        }
    }
    printf("The number of files with the .c extention is: %d\n", count);
    closedir(dir);
}

void print_menu_regular_file(char *path){
    struct stat st;
    char option[MAX_LENGTH];

    beginning :
    printf("\n");
    printf("~~~~~~~~~~ MENU ~~~~~~~~~~\n");
    printf("\nPlease select an option:\n");
        printf("-n NAME\n");//
        printf("-d SIZE\n");//
        printf("-h HARD DISK COUNT\n");
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
           exit(1);
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

}

void print_menu_symbolic_file(char *path){
    struct stat st;
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

    for(int i = 0; i <= strlen(option); ++i){
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
            exit(1);
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
     

}

void print_menu_directory(char *path){
   struct stat st;
   char option[MAX_LENGTH];

   beginning :
   printf("\n");
   printf("\nPlease select an option:\n");
        printf("-n NAME\n");
        printf("-d SIZE\n");
        printf("-a ACCESS RIGHTS\n");
        printf("-c NUMBER OF FILES WITH THE .C EXTENTION\n");
        printf("-q QUIT\n");

    scanf("%s", option);

    for(int i = 0; i <= strlen(option) ; ++i){
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

}


void print_file_info(char *path) {
    struct stat st;
    char type;
    
    if (lstat(path, &st) == -1) {
        perror(path);
        exit(1);
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

int main(int argc, char* argv[]) {
    
    if (argc <= 1) {
        printf("Error, incorrect number of arguments!\n");
        exit(1);
    }
    print_file_info(argv[1]);

      // Check if the file exists and is a regular file
    struct stat sb;
    if (stat(argv[1], &sb) == -1) {
        perror("stat");
        return 1;
    }

    if (!S_ISREG(sb.st_mode)) {
        fprintf(stderr, "%s is not a regular file\n", argv[1]);
        return 1;
    }

    // Check if the file extension is .c
    char *ext = strrchr(argv[1], '.');
    if (ext == NULL || strcmp(ext, ".c") != 0) {
        fprintf(stderr, "%s is not a C file\n", argv[1]);
        return 1;
    }

    // Create a child process to compile the file
    pid_t pid = fork();
    if (pid == -1) {
        perror("fork");
        return 1;
    } else if (pid == 0) {
        // Child process
        execlp("gcc", "gcc", "-o", "/dev/null", "-Wall", "-Werror", argv[1], NULL);
        perror("execlp");
        exit(1);
    }

    // Wait for the child process to finish and get its exit status
    int status;
    if (waitpid(pid, &status, 0) == -1) {
        perror("waitpid");
        return 1;
    }

    // Print the number of errors and warnings
    if (WIFEXITED(status)) {
        int exit_status = WEXITSTATUS(status);
        int errors = exit_status & 0xff;
        int warnings = (exit_status >> 8) & 0xff;
        printf("Errors: %d\n", errors);
        printf("Warnings: %d\n", warnings);
    }

    return 0;
}