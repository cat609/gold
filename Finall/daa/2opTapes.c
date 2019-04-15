#include<stdio.h>
#include<stdlib.h>

struct files
{
	int size;
	char fname[20];
};

int tapes_sum[20]={0};

int merge(struct files a[],int first,int last,int mid)
{

 	struct files arr2[100];
 	int i=first,j=mid+1,k=0;
 	while(i<=mid && j<=last)
 	{
   		if(a[i].size<a[j].size) 
   		{
     			arr2[k]=a[i];
     			i++;
   		}
	   	else	
   		{
     			arr2[k]=a[j];
     			j++;
   		}
  		k++;
 	}
 	while(i<=mid)						
 	{
   		arr2[k]=a[i];
   		k++;
   		i++;
 	}
	while(j<=last)							
 	{
  		arr2[k]=a[j];
  		j++;
  		k++;
 	}
 	for(i=first,k=0;i<=last;i++)			
 	{
   		a[i]=arr2[k];
  		k++;
 	}
}

void sort(struct files a[],int first,int last)
{
	int mid=(first+last)/2;
 	if(first!=last)
 	{
 		sort(a,first,mid);				
 		sort(a,mid+1,last);				
 		merge(a,first,last,mid);		
 	}
}

void store(struct files tape[][10],struct files file[],int num_of_tapes,int filled[],int num)
{
 	int i,j,k=0,flag=0;
 	for(i=0;i<10;i++)
 	{	 
  		for(j=0;j<num_of_tapes;j++)
	 	{
  			if(tapes_sum[j]>=file[k].size)				
		  	{
  				filled[j]++;					
			  	tape[j][i]=file[k];						
		  		tapes_sum[j]-=file[k].size;					
				k++;	  				
  			}
  			else flag=1;							
  			if(flag==1) break;						
    			if(k==num)break;						
  		}
 
	  	if(flag==1)break;							
  		if(k==num)break;							
 	}

 	printf("\ni is %d and j is %d\n",i,j);
 	if(k==num)									
 	{
  		printf("\nAll files are stored on the tapes!\n");
 	}
 	else
 	{
  		printf("\nFollowing files are not stored on the tapes :\n");
  		for(i=k;i<num;i++)
  		{
  			printf("(%s,%d)\n",file[i].fname,file[i].size);	
  		}
	}
}

int isAscending(struct files file[], int n)
{
    if (n == 1 || n == 0)
        return 1;
    if (file[n-1].size < file[n-2].size)
        return 0;
    return isAscending(file, n-1);
}

int isDescending(struct files file[], int n)
{
    if (n == 1 || n == 0)
        return 1;
    if (file[n-1].size > file[n-2].size)
        return 0;
    return isDescending(file, n-1);
}



void reverse(struct files file[], int n)
{
	int i,j;
	i=0;j=n;
	struct files temp[3];

	while(i<j)
	{
		temp[0]=file[i];
		file[i]=file[j];
		file[j]=temp[0];
		
		i++;
		j--;
	}	

	printf("\nArray sorted in ascending:\n");
	for(i=0;i<=n;i++)
	{
		printf("%s %d\n",file[i].fname,file[i].size);
	}
}

int main()
{
 	struct files tape[100][10];
 	struct files file[100];
 	int i,num,num_of_tapes,filled[100],j,tape_size,asc,dsc;

 	printf("\nEnter the number of files: ");							
 	scanf("%d",&num);	

	for(i=0;i<num;i++)
 	{
   		printf("\nEnter the name and size of the file :");
   		scanf("%s%d",file[i].fname,&file[i].size);			
	}

 	printf("\nEnter the total number of tapes: ");
 	scanf("%d",&num_of_tapes);						

 	printf("\nEnter size of each tape: ");
 	scanf("%d",&tape_size);						

 	for(i=0;i<num_of_tapes;i++)					
 	{
	 	tapes_sum[i]=tape_size;							
 	}

	asc=isAscending(file,num-1);
	
	if(asc==0)
	{
		dsc=isDescending(file,num-1);
		if(dsc==0)
		 	sort(file,0,num-1);									
		else
		{
			printf("\nThe files are in descending order of size\nReversing..\n");
			reverse(file,num-1);
		}		
	}
	else
		printf("\nFiles are in ascending order of sizes..!\n");

 	store(tape,file,num_of_tapes,filled,num);			

 	printf("\nContents of tapes :\n");
 	for(i=0;i<num_of_tapes;i++)
 	{
  		printf("\nTape %d :",i);
  		for(j=0;j<filled[i];j++)
  		{
    			printf("(%s,%d) ",tape[i][j].fname,tape[i][j].size);		 
  		}
 	}

 	for(i=0;i<num_of_tapes;i++)
 	{
 		printf("\n\nTotal size remained on tape %d is :%d",i,tapes_sum[i]);			
 	}
 
	printf("\n");
  	return 0;
}


/*
itexam@c05l0720:~$ gcc ass2.c
itexam@c05l0720:~$ ./a.out

Enter the number of files: 4

Enter the name and size of the file :1
2

Enter the name and size of the file :2
1

Enter the name and size of the file :2
3

Enter the name and size of the file :1
3

Enter the total number of tapes: 3

Enter size of each tape: 2

i is 0 and j is 2

Following files are not stored on the tapes :
(1,3)
(2,3)

Contents of tapes :

Tape 0 :(2,1) 
Tape 1 :(1,2) 
Tape 2 :

Total size remained on tape 0 is :1

Total size remained on tape 1 is :0

Total size remained on tape 2 is :2


*/

