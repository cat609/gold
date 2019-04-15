#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int line=0,mdtr=1,pp=0,ind=0,ap=0;
struct MNT
{
	char name[20];
	int MDTP;
	int PP;
};

struct S
{
	char s1[10];
	char s2[10];
	char s3[10];
	char s4[10];
	
};

struct MDT
{
	int ln_no;
	char label[10];
	char opcode[10];
	char op1[10];
	char op2[10];
};

struct PNTAB
{
	int index;
	char param[10];
};

struct APTAB
{
	int index;
	char value[10];
};

void error(int type,int line)
{
	switch(type)
	{
		case 1:printf("Line No %d : Invalid Input for Macro Preprocessor\n",line);
			break;
		case 2:printf("Line No %d : Passing parameter to non parameterised macro\n",line);
			break;
		case 3:printf("Line No %d : Expecting parameters in call\n",line);
			break;
	}
}

struct MNT search_macro(char macron[])
{
	//printf("searching ...%s\n",macron);
	FILE *fp;
	int flag=0;
	struct MNT mnt;
	fp=fopen("mnt.txt","r+");
	
	fread(&mnt,sizeof(mnt),1,fp);
	do
	{
		//printf("%s\n",mnt.name);
		if(strcmp(mnt.name,macron)==0)
		{
			flag=1; //printf("found\n");
			break;
		}
	}while(fread(&mnt,sizeof(mnt),1,fp));
	
	fclose(fp);
	if(flag==1)
		{return mnt;}
	else
	{
		mnt.MDTP=0;
		return mnt;
	}
	
}

void expand_macro(struct S s,int mdtp)
{
	FILE *fp,*fp1,*fp2;
	struct MDT mdt;
	struct MNT mnt;
	struct APTAB aptab,ap[10];
	mnt=search_macro(s.s1);
	//struct S s;
	int z=0,i;
	fp=fopen("output.txt","a+");
	fp1=fopen("mdt.txt","r");
	fp2=fopen("aptab.txt","r");
	if(mnt.PP!=0)
	{
		fread(&aptab,sizeof(aptab),1,fp2);
		for(i=0;i<mnt.PP;i++)
		{
			strcpy(ap[i].value,aptab.value);
			fread(&aptab,sizeof(aptab),1,fp2);
		}
	}
	
	
	fread(&mdt,sizeof(mdt),1,fp1);
	do
	{
		if(mdt.ln_no==mdtp||mdt.ln_no>mdtp)
		{
			//printf("line\n");
			if(strcmp(mdt.label,"MEND")==0)
				break;
			else
			{
				if(strcmp(mdt.label,"p1")==0) strcpy(s.s1,ap[0].value);
				else if(strcmp(mdt.label,"p2")==0) strcpy(s.s1,ap[1].value);
				else strcpy(s.s1,mdt.label); 

				if(strcmp(mdt.opcode,"p1")==0) strcpy(s.s2,ap[0].value);
				else if(strcmp(mdt.opcode,"p2")==0) strcpy(s.s2,ap[1].value);
				else strcpy(s.s2,mdt.opcode);

				if(strcmp(mdt.op1,"p1")==0) strcpy(s.s3,ap[0].value);
				else if(strcmp(mdt.op1,"p2")==0) strcpy(s.s3,ap[1].value);
				else strcpy(s.s3,mdt.op1);

				if(strcmp(mdt.op2,"p1")==0) strcpy(s.s4,ap[0].value);
				else if(strcmp(mdt.op2,"p2")==0) strcpy(s.s4,ap[1].value);
				else strcpy(s.s4,mdt.op2);
				fprintf(fp,"%s %s %s %s \n",s.s1,s.s2,s.s3,s.s4);
			}
			
		}
		else
			continue;
	}while(fread(&mdt,sizeof(mdt),1,fp1));
	
	
	fclose(fp);
	fclose(fp1);
	fclose(fp2);
}

void macro(char ip[])
{
	FILE *fp,*fp1,*fp2,*fp3,*fp4,*fp5;
	struct MNT mnt;
	struct MDT mdt;
	struct PNTAB pntab;
	struct APTAB aptab;
	struct S s;
	int found=0,z;
	char p1[10],p2[10];
	fp=fopen(ip,"r+");
	fp1=fopen("output.txt","a+");
	char buf[80];

	while(1)
	{
	fgets(buf,80,fp);
	sscanf(buf,"%s %s %s %s \n",s.s1,s.s2,s.s3,s.s4);
	line++;
	//printf("Starting Again\n");
		if(strcmp(s.s1,"MACRO")==0)
		{
			pp=0; ind=0;
			fp2=fopen("mnt.txt","a+");
			fp3=fopen("mdt.txt","a+");
			fp4=fopen("pntab.txt","a+");
			
			//read and put macro name in MNT
			strcpy(mnt.name,s.s2);
			mnt.MDTP=mdtr;
			if(strcmp(s.s3,"")!=0) 
			{
				pp++;
				z=strlen(s.s3);
				char *new=(char*)malloc(sizeof(z-1));
				int i=0;
				for(i=0;i<(z-1);i++)
				new[i]=s.s3[i+1];
				new[i]='\0'; //printf("%s\n",new);
				strcpy(pntab.param,new);
				pntab.index=++ind;
				fwrite(&pntab,sizeof(pntab),1,fp4);
				strcpy(p1,s.s3);
				
			} 
			if(strcmp(s.s4,"")!=0)
			{
				pp++; 
				z=strlen(s.s4);
				char *new=(char*)malloc(sizeof(z-1));
				int i=0;
				for(i=0;i<(z-1);i++)
				new[i]=s.s4[i+1];
				new[i]='\0'; //printf("%s\n",new);
				strcpy(pntab.param,new);
				pntab.index=++ind;
				fwrite(&pntab,sizeof(pntab),1,fp4);
				strcpy(p2,s.s4);
			}
			mnt.PP=pp;
			fwrite(&mnt,sizeof(mnt),1,fp2);

			strcpy(s.s1,"");
			strcpy(s.s2,"");
			strcpy(s.s3,"");
			strcpy(s.s4,"");
			fgets(buf,80,fp);
			sscanf(buf,"%s %s %s %s \n",s.s1,s.s2,s.s3,s.s4);
			line++;
			while(strcmp(s.s1,"MEND")!=0)
			{
				mdt.ln_no=mdtr++;
				if(strcmp(p1,s.s1)==0)strcpy(mdt.label,"p1");else if(strcmp(p2,s.s1)==0)strcpy(mdt.label,"p2");else strcpy(mdt.label,s.s1);
				if(strcmp(p1,s.s2)==0)strcpy(mdt.opcode,"p1");else if(strcmp(p2,s.s2)==0)strcpy(mdt.opcode,"p2");else strcpy(mdt.opcode,s.s2);
				if(strcmp(p1,s.s3)==0)strcpy(mdt.op1,"p1");else if(strcmp(p2,s.s3)==0)strcpy(mdt.op1,"p2");else strcpy(mdt.op1,s.s3);
				if(strcmp(p1,s.s4)==0)strcpy(mdt.op2,"p1");else if(strcmp(p2,s.s4)==0)strcpy(mdt.op2,"p2");else strcpy(mdt.op2,s.s4);
				fwrite(&mdt,sizeof(mdt),1,fp3);

				strcpy(s.s1,"");
				strcpy(s.s2,"");
				strcpy(s.s3,"");
				strcpy(s.s4,"");

				fgets(buf,80,fp);
				sscanf(buf,"%s %s %s %s \n",s.s1,s.s2,s.s3,s.s4);
				line++;
			
			}
			//printf("%s\n",s.s1);
			mdt.ln_no=mdtr++;
			strcpy(mdt.label,"MEND");
			strcpy(mdt.opcode,"");
			strcpy(mdt.op1,"");
			strcpy(mdt.op2,"");
			fwrite(&mdt,sizeof(mdt),1,fp3);
			
			fclose(fp2);
			fclose(fp3);
			fclose(fp4);
			
			continue;
		}
		else if(strcmp(s.s1,"START")==0)
		{
			//printf("Entering code from start\n");
			fprintf(fp1,"%s %s %s %s \n",s.s1,s.s2,s.s3,s.s4);
			//printf("%s %s %s %s \n",s.s1,s.s2,s.s3,s.s4);
			strcpy(s.s1,"");
			strcpy(s.s2,"");
			strcpy(s.s3,"");
			strcpy(s.s4,"");
			
			while(fgets(buf,80,fp))
			{
				sscanf(buf,"%s %s %s %s \n",s.s1,s.s2,s.s3,s.s4);
				//printf("%s %s %s %s \n",s.s1,s.s2,s.s3,s.s4);
				line++;
								
				mnt=search_macro(s.s1); //printf("%d\n",found);	
				found=mnt.MDTP;//printf("found %d\n",found);
				if(found ==0)
				{
					fprintf(fp1,"%s %s %s %s \n",s.s1,s.s2,s.s3,s.s4);
					//printf("%s %s %s %s \n",s.s1,s.s2,s.s3,s.s4);
				}
				else 
				{
					
					fclose(fp1);
					fp5=fopen("aptab.txt","a+");
					ap=0; 
					if(mnt.PP==0 && strcmp(s.s2,"")!=0)
					{
						error(2,line);
					}
					else if(mnt.PP==1)
					{
						if(strcmp(s.s2,"")!=0)
						{
							strcpy(aptab.value,s.s2);
							aptab.index=++ap;
							fwrite(&aptab,sizeof(aptab),1,fp5);
						}
						else error(3,line);
					}
					else if(mnt.PP==2)
					{
						int i;
						int len=strlen(s.s2);
						char *newstr=(char*)malloc(sizeof(len-1));
						for( i=0;i<len-1;i++)
							newstr[i]=s.s2[i];
							newstr[i]='\0';
						if(strcmp(newstr,"")!=0)
						{
							strcpy(aptab.value,newstr);
							aptab.index=++ap;
							fwrite(&aptab,sizeof(aptab),1,fp5);
						}
						else error(3,line);
						if(strcmp(s.s3,"")!=0)
						{
							strcpy(aptab.value,s.s3);
							aptab.index=++ap;
							fwrite(&aptab,sizeof(aptab),1,fp5);
						}
						else error(3,line);
					}
					fclose(fp5);
					expand_macro(s,found);
					fp1=fopen("output.txt","a+");
				}		
				strcpy(s.s1,"");
				strcpy(s.s2,"");
				strcpy(s.s3,"");
				strcpy(s.s4,"");
				
			}
			break;
			
		}
		else
			error(1,line);
			break;
	}
	fclose(fp1);
	fclose(fp);
	
}

void init()
{
	FILE *fp;
	fp=fopen("output.txt","w");
	fclose(fp);
	fp=fopen("mdt.txt","w");
	fclose(fp);
	fp=fopen("mnt.txt","w");
	fclose(fp);
	fp=fopen("pntab.txt","w");
	fclose(fp);
	fp=fopen("aptab.txt","w");
	fclose(fp);
}

void display()
{
	FILE *fp;
	char buf[80];
	struct MNT mnt;
	struct MDT mdt;
	struct PNTAB pntab;
	struct APTAB aptab;

	fp=fopen("output.txt","r+");
	
	printf("\n\n Output :\n");
	while(fgets(buf,80,fp))
	{
		printf("%s",buf);
	}
	fclose(fp);

	printf("\n\nMNT TAB\n");
	fp=fopen("mnt.txt","r+");
	fread(&mnt,sizeof(mnt),1,fp);
	do
	{
		printf("%s %d %d\n",mnt.name,mnt.MDTP,mnt.PP);
	}while(fread(&mnt,sizeof(mnt),1,fp));
	fclose(fp);

	printf("\n\nMDT TAB\n");
	fp=fopen("mdt.txt","r+");
	fread(&mdt,sizeof(mdt),1,fp);
	do
	{
		printf("%d %s %s %s %s\n",mdt.ln_no,mdt.label,mdt.opcode,mdt.op1,mdt.op2);
	}while(fread(&mdt,sizeof(mdt),1,fp));
	fclose(fp);

	printf("\n\nPNTAB\n");
	fp=fopen("pntab.txt","r+");
	fread(&pntab,sizeof(pntab),1,fp);
	do
	{
		printf("%d %s \n",pntab.index,pntab.param);
	}while(fread(&pntab,sizeof(pntab),1,fp));
	fclose(fp);

	printf("\n\nAPTAB\n");
	fp=fopen("aptab.txt","r+");
	fread(&aptab,sizeof(aptab),1,fp);
	do
	{
		printf("%d %s \n",aptab.index,aptab.value);
	}while(fread(&aptab,sizeof(aptab),1,fp));
	fclose(fp);
}

int main()
{
	char ip[20];
	printf("Enter the name of input file\n");
	scanf("%s",ip);
	init();
	macro(ip);
	display();
	return 0;
}
