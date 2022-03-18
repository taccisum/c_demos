#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <math.h>
#include <limits.h>

void help(char *cmd, int opt) {
    if(opt != -1) {
        fprintf(stderr, "Usage: %s [-dot] <binary>. Unknown option %c(ascii %d)\n", cmd, opt, opt);
    } else {
        fprintf(stderr, "Usage: %s [-dot] <binary>.\n", cmd);
    }
}

/* integer to binary */
int itob(unsigned int dec, char *bs, int len) {
    char tmp[33];
    tmp[32] = '\0';     // set end of string
    for (int i=0; i<32; i++) {
        int idx = 31 - i;
        unsigned int bit_val = 1 << idx;     // equals pow(2, idx)
        if(dec >= bit_val) {
            dec -= bit_val;
            tmp[i] = '1';
        } else {
            tmp[i] = '0';
        }
    }
    strcpy(bs, &tmp[32 - len]);     // substring [32-len, 32]
    return 0;
}

/* binary to decimalism */
int bin_to_dec(char *bin) {
    if(bin == NULL || bin[0] == '\0') {
        return 0;
    }
    int len = strlen(bin);
    int dec = 0;
    for (int i=0; i<len; i++) {
        int idx = len - i - 1;      // index(right to left)
        if(bin[i] == '1') {
            dec += pow(2, idx);
        }
    }
    return dec;
}

int main(int argc,char *argv[]) {
    int is_td = 0;
    int is_oc = 0;
    int is_tc = 0;
    int opt;

    extern int optind;
    while((opt = getopt(argc, argv, "dot")) != -1) {
        switch (opt) {
        case 'd':
            is_td = 1;
            break;
        case 'o':
            is_oc = 1;
            break;
        case 't':
            is_tc = 1;
            break;
        default: 
            help(argv[0], opt);
            exit(EXIT_FAILURE);
        }
    }

    char *binary_str = argv[optind];
    int len = strlen(binary_str);

    if(binary_str == NULL) {
        help(argv[0], -1);
        exit(EXIT_FAILURE);
    }

    printf("your binary num is: %s\n", binary_str);

    if (is_td) {
        // to decimalism
        int dec = bin_to_dec(binary_str);
        printf("to decimalism: %d\n", dec);
    }

    if (is_oc) {
        // take one's complement
        int dec = bin_to_dec(binary_str);
        int oc = dec ^ INT_MAX;      // all bits xor 1, to one's complement

        char *s = malloc((len + 1) * sizeof(char));
        itob(oc, s, len);
        printf("to one's complement: %s(dec: %d)\n", s, bin_to_dec(s));
    }

    if (is_tc) {
        // take two's complement
        int dec = bin_to_dec(binary_str);
        int oc = dec ^ INT_MAX;      // all bits xor 1, to one's complement
        int tc = oc + 1;        // plus 1 , to two's complement */

        char *s = malloc((len + 1) * sizeof(char));
        itob(tc, s, len);

        printf("to two's complement: %s(dec: %d)\n", s, bin_to_dec(s));
    }
}

