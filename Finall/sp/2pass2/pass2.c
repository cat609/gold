#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void passTwo();

struct sym_tab
{
	int index;
	char name[10];
	int address;
};

struct lt_tab
{
	int index;
	char literal[5];
	int lc_val;
};

struct lt_pool
{
	int pool;//ltpool

};

int main(void)
{
	passTwo();
	return EXIT_SUCCESS;
}

void passTwo()
{

	//dynamic
	struct sym_tab symtab[10];
	int symptr=0;

	//dynamic
	struct lt_tab lttab[10];
	int ltptr=0;

	struct lt_pool ltpool[10];
	int ltpoolptr=0;

	int LC=0;

	char data[25],m1[3],m2[3],m3[3],m4[3],m5[3],m6[3],m7[4];
	FILE *fp,*fp1;

	int i=1;

	///////////////////////////////////////////////////////////////////////////////////////////////////////////


	//to store content of  literal file into structure
	fp=fopen("littab1.txt","r");
	
	do
	{       fgets(data,25,fp);
		sscanf(data,"%d %s %d",&lttab[i].index,lttab[i].literal,&lttab[i].lc_val);
		i++;
		memset(data,0,sizeof(data));

	}while(!feof(fp));
	fclose(fp);

//////////////////////////////////////////////////////////////////////////////////////////////////////////

        i--;
int j=0;
	for(j=1;j<i;j++)
	{
		printf("\n %d %s %d",lttab[j].index,lttab[j].literal,lttab[j].lc_val);
		
	}

///////////////////////////////////////////////////////////////////////////////////////////////////////////

	i=1;



	fp=fopen("symboltab1.txt","r");
	
	do
	{	fgets(data,25,fp);
		sscanf(data,"%d %s %d",&symtab[i].index,symtab[i].name,&symtab[i].address);
	        i++;
		memset(data,0,sizeof(data));
	

	}while(!feof(fp));

	fclose(fp);

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
i--;
						for(j=1;j<i;j++)
						{
							printf("\n %d %s %d",symtab[j].index,symtab[j].name,symtab[j].address);
							
						}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

						fp=fopen("ipass2.txt","r");
						fp1=fopen("pass2out.txt","w+");
						strcpy(data,"\0");
						fgets(data,25,fp);



						do
						{
							int a;
                                                        	fgets(data,25,fp);

							sscanf(data,"%s%s%s%s%s%s%s",m1,m2,m3,m4,m5,m6,m7);

							printf("\n%s\t%s\t%s\t%s\t%s\t%s\t%s",m1,m2,m3,m4,m5,m6,m7);


							if(strcmp(m2,"IS")==0 )
							{

									if(strcmp(m6,"S")==0)
									{
										a=atoi(m7);
										fprintf(fp1,"%s) + %s %s %d\n",m1,m3,m5,symtab[a].address);
										fprintf(fp1,"%s","\n");
									}

									else if(strcmp(m6,"L")==0)
									{

										a=atoi(m7);
										fprintf(fp1,"%s) + %s %s %d\n",m1,m3,m5,lttab[a].lc_val);
										fprintf(fp1,"%s","\n");
									}

									else
									{printf("\n****************");
										fprintf(fp1,"%s) + %s \n",m1,m3);
										fprintf(fp1,"%s","\n");
									}

							}


							else if(strcmp(m2,"DL")==0) //DS
							{
								if(strcmp(m3,"2")==0)
								{printf("Hii");
									//for ds,keeping empty location of required ds
									for(i=0;i<atoi(m5);i++)
									{
										a=atoi(m1);

										fprintf(fp1,"%d)\n",atoi(m1));
										a++;
									}
								}

								else
								{

									fprintf(fp1,"%s) + %s %s\n",m1,m2,m3);


								}

							}

							else if(strcmp(m1,"AD")==0){
                                                                 if(strcmp(m2,"5")==0)
                                                                 { 
                                                                      if(strcmp(m3,"L")==0)
									{
                                                                            
										a=atoi(m4);
										fprintf(fp1,"%d)\n",lttab[a].lc_val);
										fprintf(fp1,"%s","\n");
									}

                                                                 }

							}else{}

						
memset(data,0,sizeof(data));
memset(m1,0,sizeof(m1));
memset(m2,0,sizeof(m2));
memset(m3,0,sizeof(m3));
memset(m4,0,sizeof(m4));
memset(m5,0,sizeof(m5));
memset(m6,0,sizeof(m6));
memset(m7,0,sizeof(m7));

						}while(!feof(fp));

						fclose(fp);
						fclose(fp1);








}
