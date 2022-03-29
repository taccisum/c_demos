#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>

char *str;
int idx;
int lookahead;

void err();

void match(int t) {
    if(lookahead == t) {
        idx++;
        lookahead = str[idx];
    } else {
        err();
    }
}

void err() {
    printf("error\n");
    exit(1);
}

void term() {
    /* term -> [0-9] */
    if(isdigit(lookahead)) {
        printf("%c", lookahead);
        match(lookahead);
    } else {
        err();
    }
}

void rest() {
    /* 
       rest -> + term { printf '+' } rest
             | - term { printf '-' } rest
             | expty_set
     */
    if(lookahead == '+') {
        match('+'); term(); printf("+"); rest();
    } else if(lookahead == '-') {
        match('-'); term(); printf("-"); rest();
    } else {
        /* do nothing */
    }
}

void expr() {
    /* expr -> term rest */
    term(); rest();
}

int main(int argc,char *argv[]) {
    str = malloc(256 * sizeof(char));
    strcpy(str, argv[1]);
    str[strlen(argv[1])] = '\0';
    idx = 0;

    lookahead = str[idx];
    expr();
}

