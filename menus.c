#include <stdio.h>
#include <string.h>

int main(void){
    char *option = "-nadt";

    for(int i = 0; i < strlen(option); ++i){
        if(option[i] == 'n'){
            printf("Name\n");
        }
        if(option[i] == 'a'){
            printf("Access\n");
        }
    }
    return 0;
}