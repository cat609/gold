#include<stdio.h>
#include<stdlib.h>

int heap_size=0;
int v=0;
typedef struct term
{
	int cost;
	int path[10];
	int matrix[10][10];
}hterm;
hterm list[25];
void insert(hterm element)
{

    heap_size++;

    list[heap_size] = element; 

    int now = heap_size;

    while (list[now / 2].cost > element.cost) {

        list[now] = list[now / 2];

        now /= 2;

    }

    list[now] = element;

}


hterm delete()
{
	    hterm minElement, lastElement;
		int now,child;

    	minElement = list[1];

    	lastElement = list[heap_size--];
		
	for (now = 1; now * 2 <= heap_size; now = child)
	 {
		child = now * 2;
		if (child != heap_size && list[child + 1].cost < list[child].cost)
		 {

            		child++;

        	}
		if (lastElement.cost > list[child].cost) 
		{

            		list[now] = list[child];

        	} else 
		break;

       		
    }

	list[now] = lastElement;

        return minElement; 

}
	


void output(int graph[][10])
{
	int i,j;
	for (i=1;i<=v;i++)
	{
		for(j=1;j<=v;j++)
		{
			printf(" %d ",graph[i][j]);
		}
		printf("\n");
	}
}

int colReduction(int red_mat[][10],int col[],int v)
{
	int i,j;
	for(i=1;i<=v;i++)
		col[i]=999;
		
	for(i=1;i<=v;i++)
	{
		for(j=1;j<=v;j++)
		{
			if(red_mat[i][j]<col[j])
				col[j]=red_mat[i][j];
		}
	}
	
	for(i=1;i<=v;i++)
	{
		for(j=1;j<=v;j++)
		{
			if(red_mat[i][j]!=999 && col[j]!=999)
				red_mat[i][j]-=col[j];
		}
	}
}

int rowReduction(int red_mat[][10],int row[],int v)
{
	int i,j;
	for(i=1;i<=v;i++)
		row[i]=999;
		
	for(i=1;i<=v;i++)
	{
		for(j=1;j<=v;j++)
		{
			if(red_mat[i][j]<row[i])
			{
				row[i]=red_mat[i][j];
			}
		}
	}
	
	for(i=1;i<=v;i++)
	{
		for(j=1;j<=v;j++)
		{
			if(red_mat[i][j]!=999 && row[i]!=999)
			{
				red_mat[i][j]-=row[i];
			}
		}
	}
}

int  reduce_matrix(int red_mat[][10])
{
	
	int cost =0;
	int i,j;
	int row[10],col[10];
	
	rowReduction(red_mat,row,v);
	colReduction(red_mat,col,v);
	
	
	for(i=1;i<=v;i++)
	{
		if(row[i]!=999)
			cost+=row[i];
		if(col[i]!=999)
			cost+=col[i];
	}
	return cost;
}

void set_infinity(int red_matrix[][10],int r,int j) //elements in r row and j column
{
	int i;
	for(i=1;i<=v;i++)
		red_matrix[r][i]=999;

	for(i=1;i<=v;i++)
		red_matrix[i][j]=999;
}

hterm expand(hterm node)
{
	int count,k,cost,temp_matrix[10][10],r,visited[10],i,j,m,red_matrix[10][10],cost1;
	while(1)
	{
		count=node.path[0];
		k=count+1;
		cost=node.cost;
		
		for(i=1;i<=v;i++)
		{
			for(j=1;j<=v;j++)
				temp_matrix[i][j]=node.matrix[i][j];
				
		}
		
		r=node.path[count];
		for(i=1;i<=v;i++)
			visited[i]=0;
		for(i=1;i<=count;i++)
			visited[node.path[i]]=1;
		
		for(j=2;j<=v;j++)
		{
			if(!visited[j])
			{
				printf("%d\n",j);
				for(i=1;i<=v;i++)
				{
					for(m=1;m<=v;m++)
							red_matrix[i][m]=temp_matrix[i][m];
				
				}
				
				set_infinity(red_matrix,r,j);
				red_matrix[j][1]=999; 
				
				cost1=reduce_matrix(red_matrix);
				node.cost=cost+cost1+temp_matrix[r][j];
				
				node.path[0] = k; 
				node.path[k] = j;
				
				for (i=1;i<=v;i++)
				{
					for(m=1;m<=v;m++)
					{
						node.matrix[i][m]=red_matrix[i][m];
					}
		
				}
				output(node.matrix);
				printf("cost %d\n",node.cost);
				insert(node);
			}
		}
			
		if(k==v) break;
		node=delete();
	}
	return node;
}

int main()
{
	hterm node;
	int red_mat[10][10],graph[10][10];
	int cost,i,j,r,c;


	printf("Enter the no of cities\n");
	scanf("%d",&v);
	r=c=v;										
	printf("Enter the matrix values\n");
	for (i=1;i<=v;i++)
	{
		printf("Enter row elem\n");
		for(j=1;j<=v;j++)
		{
			scanf("%d",&graph[i][j]);
		}
	}
	//output(graph);
	for (i=1;i<=v;i++)
	{
		for(j=1;j<=v;j++)
		{
			red_mat[i][j]=graph[i][j];
		}
		
	}
	//output(red_mat);
	//printf("reducing matrix\n");
	cost=reduce_matrix(red_mat);
	
	node.cost=cost;
	node.path[0]=1;
	node.path[1]=1;
	
	for (i=1;i<=v;i++)
	{
		for(j=1;j<=v;j++)
		{
			node.matrix[i][j]=red_mat[i][j];
		}
		
	}
	//output(node.matrix);
	node=expand(node);
	//printf("%d\n",list[1].cost);		
	if(node.cost<=list[1].cost)
	{
	}
	else
	{
		while(1)
		{
			if(heap_size==0)
				break;
			node=delete();
			node=expand(node);
			if(node.cost<list[1].cost) break;
		}
	}
	
	//printing output

	printf("Cost of the path is %d \n",node.cost);
	printf("Path : \n");
	for(i=1;i<=v;i++)
		printf(" %d ",node.path[i]); printf(" 1 ");
	printf("\n");
	return 0;
}
