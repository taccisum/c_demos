#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int test() {
    int a = 1;
    int b = 2;
    int c = 3;
    int d = 4;
    int e = 5;
    return a + b + c + d + e;
}

int add(int a, int b, int c) {
    return a + b + c;
}

int main(int argc,char *argv[]) {
    printf("%d\n", test());

    int *ptr = malloc(sizeof(int));
    int x;
    printf("code addr: %p\n", &main);
    printf("heap addr: %p\n", ptr);
    printf("stack addr: %p\n", &x);
    printf("func add() addr: %p\n", &add);
    printf("call func add(), result: %d\n", add(1,2,3));
}

