#include<stdio.h>
//#include<conio.h>
int cost[10][10],n;
struct term1{
	int a,b;
};
typedef struct term1 l;

l list[600];  // to store level of recursion and index that gives minimum

struct term{
  int val;
	int index;
	int ival;
};
typedef struct term aterm;

int count=1;
int find_min(aterm a[10], int len, int *p,int *r)
{
  int i,min;
  min=a[1].val;           // minimum
  *p=a[1].index;          // index
  *r=a[1].ival;           // level
  for(i=2;i<=len;i++)
     if(a[i].val < min) {
			 min = a[i].val;
			 *p = a[i].index;
			 *r = a[i].ival;
		 }
  return min;
}

int gis(int a, int s[10], int m1, int v[10])
{
  int min,i,j,k,p,q,m,r,ind,set[10],visited[10];
  aterm x[10];
  i=a; m=m1;  // a is last city visited , m cities yet to be visited
  for(k=1;k<=n;k++) 
    visited[k]=v[k];
  visited[i]=1;  // last visited city, true assignment
  if(m==1) 
    return(cost[i][s[1]] + cost[s[1]][1]); // terminating condition
  
  for(ind=1;ind<=m;ind++) // prepare new set for next recursion
  {
     j=s[ind];      // j is next next city
     p=1;
     for(k=1;k<=n;k++)
     {
	     if((k!=j) && (!visited[k]))
	     {
	     	set[p]=k;
	     	p++;
	  	 }
     }
     x[ind].val = cost[i][j] + gis(j,set,m-1,visited);
     x[ind].index = j;
     x[ind].ival = i;
  }
  
  min=find_min(x,m,&q,&r);    // find minimum
  list[count].a=r;   // add to list for finding path
  list[count].b=q;
  count++;
  return min;
 }
 
 int main()
 {
   int city,v[10],s[10],i,j,k,min,path[10],p,index;
   int dec,done,rcount,total[10],n1;

   printf("enter no of cities:");
   scanf("%d",&n);
   printf("enter complete cost matrix including 0\n");
   for(i=1;i<=n;i++)
     for(j=1;j<=n;j++)
       scanf("%d",&cost[i][j]);
   
   printf("cost matrix is\n");
   for(i=1;i<=n;i++)
    {
      for(j=1;j<=n;j++)
	      printf("\t%d",cost[i][j]);
      printf("\n");
    }

   for(i=1;i<=n-1;i++)
    {
     s[i]=i+1;
     v[i]=0;
    }
    v[n]=0;
    min=gis(1,s,n-1,v);
    //getch();
    /*clrscr();
    printf("count=%d\n",count-1);
    getch();
    printf("last %d %d\n ", list[count-1].a,list[count-1].b);*/
    total[3]=1; // pattern
    if(n>4)
    {
	    for(i=4;i<=n;i++)
	     	total[i]=(i-1)*total[i-1]+1; // compute patterns
    }

   for(i=2;i<=n;i++) 
      v[i]=0;
   path[1]=1; v[1]=1;
   city=list[count-1].b;
   path[2]=city; v[city]=1;    j=3; // found 2 cities next city index at 3
   
   if(n>3)
   {
   		p=(city-1)*total[n-1];
   		city=list[p].b;
   		path[3]=city;v[city]=1; j=4; // found 3 cities, next city stored at index 4
   		rcount=n-4;
   		n1=n;
   		for(k=1;k<=rcount;k++) // this loop will be executed if no of cities > 4
   		{
     		p=p-1;
     		dec=total[n1-2];
     		for(i=1;i<=n1-2;i++)
     		{
      		if(list[p].a!=city) // locate the pattern with base
	  				p=p-dec;
      		else
					{
	  				city =list[p].b;
	  				path[j]=city;
	  				v[city]=1;
	 					j++;
	  				break;
					}
     		}
    		n1=n1-1;
  		}
   //printf("visited array is:\n");
   		printf("\n");
 		}
 		// for last city
   i=2;
   done=0;
   while(done==0)
   {
      if(v[i]==0)
	    { 
	    	path[j] = i;
	    	v[i]=1;
	    	j++;
	    	done=1;
	    }
      else i++;
    }
     
    path[j]=1;

    printf("shortest tour for Travelling Salesman is\n");
    printf("1-->");
    for(i=2;i<=n;i++)
	     printf("%d-->",path[i]);
    printf("1\n");

    printf("min dist is %d\n",min);
    return 0;
}
