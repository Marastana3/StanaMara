#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include<sys/wait.h>
#include <unistd.h>
#include <libgen.h>
#include <time.h>

#define MAX_LENGTH 2

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
            option[i] != 'm' || option[i] !='a' || option[i] != 'l' || option[i] != 'q' ) {
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
            option[i] != 'm' || option[i] !='a' || option[i] != 'l' || option[i] != 'q' ) {
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
    printf("~~~~~~~~~~ MENU ~~~~~~~~~~\n");
    printf("\nPlease select an option:\n");
        printf("-n NAME\n");//
        printf("-d SIZE\n");//
        printf("-a ACCESS RIGHTS\n");//
        printf("-c NUMBER OF FILES WITH THE .C EXTENSION\n");
        printf("-q Quit\n");//

    scanf("%s", option);

    for(int i = 0; i <= strlen(option); ++i){
        if(option[i] == '-') {
            continue;
        }
        if (option[i] == 'n') {
        printf("You selected the NAME option.\n");
         char* name = basename(path);
         printf("The name of the file is: %s\n", name);
    }
    else if (option[i] == 'd') {
        printf("You selected the SIZE OF DIRECTORY option.\n");
        if (stat(path, &st) == 0) {
            printf("File size: %ld bytes\n", st.st_size);
        } else printf("Error getting file size\n");
    }
    else if (option[i] == 'a') {
        printf("You selected the ACCESS RIGHTS option.\n");
        access_rights(path);
    }
    else if (option[i] == 'c') {
        printf("You selected the NUMBER OF FILES WITH THE .c EXTENSION option.\n");
    }
    else if (option[i] == 'q') {
        printf("You selected the QUIT option.\n");
        printf("Goodbye!! :D \n");
    }
    else if(option[i] != '-' || option[i] != 'n' || option[i] != 'd' || option[i] != 'a' || option[i] != 'c' || option[i] !='q'){
        printf("Invalid option. Please try again.\n");
        goto beginning;   
        }
    }
}

void create_child_process(){
    pid_t pid, w;
    pid = fork();
    int wstatus;

    if(pid<0) {
        printf("error fork()");
        exit(1);
    }
    
    if(pid==0) {
        printf("this is the child process with pid %d \n", getpid());
        
        //execute script:

        exit(5);
    }
    else {
        if(pid>0) {
            printf("this is the parent process\n");
            w = wait(&wstatus);
            if(WIFEXITED(wstatus)) {
                printf("process with pid %d, exited, status = %d\n", w, WEXITSTATUS(wstatus));
            }
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
        create_child_process();

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
    return 0;
}
