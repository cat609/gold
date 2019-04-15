#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<stdbool.h>
int flag =0,strflag=0,line=0;
int sindex=0,lindex=0;
struct symtab
{
	int index;
	char symbol[20];	
};

struct littab
{
	int index;
	char literal[20];	
};



struct termtab
{
	int index;
	char terminal[10];
	int delim;
};


bool isDelimiter(char ch)
{
    if (ch == ' ' || ch == '+' || ch == '-' || ch == '*' || 
        ch == '/' || ch == ',' || ch == ';' || ch == '>' || 
        ch == '<' || ch == '=' || ch == '(' || ch == ')' || 
        ch == '[' || ch == ']' || ch == '{' || ch == '}')
        return (true);
    return (false);
}

int isarithoperator(char ch)
{
    if (ch == '+') return 1;
    if (ch == '-') return 2;
    if (ch == '*') return 3;
    if (ch == '/') return 4;
    
    return (0);
}

int iscomparithoperator(char ch, char ch1)
{
    if (ch == '+' && ch1 == '+') return 45;
    if (ch == '-' && ch1 == '-') return 46;
    return (0);
}

int iscompoundop(char ch, char ch1)
{
    if (ch == '+' && ch1 == '=') return 45;
    if (ch == '-' && ch1 == '=') return 46;
    return (0);
}

int isreloperator(char ch)
{
    if (ch == '>') return 8;
    if (ch == '<') return 9;
       
    return (0);
}

int isassignoperator(char ch)
{
    if (ch == '=')
        return 10;
    return (0);
}

int iscomprelop(char ch,char ch1)
{
    if (ch == '=' && ch1 == '=') return 42;
    if (ch == '<' && ch1 == '=') return 43;
    if (ch == '>' && ch1 == '=') return 44;
    
    return (0);
}

char* substring(char* str, int left, int right)
{
    int i;
    char* subStr = (char*)malloc(
                  sizeof(char) * (right - left + 2));
 
    for (i = left; i <= right; i++)
        subStr[i - left] = str[i];
    subStr[right - left + 1] = '\0';
    return (subStr);
}

int search(char temp[])
{
	struct termtab term;
	FILE *fp;
	char buf[80];
	fp=fopen("terminal.txt","r+");
	while(fgets(buf,80,fp))
	{
		sscanf(buf,"%d %s %d",&term.index,term.terminal,&term.delim);
		//printf("%d %s %d %s\n",term.index,term.terminal,term.delim,term.token);
		if(strcmp(term.terminal,temp)==0)
		{
			//printf("found\n");
			 return term.index;
		
		}
		
	}
	fclose(fp);
	//printf("not found\n");
	return 0;
}

bool isLiteral(char str[])
{
    int i, len = strlen(str);
 
    if (len == 0)
        return (false);
    for (i = 0; i < len; i++) {
        if (str[i] != '0' && str[i] != '1' && str[i] != '2'
            && str[i] != '3' && str[i] != '4' && str[i] != '5'
            && str[i] != '6' && str[i] != '7' && str[i] != '8'
            && str[i] != '9' )
            return (false);
    }
    return (true);
}

bool isIden(char str[])
{
	int i,len,flag=0;
	if( isalpha(str[0]) )
	{
		flag=1;
		len=strlen(str);
		for(i = 1 ; i < len ; i++ )
		{		
			if( str[i]=='_' || isalpha(str[i]) || isdigit(str[i]) )
			continue;
			else
			{
				flag=0;
				break;
			}
		}
	}

	if( flag == 1 )
		return true;
	else
		return false;
}

int insert_littab(char temp[])
{
	struct littab lit;
	int flag=0;
	FILE *fp;
	fp=fopen("littab.txt","r+");
	fread(&lit,sizeof(lit),1,fp);
	do
	{
		if(strcmp(lit.literal,temp)==0) 
		{
			flag=lit.index;
			break;
		}
	}while(fread(&lit,sizeof(lit),1,fp));
	
	if(flag!=0)
	{
		fclose(fp);
		return flag;
	}
	else
	{
		fseek(fp,0,SEEK_END);
		lindex++;
		lit.index=lindex;
		strcpy(lit.literal,temp);
		fwrite(&lit,sizeof(lit),1,fp);
			fclose(fp);
		return lindex;
	}

}		

int insert_symtab(char temp[])
{
	struct symtab sym;
	int flag=0;
	FILE *fp;
	fp=fopen("symtab.txt","r+");
	fread(&sym,sizeof(sym),1,fp);
	do
	{
		if(strcmp(sym.symbol,temp)==0) 
		{
			flag=sym.index;
			break;
		}
	}while(fread(&sym,sizeof(sym),1,fp));
	
	if(flag!=0)
	{
		fclose(fp);
	
		return flag;
	}
	else
	{
		fseek(fp,0,SEEK_END);
		sindex++;
		sym.index=sindex;
		strcpy(sym.symbol,temp);
		fwrite(&sym,sizeof(sym),1,fp);
		fclose(fp);
	
		return sindex;
	}

	

}


void handle_buf(char str[])
{
	int left=0,right=0,len;
	len=strlen(str);
	FILE *fp1;
	fp1=fopen("ust.txt","a+");

	while (right <= len && left <= right) 
	{
		if(str[right]=='/' && str[right+1]=='/')
		{
			break;
		}
	 
		if(str[right]=='/' && str[right+1]=='*')
		{
			flag=1;
			right+=2;
			left+=2;
		}
	
		if(str[right]=='*' && str[right+1]=='/')
		{
			flag=0;
			right+=2;
			left+=2;
		}
	
		if(str[right]=='"')
		{
			if(strflag==0)
			strflag=1;
			else if(strflag==1)
			strflag=0;
		}
	
		if(flag==1 && isDelimiter(str[right]))
		{right++;left++;}
	
		if(!isDelimiter(str[right])||strflag==1) //moves right pointer until delimiter
		right++;

		if(isDelimiter(str[right]) && left==right && flag==0) //handles delimiters and operators
		{
			if(isassignoperator(str[right]))
			{
				if(isassignoperator(str[right+1]))
				{
					int x = iscomprelop(str[right],str[right+1]);
					fprintf(fp1,"%c%c	TRM	  %d\n",str[right],str[right+1],x);
					right++;
				}
				else
				{
					int x = isassignoperator(str[right]);
					fprintf(fp1,"%c		TRM	%d\n",str[right],x);
				}
			}
		else if(isreloperator(str[right]))
		{
			if(isassignoperator(str[right+1]))
			{
				int x = iscomprelop(str[right],str[right+1]);
				fprintf(fp1,"%c%c	TRM	%d\n",str[right],str[right+1],x);
				right++;
			}
			else
			{
				int x = isreloperator(str[right]);
				fprintf(fp1,"%c		TRM	%d\n",str[right],x);
			}
		}
		else if(isarithoperator(str[right]))
		{
			if((str[right]=='+'&&str[right+1]=='+')||(str[right]=='-'&&str[right+1]=='-'))
			{
				int x = iscomparithoperator(str[right],str[right+1]);
				fprintf(fp1,"%c%c	TRM	%d\n",str[right],str[right+1],x);
				right++;
			}
			else if(isassignoperator(str[right+1]))
			{
				int x = iscompoundop(str[right],str[right+1]);
				fprintf(fp1,"%c%c	TRM	%d\n",str[right],str[right+1],x);
				right++;
			}
			else
			{
				int x = isarithoperator(str[right]);
				fprintf(fp1,"%c		TRM	%d\n",str[right],x);
			}
		}
		else if(str[right]!=' '&&str[right]!='\n'&&str[right]!='\t')
			{
				 if(isDelimiter(str[right]))
				{
					char *new=(char*)malloc(sizeof(2));
					new[0]=str[right]; new[1]='\0';
					int x=search(new);
					fprintf(fp1,"%c		TRM	%d\n",str[right],x);
				}
			}
			right++;
			left=right;
		}	
	
		if(isDelimiter(str[right]) && left!=right && flag==0) //handles keywords and identifiers
		{
			char* temp = substring(str,left,right-1);
		
			if(search(temp))
			{
				int x = search(temp);
				fprintf(fp1,"%s		TRM	%d\n",temp,x);
			}	
			else if(temp[0]=='"'&& temp[strlen(temp)-1]=='"')
			{
				int x = insert_littab(temp);
				fprintf(fp1,"%s		LIT	%d\n",temp,x);
			}
			else if(isIden(temp))
			{
				int x = insert_symtab(temp);
				fprintf(fp1,"%s		IDN	%d\n",temp,x);
			}
			else if(isLiteral(temp))
			{
				int x = insert_littab(temp);
				fprintf(fp1,"%s		LIT	%d\n",temp,x);
			}
			
			left=right;
		}	
	
		
	}

	fclose(fp1);
}

void operate(char inpfile[])
{
	FILE *fp;
	char buf[80];
	fp=fopen(inpfile,"r+");

	
	while(fgets(buf,80,fp))
	{
		line++;
		handle_buf(buf);
	}

	fclose(fp);

}

void disptabs()
{

	FILE *fp;
	struct symtab sym;
	struct littab lit;
	char buf[80];

	fp=fopen("symtab.txt","r+");
	printf("Symbol table\n");
	fread(&sym,sizeof(sym),1,fp);
	do
	{
		printf("%d  %s\n",sym.index,sym.symbol);
	}while(fread(&sym,sizeof(sym),1,fp));
	fclose(fp);

	
	fp=fopen("littab.txt","r+");
	printf("Literal table\n");
	fread(&lit,sizeof(lit),1,fp);
	do
	{
		printf("%d  %s\n",lit.index,lit.literal);
	}while(fread(&lit,sizeof(lit),1,fp));
	fclose(fp);

	fp=fopen("ust.txt","r+");
	printf("Uniform Symbol Table\n");
	while(fgets(buf,80,fp))
		printf("%s",buf);
	fclose(fp);
}

void init()
{

	FILE *fp;
	fp=fopen("symtab.txt","w");
	fclose(fp);
	fp=fopen("littab.txt","w");
	fclose(fp);
	fp=fopen("ust.txt","w");
	fclose(fp);
}
int main()
{
	char inpfile[15];
	printf("enter the name of input file\n");
	scanf("%s",inpfile);
	init();
	operate(inpfile);
	disptabs();
	return 0;
}
