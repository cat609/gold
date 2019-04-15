#include<stdio.h>
#include<string.h>
#include<stdlib.h>


//1st pass does analysis hence generating 1.IC   2.SYMBOL-TABLE   3.LITERAL-TABLE   4.CONDITION CODE TABLE
//we need data structures OPTAB,SYMTAB,LTTAB,LTPOOL


//defining optab structure
struct OPTAB{
char mne[20];
int opcode;
int size;
char type[10];
int no_oprands;
}optab[20]={{"STOP",00,1,"IS",0},{"ADD",01,1,"IS",2},{"SUB",02,1,"IS",2},{"MULT",03,1,"IS",1},{"MOVER",04,1,"IS",2},{"MOVEM",05,1,"IS",2},{"COMP",06,1,"IS",2},{"BC",07,1,"IS",1},{"DIV",8,1,"IS",1},{"READ",9,1,"IS",1},{"PRINT",10,1,"IS",1},{"START",01,0,"AD",1},{"END",02,0,"AD",1},{"ORIGIN",03,0,"AD",0},{"EQU",04,0,"AD",0},{"LTORG",05,0,"AD",0},{"DC",01,1,"DL",1},{"DS",02,1,"DL",1}};


//defining condition code structure
struct reg_cond
{
 char type[5];
 int opcode;
 char t[5];
}reg_cond[10]={{"LT",01,"CC"},{"LE",02,"CC"},{"EQ",03,"CC"},{"GT",04,"CC"},{"GE",05,"CC"},{"ANY",06,"CC"},{"AREG",01,"R"},
		        {"BREG",02,"R"},{"CREG",03,"R"}};

//defining literal tab structure
struct literal
{
	char literal[5];
	int address;
}lit[20];

//defining symbol tab structure
struct symbol
{
char sym[10];
int addr;
int length;
}symm[10];


int ip=0,sym_count=0,flag=0,pooltab_index=0,lit_count=0,pooltab[20];

int  optabsearch(char str[20], struct OPTAB *result);
void handlesymbol(FILE *fp2,char str[10]);
void handleasm(FILE *fp2,struct OPTAB result,char s1[10],char s2[10],char s3[10],char s4[10]);
void handle_mnemonic(FILE *fp2,struct OPTAB optabb,char s1[10],char s2[10],char s3[10],char s4[10]);
void handleimperativestmt(FILE *fp2,struct OPTAB opatbb,char s1[10],char s2[10],char s3[10],char s4[10]);
int  symbolsearch(char str[10]);
int searchliteral(char str[10]);

int main()
{
int i,ret,val;
FILE *fp,*fp2,*fp3;
struct OPTAB optabb;
struct symbol symmm;
pooltab[0]=1;
char s1[10],s2[10],s3[10],s4[10],str[30];
s1[0]='\0';
s2[0]='\0';
s3[0]='\0';
s4[0]='\0';
fp=fopen("ippass1.txt","r+");
	if(fp==NULL)
          printf("\nerror while opening file");
       fp2=fopen("ipass2.txt","w");
        if(fp==NULL)
          printf("\nerror while opening file");

      
do
{
fgets(str,100,fp);
                      if(strlen(str)==0)
			{
				break;
			}
sscanf(str,"%s%s%s%s",s1,s2,s3,s4);
printf("\n%s\t%s\t%s\t%s",s1,s2,s3,s4);
//If Mnemonic
ret=optabsearch(s1,&optabb);
if(ret==0)
{
    handle_mnemonic(fp2,optabb,s1,s2,s3,s4);
    
}
//If Label
else
{
	val=symbolsearch(s1);
        
	if(val==0)
	{
		printf("Symbol not found");
		sym_count++;
		strcpy(symm[sym_count].sym,s1);
                symm[sym_count].length=0;
                symm[sym_count].addr=ip;
                ret=optabsearch(s2,&optabb);
                handle_mnemonic(fp2,optabb,s2,s3,s4,s1);
                ip=ip+symm[sym_count].length;           
       }
	else
	{
		ret=optabsearch(s2,&optabb);
		handle_mnemonic(fp2,optabb,s2,s3,s4,s1);
		if(symm[val].addr==-1)
		{       symm[val].addr=ip;
			ip=ip+symm[val].length;
		}
        	else
		{
			printf("\n*Duplicate Label");
                	return 0;
		}

	}
}
memset(str,0,sizeof(str));
memset(s1,0,sizeof(s1));

memset(s2,0,sizeof(s2));
memset(s3,0,sizeof(s3));
memset(s4,0,sizeof(s4));
}while(!feof(fp));
fclose(fp);


//Printing Pool Tab

for(i=pooltab[pooltab_index];i<=lit_count;i++)
{   
	lit[i].address=ip;
         ip=ip+1;
 
}



//printing Symbol Tab
fp3=fopen("symboltab1.txt","w");
printf("\n------------SYMBOL TABLE----------------");
for(i=0;i<sym_count;i++)
{
	printf("\n%d\t%s\t%d\t%d",i+1,symm[i+1].sym,symm[i+1].addr,symm[i+1].length);
        fprintf(fp3,"%d\t%s\t%d\n",i+1,symm[i+1].sym,symm[i+1].addr);
}
fclose(fp3);
//printing Literal tab
printf("\n------------Literal TABLE----------------");
fp3=fopen("littab1.txt","w");
for(i=0;i<lit_count;i++)
{   
	printf("\n%d\t%s\t%d",i+1,lit[i+1].literal,lit[i+1].address);
       fprintf(fp3,"%d\t%s\t%d\n",i+1,lit[i+1].literal,lit[i+1].address);
}
fclose(fp3);

//Printing Literal Pool
fp3=fopen("pooltab1.txt","w");
printf("\n-----------LITERAL POOL-------------");
printf("\n INDEX\tLITERAL TABLE IDX\n");
for(i=0;i<=pooltab_index;i++)
{   
	printf("%d\t%d\n",i,pooltab[i]);
        fprintf(fp3,"%d\n",pooltab[i]);
}
fclose(fp3);

return 0;
}




//Handle Mnemonic*******************************************************************************************************************
void handle_mnemonic(FILE *fp2,struct OPTAB optabb,char s1[10],char s2[10],char s3[10],char s4[10])
{

int i;
	for(i=0;i<=18;i++)
	{
	if(strcmp(s1,optab[i].mne)==0)
	{
	
	}

	else
	{
		printf("\n *Invalid Mnemonic:%s",s1);
		return ;
	}
}



	if(strcmp(optabb.type,"AD")==0)
     {
     printf("Assembler Directive Found");
     handleasm(fp2,optabb,s1,s2,s3,s4);
     }
     if(strcmp(optabb.type,"IS")==0 || strcmp(optabb.type,"DL")==0 )
      {
	printf("Imperative Statement found");
	handleimperativestmt(fp2,optabb,s1,s2,s3,s4);

     }



}





//Handle Assembler Directive*******************************************************************************************
void handleasm(FILE *fp2,struct OPTAB result,char s1[10],char s2[10],char s3[10],char s4[10])
{

int val=0,i;
val=atoi(s2);
fprintf(fp2,"\n");
if(strcmp(result.mne,"START")==0)
	    {
   	    	 ip=val;
	    	 fprintf(fp2," %s  %d %s  %d",result.type,result.opcode,"C",val);
	    }
   	    if(strcmp(result.mne,"END")==0)
   	    {
   	    	fprintf(fp2,"%s  %d",result.type,result.opcode);
   	    	
            }
            if(strcmp(result.mne,"ORIGIN")==0)
            {
               if(strcmp(s3,"+")==0)
                {
                    int ret=symbolsearch(s2);   
                    ip=symm[ret].addr+atoi(s4);
                }
                else{
               
                	ip=val=atoi(s2);}
                	fprintf(fp2," %s  %d C %d ",result.type,result.opcode,ip);
            }
            if(strcmp(result.mne,"LTORG")==0)
            {
              pooltab_index++;
              pooltab[pooltab_index]=lit_count+1;
               for(i=pooltab[pooltab_index-1];i<pooltab[pooltab_index];i++)
                  {
                          lit[i].address=ip;
                          ip=ip+1;
                  }
               fprintf(fp2," %s  %d",result.type,result.opcode);
            }
           
              if(strcmp(result.mne,"EQU")==0)
              {  fprintf(fp2,"%s %d",result.type,result.opcode);
                  int ret=symbolsearch(s2);
                  if(ret!=0)
			{ 
                                      handlesymbol(fp2,s4);
                                      int r=symbolsearch(s2);
                                      int val2=symbolsearch(s4);
                                      symm[val2].addr=symm[r].addr;
                                      fprintf(fp2," C %d", symm[val2].addr);    
			}
             
            }

            

   	    
}


//Handle Imperative Statement******************************************************************************************************
void handleimperativestmt(FILE *fp2,struct OPTAB result,char s1[10],char s2[10],char s3[10],char s4[10])
{
int i,size,val=-1;
fprintf(fp2,"\n%d",ip);
	
     if(strcmp(s1,"DS")==0)
     {
        val=symbolsearch(s4);
        symm[val].length=atoi(s2);
        fprintf(fp2," %s %d C %d",result.type,result.opcode,symm[val].length);
        return;
     }
     else if(strcmp(s1,"DC")==0)
     {
        val=symbolsearch(s4);
        symm[val].length=1;
        s2[0]=s2[1];
        s2[1]='\0';
        fprintf(fp2," %s %d C %d",result.type,result.opcode,atoi(s2));
        return;
     }
    else{
           ip=ip+result.size;
           fprintf(fp2," %s %d",result.type,result.opcode);
	}

/////////////for condition code////////
	for(i=0;i<9;i++) 
	{
		if(strcmp(s2,reg_cond[i].type)==0)
		{       flag=1;
			fprintf(fp2," %s %d",reg_cond[i].t,reg_cond[i].opcode);
                        break;
		}
	}

	if(flag==0)
		{//Symbol Handling
 			handlesymbol(fp2,s2);
		}                                                  
	if(s3[0]!='=' && s3[0]!='\0')
    		{
      			handlesymbol(fp2,s3);
    		}
	//Literal Handiling
    	if(s3[0]=='=' && s3[0]!='\0')
	{
            
          	val=searchliteral(s3);
            	if(val!=0);
            	else
               	{           
                     printf("\nLiteral Not Found");  
                     lit_count++;
                     strcpy(lit[lit_count].literal,s3);
                     lit[lit_count].address=-1;
                     fprintf(fp2," L %d",lit_count);
                   
                   
                }           
         }

}

//OPTAB Search**************************************************************************************************
int optabsearch(char str[20], struct OPTAB *result)
{
	int i;
	for(i=0;i<=18;i++)
	{
	if(strcmp(str,optab[i].mne)==0)
	{
	  *result=optab[i];
	  return 0;
	}
	}

	return 1;
}

//Symbol Searh*****************************************************************************************************
int symbolsearch(char str[10])
{
        int i;
	for(i=0;i<=sym_count;i++)
	{

		if(strcmp(str,symm[i].sym)==0)
		{
	 	 return (i);
		}
	}

	return 0;
}

//Literal Search**************************************************************************************************
int searchliteral(char str[10])
{
int i;

	for(i=pooltab[pooltab_index];i<=lit_count;i++)
 	{
		if(strcmp(lit[i].literal,str)==0)
     		return i;
 	}
 	return 0;
}



//Symbol Handling***************************************************************************************************
void handlesymbol(FILE *fp2,char str[10])
{
	int val1;
	val1=symbolsearch(str);
	if(val1==0)
	{
		printf("\n Symbol not found");
		sym_count++;
		strcpy(symm[sym_count].sym,str);
		symm[sym_count].addr=-1;
		fprintf(fp2," S %d",sym_count);
	}
	else
	{
   		fprintf(fp2," S %d",val1);
	}
}

