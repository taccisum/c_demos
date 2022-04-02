#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>

#define ERR_BUF_NO 1
#define UNKNOWN_PATTERN 2
#define SOURCE_NULL 3

#define BUF_1 1
#define BUF_2 2
#define BUF_LENGTH 1024
#define BUF_SIZE BUF_LENGTH - 1

#define ID 1
#define NUM 2
#define OPER 3

char *source; int now;

/* left pointer, right pointer */
int l, r;
int lp, rp;
int tk; char *tkv;
char buf1[BUF_LENGTH], buf2[BUF_LENGTH];

/* get token display name */
char* _tks() {
    switch(tk) {
        case ID:
            return "ID";
        case NUM:
            return "Number";
        case OPER:
            return "Operator";
        default:
            return "Unknown";
    }
}

void _initbuf () {
    l = 0, r = 0;
    lp = BUF_1, rp = BUF_1;
    buf1[BUF_LENGTH - 1] = EOF;
    buf2[BUF_LENGTH - 1] = EOF;
}

int _rbuf(int no) {
    if (source == NULL) {
        return 1;
    }
    if (no == BUF_1) {
        strncpy(buf1, source + now, BUF_SIZE);
        now += BUF_SIZE;
    } else if (no == BUF_2) {
        strncpy(buf2, source + now, BUF_SIZE);
    } else {
        exit(ERR_BUF_NO);
    }
    return 0;
}

void init(char *str) {
    source = str; now = 0;
    _initbuf();
    int r = _rbuf(BUF_1);
    if(r != 0) {
        if (r == 1) {
            exit(SOURCE_NULL);
        }
    }
}

char gc() {
    char c;
    if (rp == BUF_1) {
        c = buf1[r];
        if (c == EOF) {
            /* reach end of buf1 */
            _rbuf(BUF_2);
            rp = BUF_2;
            r = 0;
            /* redo gc() */
            c = gc();
        }
    } else if (rp == BUF_2) {
        c = buf2[r];
        if (c == EOF) {
            /* reach end of buf2 */
            _rbuf(BUF_1);
            rp = BUF_1;
            r = 0;
            /* redo gc() */
            c = gc();
        }
    } else {
        exit(ERR_BUF_NO);
    }
    r++;
    return c;
}

void ugc() {
    r--;
}

/* take lexeme between pointers */
void take() {
    /* printf("l %d, r %d\n", l, r); */
    if(lp == rp) {
        int len = r-l;
        char *lexeme = malloc((len + 1) * sizeof(char));
        if (lp == BUF_1) {
            strncpy(lexeme, buf1 + l, len);
        } else {
            strncpy(lexeme, buf2 + l, len);
        }
        lexeme[len] = '\0';
        l = r;
        tkv = lexeme;
    } else if (lp != rp) {
        int len = BUF_SIZE - r + l;
        char *lexeme = malloc((len + 1) * sizeof(char));
        l = r;
        /* TODO:: cpy */
        tkv = lexeme;
    } else {
        exit(3);
    }
}

void scan() {
    /* scan analys string in buf return next lexeme */ 
    while(1) {
        char c = gc();

        /* assert mode */ 
        if (c == ' ' || c == '\t') {
            /* printf("match empty.\n"); */
            /* ignore empty space */
            l = r;
            continue;
        } else if (isdigit(c)) {
            /* printf("match num.\n"); */
            tk = NUM;
            while (1) {
                c = gc();
                if (!isdigit(c)) {
                    ugc();
                    break;
                }
            }
        } else if (c == '+' || c == '-' || c == '*' || c == '/') {
            tk = OPER;
            /* printf("match operator %c.\n", c); */
        } else if (isalpha(c)) {
            tk = ID;
            /* printf("match id.\n"); */
            /* 
              pattern: letter (letter | digit)* 
             */
            while (1) {
                c = gc();
                if (!isalpha(c) && !isdigit(c)) {
                    ugc();
                    break;
                }
            }
        } else if (c == '\0') {
            /* printf("match end.\n"); */
            tk = EOF;
        } else {
            exit(UNKNOWN_PATTERN);
        }

        break;
    }

    take();
}

#ifndef __ut
char *source = "hello world   i18n if else 7*2+3"; int now = 0;

int main(int argc,char *argv[]) {
    init(argv[1]);

    do {
        scan();
        if (tk != EOF) {
            printf("%s(%s)\n", tkv, _tks());
        }
    } while (tk != EOF);
}
#endif

