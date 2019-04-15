%{
    #include<ctype.h>
    #include<stdio.h>
#include <math.h>

    #define YYSTYPE double
%}

%token NUM
%token COS SIN TAN LOG 

%left '+' '-'
%left '*' '/'
%right UMINUS

%%

S         : S E '\n' { printf("Answer: %g \nEnter:\n", $2); }
           | S '\n'
           |
           | error '\n' { yyerror("Error: Enter once more...\n" );yyerrok; }
           ;
E         : E '+' E    { $$ = $1 + $3; }
           | E'-'E    { $$=$1-$3; }
           | E'*'E    { $$=$1*$3; }
           
            |E'/'E    { $$=$1/$3; }
           | '('E')'    { $$=$2; }
           | '-'E %prec UMINUS { $$= -$2; }
           | NUM
           | COS'('E')' {$$=cos($3);}
           | SIN'('E')' {$$=sin($3);}
           | TAN'('E')' {$$=tan($3);}
           | LOG'('E')' {$$=log($3);}
            
           ;

%%

#include "lex.yy.c"

int main()
{
    printf("Enter the expression: ");
    yyparse();
}

