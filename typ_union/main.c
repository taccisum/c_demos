#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <termios.h>
#include <string.h>

typedef union Fruit 
{
    // fields type & name stored at the same memory area.
    int type;
    char* name;
} fruit_u;

int main(int argc,char *argv[]) {
    fruit_u apple;
    // only one field has val anytime.
    apple.type = 0;
    printf("fruit type: %d\n", apple.type);
    printf("fruit name: %s\n", apple.name);

    // change field 'name' will cause unexpected val of field 'type'
    apple.name = "apple";
    printf("fruit type: %d\n", apple.type);
    printf("fruit name: %s\n", apple.name);
}
