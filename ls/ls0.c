#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <dirent.h>

int main(int argc,char *argv[]) {
    char dir_path[128];
    memset(dir_path, '\0', sizeof(dir_path));
    getcwd(dir_path, 128);
    printf("current dir: %s\n", dir_path);

    DIR *dir = opendir(dir_path);
    if (dir == NULL) {
        perror("open dir error.");
        exit(1);
    } else {
        struct dirent *dir_info;
        while((dir_info = readdir(dir)) != NULL) {
            if(strcmp(dir_info->d_name, ".") == 0 || strcmp(dir_info->d_name, "..") == 0) {
                /* ignore . & .. */
                continue;
            } else {
                printf("%s\n", dir_info->d_name);
            }
        }
        closedir(dir);
    }

}


