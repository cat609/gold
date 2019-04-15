#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>

int LC,line=1,sindex=0 ,pooltabptr=0,litabptr=0;
 struct OPTAB
{
	char name[10];
	int opcode;
	int size;
	char type[2];
	int nop;
};
struct OPTAB op; 
struct S
{
	char s1[10];
	char s2[10];
	char s3[10];
	char s4[10];
	
};

struct SYMTAB
{
	int index;
	char symbol[10];
	int address;
};

struct op2
{
	char type2;
	int value;
};

struct Imm_code
{
	int lc;
	char type[2];
	int opcode;
	char type1[2];
	int op1 ;
	struct op2 op2;
};

struct LITTAB
{
	int no;
	char literal[10];
	int addr;
};

struct LITTAB litab[20];
struct POOLTAB
{
	int index;
};
struct POOLTAB pooltab[20];
struct operand
{
	char name[6];
	int code;
	char type[2];
};

void error(int line,int type)
{
	switch(type)
	{
		case 1 : printf("Line No %d :First Statement Must be Start \n",line);
			break;
		case 2 :printf("Line No %d :Unmatched Instruction\n",line);
			break;
		case 3 :printf("Line No %d :arguements to start must be const\n",line);
			break;
		case 4 :printf("Line No %d :Error while processing symbols\n",line);
			break;
		case 5 :printf("Line No %d :DS must contain constant argument\n",line);
			break;
		case 6 :printf("Line No %d :Invalid symbol specified by EQU\n",line);
			break;
		case 7 :printf("Line No %d :Invalid symbol specified by ORIGIN\n",line);
			break;
		case 8 :printf("Line No %d :Searching for undefined symbol\n",line);
			break;
		case 9 :printf("Line No %d :Referring symbol whose address not defined\n",line);
			break;
		default:printf("Invalid Error No !!!\n");
	}
}

int search(struct S s)
{
	FILE *fp;
	//struct OPTAB op;
	char buf[80];
	
	fp=fopen("optab.txt","r");
	
	while(fgets(buf,80,fp))
	{
	sscanf(buf,"%s %d %d %s %d\n",op.name,&op.opcode,&op.size,op.type,&op.nop);
	
	//printf("%s|%d|%d|%s|%d\n",op.name,op.opcode,op.size,op.type,op.nop);
		if(strcmp(s.s1,op.name)==0)
		{
			//printf("Record Found\n");
			//printf("%s|%d|%d|%s|%d\n",op.name,op.opcode,op.size,op.type,op.nop);
			//found=1;
			//return op; 
			
			return 1;
			
		}
		else if(strcmp(s.s2,op.name)==0)
		{
			//printf("Record Found\n");
			//printf("%s|%d|%d|%s|%d\n",op.name,op.opcode,op.size,op.type,op.nop);
			//found=2;
			//return op; 
			return 2;
			
		}
		
	}
	fclose(fp);
	
	//found=3;
	return 3;
}
void display(char inpfile[])
{
	FILE *fp;
	struct S s;
	char buf[80];
	
	fp=fopen(inpfile,"r");
	
	while(fgets(buf,80,fp))
	{
	sscanf(buf,"%s %s %s %s \n",s.s1,s.s2,s.s3,s.s4);
	
	printf("%s|%s|%s|%s\n",s.s1,s.s2,s.s3,s.s4);
	strcpy(s.s1,"");
	strcpy(s.s2,"");
	strcpy(s.s3,"");
	strcpy(s.s4,"");
			
	}
	fclose(fp);
}

int check_string(const char* string) {
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
 	//int i= atoi(val);
	if(check_string(val)==1 )
		return 'c';
	else if(val[0]== '='&& val[1]== '\'' && isdigit(val[2]) && val[3]== '\'')
		return 'l';
	else if (check_s(val)==1)
		return 's';
}
 
int process(char literal[])
{
	return literal[2];
}

void handle_label(char label[],int LC)
{
	FILE *fp1;
	struct SYMTAB sym;
	char buf[80];
	int flag=0;
	
	fp1=fopen("symtab.txt","r+");
	fread(&sym,sizeof(sym),1,fp1);
	do
	{
	//sscanf(buf," %d %s %d\n",&sym.index,sym.symbol,&sym.address);
	
	//printf("%s|%d|%d|%s|%d\n",op.name,op.opcode,op.size,op.type,op.nop);
		if(strcmp(sym.symbol,label)==0)
		{
			if(sym.address==-1)
				{
					sym.address=LC;
					fseek(fp1,-sizeof(sym),SEEK_CUR);
					fwrite(&sym,sizeof(sym),1,fp1);
					//printf("Second time\n");
					flag=1;
				}
			else //if(sym.address!=-1)
					error(line,4);
				
	
		}
		
	}while(fread(&sym,sizeof(sym),1,fp1));
	
	if(flag!=1)
	{
			fseek(fp1,0,SEEK_END);
			//fprintf(fp1,"%d %s %d \n",++sindex,label,LC);
			++sindex;
			sym.index=sindex;
			strcpy(sym.symbol,label);
			sym.address=LC;
			fwrite(&sym,sizeof(sym),1,fp1);
			//printf("first time\n");
			
	}
	fclose(fp1);
	
}

int find_addr(char key[])
{

	FILE *fp4;
	struct SYMTAB sym;
	int temp=0,flag=0;
			
	
	fp4=fopen("symtab.txt","r+");
	fread(&sym,sizeof(sym),1,fp4);
	do
	{
		if(strcmp(sym.symbol,key)==0)
		{
			temp=sym.address;
			flag=1;
			break;
		}
		
	}while(fread(&sym,sizeof(sym),1,fp4));
	if(flag!=1)
		error(line,8);
	if(temp== -1)
		error(line,9);
	fclose(fp4);
	return temp;

}
void handle_AD(struct S s)
{
	FILE *fp2;
	fp2=fopen("output.txt","a+");
	struct Imm_code imm;
	char flag;
	if(strcmp(s.s1,"START")==0)
	{
		if(strcmp(s.s2,"")==0)
		{
			LC=0;
			printf("start has no operands!! ....starting with LC = %d\n",LC);
		}
		else
		{
		 	flag=check(s.s2); 
			if(flag!='c')
			{error(line,3); LC=0;}
			
			else
			{LC= atoi(s.s2);
			printf("\nLC is...%d \n",LC);}
		}
		strcpy(imm.type,"AD");
		imm.opcode=01;
		strcpy(imm.type1,"C");
		imm.op1=LC;
		
		printf("...    (%s ,%d)- (%s,%d) \n",imm.type,imm.opcode,imm.type1,imm.op1);
		fprintf(fp2,"%s,%d	%s,%d \n",imm.type,imm.opcode,imm.type1,imm.op1);

	}
	else if(strcmp(s.s1,"LTORG")==0)
	{
		struct LITTAB lit;
		FILE *fp3;
		int j, i=1,k;
		fp3=fopen("littab.txt","r+");
		strcpy(imm.type,"DL");
		imm.opcode=01;

		fread(&lit,sizeof(lit),1,fp3);
		do
		{
			litab[i].no=lit.no;
			strcpy(litab[i].literal,lit.literal);
			litab[i].addr=lit.addr;
			i++;
		
		}while(fread(&lit,sizeof(lit),1,fp3));
	
		 j=pooltab[pooltabptr].index;
		//printf("%d",j);
		for(;j<=litabptr;j++)
		{
			imm.lc=LC;
			imm.op2.type2='C';
			imm.op2.value=process(litab[j].literal)-48;
			litab[j].addr=LC;
			LC++;
			printf("...%d--> (%s ,%d)- (-,-) - (%c,%d)\n",imm.lc,imm.type,imm.opcode,imm.op2.type2,imm.op2.value);

			fprintf(fp2,"%d	%s,%d	%c,%d\n",imm.lc,imm.type,imm.opcode,imm.op2.type2,imm.op2.value);

		}
		pooltab[++pooltabptr].index=litabptr+1;

		fclose(fp3);

		fp3=fopen("littab.txt","w+");
		for(k=1;k<=litabptr;k++)
		{
			lit.no=litab[k].no;
			strcpy(lit.literal,litab[k].literal);
			lit.addr=litab[k].addr;
			fwrite(&lit,sizeof(lit),1,fp3);
		}
		fclose(fp3);		

	}

	else if(strcmp(s.s1,"END")==0)
	{
		//printf("End of statement\n");

		strcpy(imm.type,"AD");
		imm.opcode=02;
		
		printf("...    (%s ,%d) \n",imm.type,imm.opcode);
		fprintf(fp2,"%s,%d\n",imm.type,imm.opcode);

		struct LITTAB lit;
		FILE *fp3;
		int j, i=1,k;
		fp3=fopen("littab.txt","r+");
		strcpy(imm.type,"DL");
		imm.opcode=01;

		fread(&lit,sizeof(lit),1,fp3);
		do
		{
			litab[i].no=lit.no;
			strcpy(litab[i].literal,lit.literal);
			litab[i].addr=lit.addr;
			i++;
		
		}while(fread(&lit,sizeof(lit),1,fp3));
	
		 j=pooltab[pooltabptr].index;
		//printf("%d",j);
		if(j>litabptr)
		{
			pooltabptr--;
		}
		else
		{
			for(;j<=litabptr;j++)
			{
				imm.lc=LC;
				imm.op2.type2='C';
				imm.op2.value=process(litab[j].literal)-48;
				litab[j].addr=LC;
				LC++;
				printf("...%d--> (%s ,%d)- (-,-) - (%c,%d)\n",imm.lc,imm.type,imm.opcode,imm.op2.type2,imm.op2.value);

				fprintf(fp2,"%d	%s,%d	%c,%d\n",imm.lc,imm.type,imm.opcode,imm.op2.type2,imm.op2.value);

			}		
			//pooltab[++pooltabptr].index=litabptr+1;
		}

		fclose(fp3);

		fp3=fopen("littab.txt","w+");
		for(k=1;k<=litabptr;k++)
		{
			lit.no=litab[k].no;
			strcpy(lit.literal,litab[k].literal);
			lit.addr=litab[k].addr;
			fwrite(&lit,sizeof(lit),1,fp3);
		}
		fclose(fp3);		

	}
	else if(strcmp(s.s2,"EQU")==0)
	{
		flag=check(s.s3); 
		if(flag=='s')
		{
			int temp;
			temp=find_addr(s.s3);
			handle_label(s.s1,temp);
			strcpy(imm.type,"AD");
			imm.opcode=04;
		
			printf("...    (%s ,%d) \n",imm.type,imm.opcode);
			fprintf(fp2,"%s,%d \n",imm.type,imm.opcode);

		}
		else 
			error(line,6);
			
	}
	else if(strcmp(s.s1,"ORIGIN")==0)
	{
		char *token;
		char *search ="+";
		int temp,f;

		token = strtok(s.s2, search);
		//printf("%s\n",token);
		

		flag=check(token); 
		if(flag=='s')
		{
			
			temp=find_addr(token);
		}
		else 
			error(line,7);

		token = strtok(NULL, search);	
		 f= atoi(token);
		LC=f+temp;
		printf("Updated LC = %d\n",LC);
		//printf("%s\n",token);	
		strcpy(imm.type,"AD");
		imm.opcode=03;
		
		printf("...    (%s ,%d) \n",imm.type,imm.opcode);
		fprintf(fp2,"%s,%d\n",imm.type,imm.opcode);
	}
	fclose(fp2);
}

int handle_literal(char op2[])
{
	struct LITTAB litab;
	FILE *fp3;
	fp3=fopen("littab.txt","a+");
	//fprintf(fp3,"%d %s %d \n",++litabptr,op2,-1);
	++litabptr;
	litab.no=litabptr;
	strcpy(litab.literal,op2);
	litab.addr=-1;
	fwrite(&litab,sizeof(litab),1,fp3);
	fclose(fp3);
	return litabptr;
}



int handle_symbol(char OP1[])
{
	
	FILE *fp1;
	struct SYMTAB sym;
	char buf[80];
	
	fp1=fopen("symtab.txt","a+");
	fread(&sym,sizeof(sym),1,fp1);
	do
	{
	//sscanf(buf," %d %s %d\n",&sym.index,sym.symbol,&sym.address);
	
	//printf("%s|%d|%d|%s|%d\n",op.name,op.opcode,op.size,op.type,op.nop);
		if(strcmp(sym.symbol,OP1)==0)
		{
			return sym.index;
	
		}
		
	}while(fread(&sym,sizeof(sym),1,fp1));
	
	++sindex;
	sym.index=sindex;
	strcpy(sym.symbol,OP1);
	sym.address=-1;
	fwrite(&sym,sizeof(sym),1,fp1);
	fclose(fp1);
	return sindex;
	
}

struct operand handle_op1(char OP1[])
{
	FILE *fp2;
	struct operand op3;

	char buf[80];
	int s=0;
	
	fp2=fopen("op1.txt","r");
	
	while(fgets(buf,80,fp2))
	{
	sscanf(buf,"%s %d %s\n",op3.name,&op3.code,op3.type);
	
		if(strcmp(OP1,op3.name)==0)
		{
			//printf("%s-%d-%s\n",op1.name,op1.code,op1.type);
			s= op3.code;
			break;
		}
	
	}
	fclose(fp2);
	if(s!=0)
	{ 
		//return s;
		return op3;
	}
	else
	{
	s=handle_symbol(OP1);
	//return s;
	op3.code=s;
	strcpy(op3.type,"s");
	return op3;
	}
		
}

struct op2 handle_op2(char op2[])
{
	char flag; 
	int a;
	struct op2 op;

	flag=check(op2);
	//printf("%c",flag);
	if(flag=='s')
	{
		a=handle_symbol(op2);
		op.type2='s';
		op.value=a;
		return op;
		
	}
	else if(flag=='l')
	{
		//printf("literal\n");
		a=handle_literal(op2);
		op.type2='l';
		op.value=a;
		return op;
	}
}

void gen_IC(struct S s , int no,struct OPTAB op)
{
	FILE *fp2;
	fp2=fopen("output.txt","a+");
	struct Imm_code imm;
	struct op2  op22;
	struct operand op11;
	imm.lc=LC;

	if(no==1)
	{

		strcpy(imm.type,op.type);
		imm.opcode=op.opcode;
		if(op.nop>0)
		{
			op11=handle_op1(s.s2);
			imm.op1=op11.code;
			strcpy(imm.type1,op11.type);
			if(op.nop==1)
			{
				printf("...%d--> (%s ,%d)- (%s,%d) \n",imm.lc,imm.type,imm.opcode,imm.type1,imm.op1);
				fprintf(fp2,"%d	%s,%d	%s,%d \n",imm.lc,imm.type,imm.opcode,imm.type1,imm.op1);
			}
			else
			{
				op22=handle_op2(s.s3);
				imm.op2.type2=op22.type2;
				imm.op2.value=op22.value;
				printf("...%d--> (%s ,%d)- (%s,%d) - (%c,%d)\n",imm.lc,imm.type,imm.opcode,imm.type1,imm.op1,imm.op2.type2,imm.op2.value);

				fprintf(fp2,"%d	%s,%d	%s,%d	%c,%d\n",imm.lc,imm.type,imm.opcode,imm.type1,imm.op1,imm.op2.type2,imm.op2.value);
			}
		}
		else
		{
			printf("...%d--> (%s ,%d) \n",imm.lc,imm.type,imm.opcode);
			fprintf(fp2,"%d	%s,%d \n",imm.lc,imm.type,imm.opcode);
		}
	}

	if(no==2)
	{
		strcpy(imm.type,op.type);
		strcpy(imm.type,op.type);
		imm.opcode=op.opcode;
		if(op.nop>0)
		{
			op11=handle_op1(s.s3);
			imm.op1=op11.code;
			strcpy(imm.type1,op11.type);
			if(op.nop==1)
			{
				printf("...%d--> (%s ,%d)- (%s,%d) \n",imm.lc,imm.type,imm.opcode,imm.type1,imm.op1);
				fprintf(fp2,"%d	%s,%d	%s,%d \n",imm.lc,imm.type,imm.opcode,imm.type1,imm.op1);
			}
			else
			{
				op22=handle_op2(s.s4);
				imm.op2.type2=op22.type2;
				imm.op2.value=op22.value;
				printf("...%d--> (%s ,%d)- (%s,%d) - (%c,%d)\n",imm.lc,imm.type,imm.opcode,imm.type1,imm.op1,imm.op2.type2,imm.op2.value);

				fprintf(fp2,"%d	%s,%d	%s,%d	%c,%d\n",imm.lc,imm.type,imm.opcode,imm.type1,imm.op1,imm.op2.type2,imm.op2.value);
			}
		}
		else
		{
			printf("...%d--> (%s ,%d) \n",imm.lc,imm.type,imm.opcode);
			fprintf(fp2,"%d	%s,%d \n",imm.lc,imm.type,imm.opcode);
		}
	}
	fclose(fp2);
}


void handle_DL(struct S s)
{
	FILE *fp2;
	fp2=fopen("output.txt","a+");
	struct Imm_code imm;
	
	
	if(strcmp(s.s2,"DC")==0)
	{
		handle_label(s.s1,LC);
		imm.lc=LC;
		strcpy(imm.type,"DL");
		imm.opcode=01;
		strcpy(imm.type1,"C");
		imm.op1=atoi(s.s3);
		
		LC++;

		printf("...%d--> (%s ,%d)- (%s,%d) \n",imm.lc,imm.type,imm.opcode,imm.type1,imm.op1);
		fprintf(fp2,"%d	%s,%d	%s,%d \n",imm.lc,imm.type,imm.opcode,imm.type1,imm.op1);
	}
	else if(strcmp(s.s2,"DS")==0)
	{

		if(check(s.s3)!='c')
			error(line,5);
		else
		{

		handle_label(s.s1,LC);
		imm.lc=LC;
		strcpy(imm.type,"DL");
		imm.opcode=02;
		


		strcpy(imm.type1,"C");
		imm.op1=atoi(s.s3);
		LC=LC+imm.op1;

		printf("...%d--> (%s ,%d)- (%s,%d) \n",imm.lc,imm.type,imm.opcode,imm.type1,imm.op1);
		fprintf(fp2,"%d	%s,%d	%s,%d \n",imm.lc,imm.type,imm.opcode,imm.type1,imm.op1);
		}
	}
			

	fclose(fp2);	
}


void operate(char inpfile[])
{
	FILE *fp;
	struct S s;
	//struct OPTAB op;
	char buf[80];
	int found=0,p;
	char z;
	fp=fopen(inpfile,"r+");
	


	//printf("Processing File ....%s\n",inpfile);
	fgets(buf,80,fp);
	sscanf(buf,"%s %s %s %s \n",s.s1,s.s2,s.s3,s.s4);			
	//printf("%s|%s|%s|%s\n",s.s1,s.s2,s.s3,s.s4);
	found = search(s);
	if(strcmp(s.s1,"START")!=0)
	{
		//printf("First Statement must be start!!\n");
		error(line,1);
	}
	else
	{
		printf("\n Start successful\n");
		handle_AD(s);

		strcpy(s.s1,"");
		strcpy(s.s2,"");
		strcpy(s.s3,"");
		strcpy(s.s4,"");

		while(fgets(buf,80,fp))
		{
			
			sscanf(buf,"%s %s %s %s \n",s.s1,s.s2,s.s3,s.s4);
			z=check(s.s1); //printf("%s",s.s3);
			line++;
			found = search(s);
			if(found==2)
			{
				//printf("Label Instruction\n");
				handle_label(s.s1,LC);
				gen_IC(s,2,op);
				LC=op.size+LC;
			}
			else if(found==1)
			{
				//printf("Instruction\n");
				
				gen_IC(s,1,op);
				LC=op.size+LC;
				
			}
			else if(strcmp(s.s1,"END")==0)
				 handle_AD(s);
			else if(strcmp(s.s1,"LTORG")==0)
				handle_AD(s);
			else if(strcmp(s.s2,"EQU")==0)
				handle_AD(s);
			else if(strcmp(s.s1,"ORIGIN")==0)
				handle_AD(s);
			else if(strcmp(s.s2,"DS")==0 || strcmp(s.s2,"DC")==0)
				handle_DL(s);
			else if(z=='l')
			{
				;
			}
			else 
			{
				error(line,2);
				
			}
			strcpy(s.s1,"");
			strcpy(s.s2,"");
			strcpy(s.s3,"");
			strcpy(s.s4,"");
			
		}
	}
		
	fclose(fp);
}

void disp_tabs()
{
	int i;
	FILE *fp1;
	struct SYMTAB sym;
	struct LITTAB lit;

		printf("\n\nSymbol Table\n");
	fp1=fopen("symtab.txt","r+");
	fread(&sym,sizeof(sym),1,fp1);
	do
	{
		printf("%d %s %d \n",sym.index,sym.symbol,sym.address);
		
	}while(fread(&sym,sizeof(sym),1,fp1));
	
	
	fclose(fp1);

		printf("\nLiteral Table\n");
	fp1=fopen("littab.txt","r+");
	fread(&lit,sizeof(lit),1,fp1);
	do
	{
		printf("%d-> %s -> %d \n",lit.no,lit.literal,lit.addr);
		
	}while(fread(&lit,sizeof(lit),1,fp1));
	

			printf("\nPOOLTAB\n");
	for(i=0;i<=pooltabptr;i++)
	{
		printf("%d\n",pooltab[i].index);
	}	
	fclose(fp1);
	
	
}


void init()
{
	FILE *fptr;
	fptr=fopen("symtab.txt","w");
	fclose(fptr);
	fptr=fopen("littab.txt","w");
	fclose(fptr);
	fptr=fopen("output.txt","w");
	fclose(fptr);

	pooltab[0].index=1;
}

int main()
{
	char inpfile[20];
	init();
	printf("Enter the name of input file :\n");
	scanf("%s",inpfile);
	//printf("Processing File ....%s\n",inpfile);
	operate(inpfile);
	
	disp_tabs();
	
	printf("Output of Pass I is stored in file output.txt \n");
	
return 0;

}
