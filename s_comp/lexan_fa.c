#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>

#define ERR_BUF_NO 1
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

/*
   defines state-flow table:
            digit  char  operator  other
   ε         num    id     oper     -
   id        id     id      -       -
   num       num    -       -       -
   oper       -     -       -       -
 */
int sf_tbl[4][4] = {
    { NUM, ID, OPER, -1 },
    { ID,  ID, -2,   -2 },
    { NUM, -2, -2,   -2 },
    { -2,  -2, -2,   -2 },
};

/* move to next state */
int move(int s, char c) {
    int type = 0;
    if (isdigit(c)) {
        type = 0;
    } else if (isalpha(c)) {
        type = 1;
    } else if (c == '+' || c == '-' || c == '*' || c == '/') {
        type = 2;
    } else {
        type = 3;
    }

    /* return new state */
    return sf_tbl[s][type];
}


void scan() {
    /* scan analys string in buf return next lexeme */ 
    tk = EOF;
    char c; int new_s;
    do {
        c = gc();
        if(c == '\0') {
            break;
        }

        new_s = move(tk == EOF ? 0 : tk, c);
        if (new_s == -1) {
            /* printf("detect emtpy space '%c', ignore\n", c); */
            l = r;
            continue;
        } else if (new_s >= 0) {
            tk = new_s;
        }
    } while (new_s != -2);
    ugc();

    take();
}

#ifndef __ut
char *source = "hello world   i18n if else 7*2+3-4/1"; int now = 0;

int main(int argc,char *argv[]) {
    /* init(source); */
    init(argv[1]);

    do {
        scan();
        if (tk != EOF) {
            printf("%s(%s)\n", tkv, _tks());
        }
    } while (tk != EOF);
}
#endif

