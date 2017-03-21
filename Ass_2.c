#include <stdio.h>
#include <math.h>
#include <stdlib.h>
int selected[100],n,m,counter=0;
float obj[100];
float  s[100][2];
float a[100][100],b[100],sum,err,prev;
float *gauss_seidel()
{
	int i,j,flag=0;
	float *sol,sum,prev; sol=(float *)malloc(m*sizeof(float));
	for(i=0;i<m;i++)
		sol[i]=0;
	while(1) 
	{
		for(i=0;i<m;i++)
		{
			sum=0;
			// if(selected[i]==0)
			// 	continue;
			for(j=0;j<n;j++)
			{
				if(j==i)
					continue;
				if(selected[j]==1)
					sum+=sol[j]*a[i][j];
			}
			prev=sol[i];
			sol[i]=(b[i]-sum)/a[i][i]; //printf("\t %d %f %f\n",i,prev,sol[i]);
			if(fabs((sol[i]-prev)/prev)<err)
				flag=1;
		}
		if(flag)
			break;
	}
	return sol;
}
void basic_sol()
{
	int j;
	printf("\n");
	printf("Zero variables are ");
			for(j=0;j<n;j++)
				if(selected[j]==0)
					printf("X%d ",j+1);
	printf("\n");
	for(j=0;j<m;j++)
			printf("X%d -> %f\n",(int)s[j][0],s[j][1]);
	printf("\n");

}
void bfs()
{
	int j;
	for(j=0;j<m;j++)
		if(s[j][1]<0)
			return;
	printf("\n");
	printf("Zero variables are ");
		for(j=0;j<n;j++)
			if(selected[j]==0)
				printf("X%d ",j+1);
	printf("\n");
	for(j=0;j<m;j++)
			printf("X%d -> %f\n",(int)s[j][0],s[j][1]);
	printf("\n");

}
void deg()
{
	int j,flag=0;
	for(j=0;j<m;j++)
		if(s[j][1]==0)
		{
			flag=1;
			break;
		}
	if(flag)
	{

		printf("\n");
		printf("Zero variables are ");
			for(j=0;j<n;j++)
				if(selected[j]==0)
					printf("X%d ",j+1);
		printf("\n");
		for(j=0;j<m;j++)
			printf("X%d -> %f\n",(int)s[j][0],s[j][1]);
		printf("\n");
	}

}
void non_deg()
{
	int j;
	for(j=0;j<m;j++)
		if(s[j][1]<=0)
			return;
	printf("\n");
	printf("Zero variables are ");
		for(j=0;j<n;j++)
			if(selected[j]==0)
				printf("X%d ",j+1);
	printf("\n");
		for(j=0;j<m;j++)
			printf("X%d -> %f\n",(int)s[j][0],s[j][1]);
	printf("\n");

}
void print_comb(int arr[],int n,int r,int index,int data[],int i,int option)
{
	if(index==r)
	{
		int j;
		
		for(j=0;j<n;j++)
			selected[j]=0;
		for(j=0;j<r;j++)
		{
			selected[data[j]]=1;
			s[j][0]=data[j]+1;
		}
		//printf("\n");
		float *sol=gauss_seidel();
		for(j=0;j<m;j++)
			s[j][1]=sol[j];
		if(option==1)
			basic_sol();
		else if(option==2)
			bfs();
		else if(option==3)
			deg();
		else
			non_deg();
		//printf("Basic solution  is \n");
		return;
	}
	if(i>=n)
		return;

	data[index]=arr[i];
	print_comb(arr,n,r,index+1,data,i+1,option);
	print_comb(arr,n,r,index,data,i+1,option);
}

int main()
{
	int i,j,flag=0,arr[100],data[100];
	
	printf("Give the number of variables \n");
	scanf("%d",&n);
	printf("Give number of equations \n");
	scanf("%d",&m);
	printf("Enter the elements of matrix row-wise\n");
	for(i=0;i<m;i++)
		{for(j=0;j<n;j++){printf("a[%d][%d]:",i,j);
			scanf("%f",&a[i][j]);}}
	printf("Enter elements of B\n");
	for(i=0;i<m;i++)
		{printf("b[%d]:",i);
scanf("%f",&b[i]);}
	printf("Enter the stopping criteria\n");
	scanf("%f",&err);
	printf("The solutions are \n");
	for(i=0;i<n;i++)
		{arr[i]=i;}
	/*printf("Enter objective function\n");
	for(i=0;i<n;i++)
		{scanf("%f",&obj[i]); }*/
	int option;
	printf("What do you want??\n1-> Basic Solution\n");
	printf("2->Basic Feasible Solution\n3->Degenerate Basic Feasible Solution\n");
	printf("4->Non Degenerate Basic Feasible Solution\n");
	scanf("%d",&option);
	print_comb(arr,n,m,0,data,0,option);
	
	return 0;
}

/*
Basic Feasible Solution	satisfy and greater than  or equal to 0
Degenerate 				anyone 0
Non Degenerate			satisfy and greater than 0

*/


