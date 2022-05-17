num   [1-9][0-9]*
word  [a-zA-Z]+

%%
{num}       { printf("number: %d\n", atoi(yytext)); }
{word}      { printf("word: %s\n", yytext); }
.           {}
%%

int main(int argc, char* argv[]) {
    yylex();
    return 0;
}
