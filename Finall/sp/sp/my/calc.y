%{
    #include<ctype.h>
    #include<stdio.h>
#include <math.h>

    #define YYSTYPE double
%}

%token NUM

%left '+' '-'
%left '*' '/'

%%

S         : S E '\n' { printf("Answer: %g \nEnter:\n", $2); }
           | S '\n'
           |
           | error '\n' { yyerror("Error: Enter once more...\n" );yyerrok; }
           ;
           
E         : E '+' T    { $$ = $1 + $3; }
           | E'-'T    { $$=$1-$3; }
           | T
           ;
           
T         : T'*'F    { $$=$1*$3; }
           
           | T'/'F    { $$=$1/$3; }
           | F
           ;
           
F         :  '('E')'    { $$=$2; }
           | NUM
           ;

%%

#include "lex.yy.c"

int main()
{
    printf("Enter the expression: ");
    yyparse();
}

