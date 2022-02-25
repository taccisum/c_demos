#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <dirent.h>

int main(int argc,char *argv[]) {
    char *fp = argv[1];     // file path
    FILE *f;
    char buf[128];

    printf("open file: %s\n", fp);
    if((f = fopen(fp, "r")) == NULL) {
        perror("fail to open file.");
    }

    int n;
    while((n = fread(buf, sizeof(char), 128, f)) > 0) {
        fwrite(buf, sizeof(char), n, stdout);
    }

    fclose(f);
}
