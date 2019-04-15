%{
  #include<stdio.h>
 int yylex();
 void yyerror();
%}
%token DIGIT 
%left '+' '-'
%left '*' '/'
%%
start:  expr '\n' { printf("expression value:%d\n",$1);};
expr: expr '+' expr { $$ = $1 + $3; }
|   expr '-' expr { $$ = $1 - $3; }

| expr '*' expr { $$ = $1 * $3; }
| expr '/' expr { $$= $1 / $3; }
|  '(' expr ')' { $$ = $2; }
| DIGIT { $$ = $1;}
;
%%

void yyerror(char const *s)
{
printf("yyerror:%s\n",s);

}
int main(void)
{
yyparse();
return 0;
}
