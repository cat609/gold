#include<stdio.h>
int min,max;

void max_min(int a[30],int i,int j)
{
int min1,max1,mid;//5
if(i==j)
{
	min=max=a[i];
}
else if(i==j-1)
{
	if(a[i]>a[j])
	{	max=a[i];
		min=a[j];
	}
	else
	{
		max=a[j];
		min=a[i];
	}
}

else
{
	mid=(i+j)/2;
	max_min(a,i,mid);
	min1=min;
	max1=max;
	max_min(a,mid+1,j);
	
	     if(min1<min)
             min=min1;
        
         if(max1>max)
     
            max=max1;
           
}
}
int main()
{
	int a[30],n,i;
	printf("\nEnter number of elements");
	scanf("%d",&n);
	for(i=0;i<n;i++)
	{
	printf("\nEnter element:");
	scanf("%d",&a[i]);
	}
	max_min(a,0,n-1);
	printf("min %d max %d",min,max);
	
}


/*

itexam@c05l0720:~$ gcc ass1.c
itexam@c05l0720:~$ ./a.out

Enter number of elements 4

Enter element:1

Enter element:3

Enter element:2

Enter element:5
min 1 max 5itexam@c05l0720:~$



*/
