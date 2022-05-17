/* 
    辅助声明部分写在%{%}内，使用 c 语言编写。
    通常用于定义 function、include 头文件、定义全局变量或常量等
 */
%{
#include "y.tab.h"

char* opplus = "plus";
%}

/* 正则声明部分 */
numb         [1-9][0-9]*
op_plus      \+
op_minus     \-
op_multi     \*
op_divide    \/

/* 
    规则部分，写在 %% xx %% 内。
    lex 会通过这些规则生成对应的 c 代码，并通过 yylex() 函数对外暴露

    左部是匹配规则，右部是动作
 */
%%
\+[0-9]{1,2}-137[0-9]{8}       { printf("phone num: %s", yytext); }
{numb}                         { yylval.ival=atoi(yytext); return NUM; }
{op_plus}                      { return PLUS; }
{op_minus}                     { return MINUS; }
{op_multi}                     { return MULTI; }
{op_divide}                    { return DIVIDE; }
(\ )                           { }
[;\(\)]                        { return yytext[0]; }
"exit"                         { return EXIT; }
.                              { }
%%


/* 辅助函数部分 */
/* int main() {
    yylex();
    return 0;
} */


