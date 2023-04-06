#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#define MAX_LENGTH 1

void print_file_info(const char *path) {
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
}

void print_menu_regular_file(char* argv[]){
    char option[MAX_LENGTH];
    printf("~~~~~~~~~~ MENU ~~~~~~~~~~\n");
    
     do {
        printf("\nPlease select an option:\n");
        printf("-n NAME\n");
        printf("-d SIZE\n");
        printf("-h HARD DISK COUNT\n");
        printf("-m TIME OF LAST MODIFICATION\n");
        printf("-a ACCESS RIGHTS\n");
        printf("-l CREATE SYMBOLIC LINK\n");
        printf("-q Quit\n");

        for(int i = 0; i < MAX_LENGTH; ++i){
            scanf("%c", &option[i]);
        }

        switch(option[1]) {
            case 'n':
                printf("You selected NAME .\n");
                break;
            case 'd':
                printf("You selected SIZE.\n");
                break;
            case 'h':
                printf("You selected HARD DISK COUNT\n");
                break;
            case 'm':
                printf("You selected TIME OF LAST MODIFICATION .\n");
                break;
            case 'a':
                printf("You selected ACCESS RIGHTS .\n");
                break;
            case 'l':
                printf("You selected CREATE SYMBOLIC LINK .\n");
                break;
            case 'q':
                printf("Goodbye!\n");
                break;
            default:
                printf("Invalid option. Please try again.\n");
        }
    } while (option != 'q');

}

int main(int argc, char* argv[]) {
    if (argc <= 1) {
        printf("Error, incorrect number of arguments!\n");
        exit(1);
    }
    print_file_info(argv[1]);
    print_menu_regular_file(argv[1]);
    return 0;
}
//check for input string, if letter not valid option --> error message + re-print menu