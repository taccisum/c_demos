#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <dirent.h>

int main(int argc,char *argv[]) {
    fputs("Yes or No?(y/n): ", stdout);
    while(1) {
        int answer = fgetc(stdin);
        if(answer == 'y') {
            printf("Yes!");
            exit(0);
        } else if (answer == 'n'){
            printf("No!");
            exit(-1);
        } else {
            // ignore unknown input
            continue;
        }
    }
}









