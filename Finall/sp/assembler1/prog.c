#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>

struct S
{
	char s1[10];
	char s2[10];
	char s3[10];
	char s4[10];
	
};

struct Imm_code
{
	int lc;
	char opcode[3];
	int op1;
	int op2;
};

struct LITTAB
{
	int no;
	char literal[10];
	int addr;
};

struct SYMTAB
{
	int index;
	char symbol[10];
	int address;
};

int check_d(const char* string) {
  const int string_len = strlen(string);
  for(int i = 0; i < string_len; ++i) {
    if(!isdigit(string[i])) 
      return 0;
  }
  return 1;
}

int check_s(const char* string) {
  const int string_len = strlen(string);
  for(int i = 0; i < string_len; ++i) {
    if(!isalpha(string[i])) 
      return 0;
  }
  return 1;
}

char check(char val[])
{
	if(check_d(val)==1 )
		return 'c';
	else if(val[0]== '='&& val[1]== '\'' && isdigit(val[2]) && val[3]== '\'')
		return 'l';
	else if (check_s(val)==1)
		return 's';
}

int find_lit(char *key )
{
	struct LITTAB lit;
	int z=atoi(key); 
	FILE *fp2;
	fp2=fopen("littab.txt","r+");
	fread(&lit,sizeof(lit),1,fp2);
	do
	{
		if(lit.no==z)
			{z=lit.addr; break;}
	}while(fread(&lit,sizeof(lit),1,fp2));
	fclose(fp2);
		return z;
}

int find_sym(char *key )
{
	struct SYMTAB sym;
	int z=atoi(key); 
	FILE *fp2;
	fp2=fopen("symtab.txt","r+");
	fread(&sym,sizeof(sym),1,fp2);
	do
	{
		if(sym.index==z)
			{z=sym.address; break;}
	}while(fread(&sym,sizeof(sym),1,fp2));
	fclose(fp2);
		return z;
}
 
void operate(char inpfile[])
{
	FILE *fp,*fp1,*fp2;
	struct S s;
	struct Imm_code imm;
	struct LITTAB lit;
	struct SYMTAB sym;
	int z;
	char buf[80];
	char a;
	char *token;
	char *search =",";
	
	fp=fopen(inpfile,"r+");
	fp1=fopen("output2.txt","a+");


	while(fgets(buf,80,fp))
	{
		sscanf(buf,"%s %s %s %s \n",s.s1,s.s2,s.s3,s.s4);
		//printf("%s %s %s %s \n",s.s1,s.s2,s.s3,s.s4);
		a=check(s.s1);
		if(a=='c')
		{

			imm.lc=atoi(s.s1); 
			if(s.s2)
			{
				token = strtok(s.s2, search);
				if(strcmp(token,"IS")==0)
				{
					
					token = strtok(NULL, search);
					strcpy(imm.opcode,"+");
					strcat(imm.opcode,token);  
					if(strcmp(s.s3,"")!=0)
					{
						
						token=strtok(s.s3,search);
						if(strcmp(token,"R")==0||strcmp(token,"CC")==0)
						{
							token = strtok(NULL, search);
							imm.op1=atoi(token);
						}
						else if(strcmp(token,"s")==0)
						{
							token = strtok(NULL, search);
							imm.op1=find_sym(token);
						}
					}
					else
						imm.op1=0;
					if(strcmp(s.s4,"")!=0)
					{
						token=strtok(s.s4,search);
						if(strcmp(token,"l")==0)
						{
							token = strtok(NULL, search);
							imm.op2=find_lit(token);
							
						}
						else if(strcmp(token,"s")==0)
						{
							token = strtok(NULL, search);
							imm.op2=find_sym(token);
						}
					}
					else imm.op2=0;
					printf("%d %s %d %d\n",imm.lc,imm.opcode,imm.op1,imm.op2);
					fprintf(fp1,"%d %s %d %d\n",imm.lc,imm.opcode,imm.op1,imm.op2);
				
				}
				else if(strcmp(token,"DL")==0)
				{
					//printf("DL\n");
					token = strtok(NULL, search);
					z=atoi(token);
					if(z==1)
					{
						//printf("DC\n");
						strcpy(imm.opcode,"+00");
						imm.op1=0;
						token=strtok(s.s3,search);
						if(strcmp(token,"C")==0)
						{
							token = strtok(NULL, search);
							imm.op2=atoi(token);
						}
						
					}
					else if(z==2)
					{
						//printf("DS\n");
						strcpy(imm.opcode,"+00");
						imm.op1=0;
						imm.op2=0;
					}
					printf("%d %s %d %d\n",imm.lc,imm.opcode,imm.op1,imm.op2);
					fprintf(fp1,"%d %s %d %d\n",imm.lc,imm.opcode,imm.op1,imm.op2);
					
				}
				else
				{
					printf("Reading wrong type\n");
				}
					
			}
			
		}
		else
		{
			printf("\n");
			fprintf(fp1," \n");
		}
		
		strcpy(s.s1,"");
		strcpy(s.s2,"");
		strcpy(s.s3,"");
		strcpy(s.s4,"");
			
		}
	
		
	fclose(fp);
	fclose(fp1);
	
}

void init()
{
	FILE *fptr;
	fptr=fopen("output2.txt","w");
	fclose(fptr);
}

int main()
{

	char inpfile[20];
	init();
	printf("Enter the name of input file :\n");
	scanf("%s",inpfile);
	//printf("Processing File ....%s\n",inpfile);
	operate(inpfile);
	
	printf("Output of Pass I is stored in file output2.txt \n");
	return 0;
}


