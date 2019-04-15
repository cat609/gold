%{
#include "y.tab.h"
#include<stdio.h>

%}


%%

[0-9]+ { yylval = atoi(yytext);
	return DIGIT;
	}
[\n] {return *yytext;}
[()] {return *yytext;}
"+" {return *yytext;}
"-" {return *yytext;}
"*" {return *yytext;}
"/" {return *yytext;}

%%

int yywrap()
{
return 1;
}
