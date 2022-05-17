%{
  #include <stdio.h>
  #include <stdlib.h>

  int yylex(void);
  void yyerror(char *err);
  
  typedef struct Node node_t;
  void newline(struct Node *root);
  node_t* mknode(char op, node_t* left, node_t* right);
  node_t* mkleaf(int num);
%}

%union {
    int ival;
    node_t* node;
}

%token <ival> NUM
%token PLUS
%token MINUS
%token MULTI
%token DIVIDE
%token EXIT

// define type for non-terminal symbols
%type <node> expr
%type <node> term
%type <node> factor

%%
calculator: calculator line
    | line
    ;
line: expr ';'            { newline($1); }
    | EXIT                { printf("byebye."); exit(0); }
    ;
expr: expr PLUS   term    { $$ = mknode('+', $1, $3); }
    | expr MINUS  term    { $$ = mknode('-', $1, $3); }
    | term
    ;
term: term MULTI  factor  { $$ = mknode('*', $1, $3); }
    | term DIVIDE factor  { $$ = mknode('/', $1, $3); }
    | factor
    ;
factor: '(' expr ')'      { $$ = $2; }
    | NUM                 { $$ = mkleaf($1); }
    ;
%%

void yyerror(char *err)
{
    fprintf(stderr, "%s\n", err);
    exit(1);
}
