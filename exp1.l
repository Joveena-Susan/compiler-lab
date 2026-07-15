%{
#include <stdio.h>
%}

%%
"if"|"else"|"while"|"for"|"int"|"float"|"char"|"return" { printf("Keyword : %s\n", yytext); }

[0-9]+                                                 { printf("Number : %s\n", yytext); }

[a-zA-Z_][a-zA-Z0-9_]*                                 { printf("Identifier : %s\n", yytext); }

"=="|"!="|"<="|">="|"+"|"-"|"*"|"/"|"="|"<"|">"|"%"     { printf("Operator : %s\n", yytext); }

"("|")"|"{"|"}"|"["|"]"|";"|","                         { printf("Delimiter : %s\n", yytext); }

[ \t\n]+                                               ;

.                                                      { printf("Unknown : %s\n", yytext); }
%%

int yywrap()
{
    return 1;
}

int main()
{
    yylex();
    return 0;
}
