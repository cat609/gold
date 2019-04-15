#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include<ctype.h>
int termp = 0, i, litp = 0, idnp, line = 1,unip=0;
char word[20], lexeme[30];
struct term {
	char symbol[20];
	int indication; //1 for yes 0 for no
} term[57] = { { "auto", 0 }, { "double", 0 }, { "int", 0 }, { "struct", 0 }, {
		"break", 0 }, { "else", 0 }, { "long", 0 }, { "switch", 0 },
		{ "case", 0 }, { "enum", 0 }, { "register", 0 }, { "typedef", 0 }, {
				"char", 0 }, { "extern", 0 }, { "return", 0 }, { "union", 0 }, {
				"const", 0 }, { "float", 0 }, { "short", 0 }, { "unsigned", 0 },
		{ "continue", 0 }, { "for", 0 }, { "signed", 0 }, { "void", 0 }, {
				"default", 0 }, { "goto", 0 }, { "sizeof", 0 },
		{ "volatile", 0 }, { "do", 0 }, { "if", 0 }, { "static", 0 }, { "while",
				0 }, { "!", 1 }, { "*", 1 }, { "+", 1 }, { "<", 1 }, { "#", 1 },
		{ "(", 1 }, { "=", 1 }, { "|", 1 }, { ">", 1 }, { "%", 1 }, { ")", 1 },
		{ "~", 1 }, { ";", 1 }, { "/", 1 }, { "^", 1 }, { "-", 1 }, { "[", 1 },
		{ ":", 1 }, { ",", 1 }, { "?", 1 }, { "&", 1 }, { "-", 1 }, { "]", 1 },
		{ "{", 1 }, { "}", 1 } };
//structure for the each table 
//1
struct identifier 
{
	char name[20];
} identifier[20];
//2
struct literal 
{
	char num[10];
} literal[20];
//3
struct terminal 
{
	char term_name[30];
} terminal[30];
//4
struct universal
{
	int index;
	char class[10];
	char token[30];
}universal[100];

int lit_search(char lex[30]);
//2
void check_type(char word[20]);
//3
int check_teminal(char ch);
//4
void generate_lexeme(char word[30]);
//5
int term_search(char lex[30]);
//6
int check_valid_idn(char lex[30]);
//7
int valid_digit(char lex[30]);
//8
int idn_search(char lex[30]);

int k = 0;
int main(void) {

	FILE *fp;
	char buff[200], c;
	int i = 0, j = 0, flag = 0, l = 0, flag1 = 0;
	buff[0] = '\0';
	fp = fopen("prog.txt", "r");
	if (fp == NULL) 
	{
		printf("Cannot open file \n");
		exit(0);
	} else {
printf("\n=============LEXEMS:============\n");
		do {
			printf("\n");
			fgets(buff, 200, fp);

			i = 0;
			j = 0;
			flag = 0;

			if (buff[0] == '\n') 
			{
				line++;
			} else {
                              

				generate_lexeme(buff);

				memset(word, 0, sizeof(word));
			}

			memset(buff, 0, sizeof(buff));
		} while (!feof(fp));
		fclose(fp);
	}
	printf("\n==========terminal table==========");
	for (i = 0; i < termp; i++) 
	{
		printf("\n%d\t%s", i, terminal[i].term_name);
	}
	printf("\n===========Literal table==========");
	for (i = 0; i < litp; i++) 
	{
		printf("\n%d\t%s", i, literal[i].num);
	}

	printf("\n==========Identifier table=========");
	for (i = 0; i < idnp; i++) 
	{
		printf("\n%d\t%s", i, identifier[i].name);
	}
        	printf("\n===========Universal table==========");
	for (i = 0; i < unip; i++) 
	{
		printf("\n\t\t%s\t%d\t%s", universal[i].class, universal[i].index,universal[i].token);
	}
       

	return EXIT_SUCCESS;

}
//2
void check_type(char lex[30]) 
{
	int i, a;
	int flag1 = 1;
	int l = 0;
//Identify Terminal
	for (i = 0; i < 57; i++) 
	{

		if (strcmp(lex, term[i].symbol) == 0) 
		{
			a = term_search(lex);
			if (a==0) 
			{
				strcpy(terminal[termp].term_name, lex);
				
                                universal[unip].index=termp;
                                strcpy(universal[unip].class,"TRM");
                                strcpy(universal[unip].token,lex);
                               termp++;
                               unip++;
			}
			flag1 = 0;
		}

	}

	if (flag1 == 1) 
	{
		a = valid_digit(lex);//Check For Digit
		if (a) 
		{

			a = lit_search(lex);
			if (a ==0) 
			{
				strcpy(literal[litp].num, lex);//If So Enter it into Literal Table
				
				universal[unip].index=litp;
                                strcpy(universal[unip].class,"LIT");
                                strcpy(universal[unip].token,lex);
                                litp++;
                                unip++;

			}
			flag1 = 0;
		}
	}
	if (flag1 == 1) 
	{
		if (check_valid_idn(lex)) 
		{//Check For Identifier
			if (idn_search(lex) == 0)
			{
				strcpy(identifier[idnp].name, lex);//If So Enter it into 								Identifier Table
				universal[unip].index=idnp;
                                strcpy(universal[unip].class,"IDN");
                                strcpy(universal[unip].token,lex);
                                idnp++;
                                unip++;
			}
		} else {
			printf("\tInValid IDN[");
			printf("Line:%d]\n", line);
                        exit(0);
		}

	}
}
//4
void generate_lexeme(char buff[30]) 
{
	char lex[10];
	int j = 0, flag = 0, flag1 = 0;
	k = 0;

	for (j = 0; buff[j] != '\0'; j++) 
	{
		if (buff[j] == '\n') 
		{
			line++;
		} else if (isalnum(buff[j])) {
			lexeme[k++] = buff[j];
			flag = 1;
		} else if (buff[j] == ' ') {
			lexeme[k] = '\0';
			k = 0;
			check_type(lexeme);
			printf("\t%s", lexeme);
		} else {

			if (flag == 1) 
			{
				lexeme[k] = '\0';
				k = 0;
				printf("\t%s", lexeme);
				check_type(lexeme);
			}
			lexeme[0] = buff[j];
			lexeme[1] = '\0';
			printf("\t%s", lexeme);
			check_type(lexeme);
			flag = 0;

		}
	}

}
//4
int term_search(char lex[30]) 
{
	int l = 0;
	for (l = 0; l < termp; l++) 
	{

		if (strcmp(lex, terminal[l].term_name) == 0) 
		{
			return 1;
		}

	}
	return 0;
}
//5
int lit_search(char lex[30]) 
{
	int i;
	for (i = 0; i < litp; i++) 
	{
		if (strcmp(lex, literal[i].num) == 0)
		{
			return 1;
		}
	}

	return 0;
}
//6
int check_valid_idn(char lex[30]) 
{
	int i;
	if (!isalpha(lex[0])) 
	{
		return 0;
	}
	i = 1;
	while (lex[i] != '\0') 
	{
		if (lex[i] == '_') 
		{
		} else if (!isalpha(lex[i]))
			return 0;
		i++;
	}
	return 1;
}
//7
int valid_digit(char lex[30]) 
{

	
	while (lex[i] != '\0') 
	{
		if (isdigit(lex[i])) 
		{
			i++;
		} else
			return 0;
	}
	if (i == strlen(lex) - 1)
		return 1;

}
//8
int idn_search(char lex[30]) 
{
	int i;
	for (i = 0; i < idnp; i++) 
	{
		if (strcmp(lex, identifier[i].name) == 0)
			return 1;
	}
	return 0;

}

