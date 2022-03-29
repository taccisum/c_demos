#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>

int idx = 0;
char *str;
int lookahead;

void err();


/* symbol table start */
/* use simple linear array structure */

/* symbol entry */
struct sym_ent {
    int tk; /* lex token */
    char *lex_ptr; /* lex pointer */
};

struct sym_ent sym_tbl[999];        /* symbol table */
int nava = 1;    /* next avaiable index, init 1(zero as default) */

void insert(int token, char *lex);
int lookup(char *lex);

/* insert a new token into symbol table */
void insert(int token, char *lex) {
    if (lookup(lex) != 0) {
        /* exists token, pass */
        return;
    }
    printf("tk %d, lex %s\n", token, lex);
    sym_tbl[nava].tk = token;
    sym_tbl[nava].lex_ptr = lex;
    nava++;     /* index +1 */
}

/* lookup token from symbol table by lex */
int lookup(char *lex) {
    printf("lookup %s\n", lex);
    for (int i = 1; i < nava; i++) {
        struct sym_ent ent = sym_tbl[i];
        printf("entry: tk: %d, lex: %s\n", ent.tk, ent.lex_ptr);
        if(strcmp(ent.lex_ptr, lex) == 0) {
            return ent.tk;
        }
    }
    return 0;
}

/* symbol table end */

/* get a char */
char gc() {
    return str[idx++];
}

/* unget a char */
void ugc() {
    idx--;
}

/* read a num sequence from input */
int lexan() {
    int c;
    int tv;

    while(1) {
        c = gc();
        if(c == ' ' || c == '\t') {
            continue;
        } else if (c == '\n') {
            continue;
        } else if (isdigit(c)) {
            tv = c - '0';
            c = gc();
            while(isdigit(c)) {
                tv = tv * 10 + (c - '0');
                c = gc();
            }
            ugc();
            break;
        } else {
            tv = 0;
            break;
        }
    }

    return tv;
}

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
    int num = lexan();
    printf("%d", num);
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

#ifndef __ut
#define NUM 1

int main(int argc,char *argv[]) {
    /* do init start */

    /* built-in lexes */
    insert(NUM, "NUM");

    str = malloc(256 * sizeof(char));
    char *ori = argv[1];
    /* ori = "123 567 890"; */
    strcpy(str, ori);
    str[strlen(ori)] = '\0';
    /* do init end */

    expr();
}
#endif

