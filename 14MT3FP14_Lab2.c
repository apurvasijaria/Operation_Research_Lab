#include<stdio.h>
#include<math.h>
#include<stdlib.h>

int count=0;

struct node{
	float* data;
	struct node *next;
	int Is_BFS;

};

struct node *Head=NULL;

void print_it(int n){
	struct node *pntr=Head;
	int j=0,i;
	printf("Solutions are:- \n");
	while(pntr!=NULL)
	{
		printf("Solution no.(%d)= ",j++);
		for(i=0;i<n;i++)
			printf("x(%d) = %.2f ",i,pntr->data[i]);
		printf("\n\n");
		pntr = pntr->next;
	}
}

void printBFS(int n){
	struct node *pntr=Head;
	int Count_BFS=0;
	int i,flag;
	printf("-------------------------------------------");
	printf("The Basic Feasible solutions are: \n\n");
	while(pntr!=NULL)
	{
		if(pntr->Is_BFS==1){
			printf("Soln%d= ",Count_BFS);
			for(i=0;i<n;i++)printf("x(%d)=%.2f ",i,pntr->data[i]);
			printf("\n\n");
			Count_BFS++;
			

		}
		pntr = pntr->next;
	}
	if(Count_BFS==0)
		printf("\n\nThere exist no BFS\n");
}

void Print_NDBS(int n,int m){

	int Count_NDBS=0;
	struct node *pntr=Head;
	int j=0,i,flag;
	int count=0;
	printf("-------------------------------------------");
	printf("The Non Degenrate Basic Feasible solutions(BFS) are: \n\n");
	while(pntr!=NULL)
	{
		
		
		if(pntr->Is_BFS==0){
	        pntr = pntr->next; continue;}
		else
		{
			count=0;
			for(i=0;i<n;i++){
			if(pntr->data[i]==0)count++;
							}
			if(count==n-m)
			{
				//This means no. of 0's in this soln. is =(n-m) i.e. rest m's are (+)ve
				printf("Soln(%d)= ", Count_NDBS);

				for(i=0;i<n;i++)printf("x(%d)=%.2f ",i,pntr->data[i]);
				printf("\n\n");
				Count_NDBS++;
			}
			pntr = pntr->next;
		}
	}
	if(Count_NDBS==0)
		{printf("There exists no NDBS\n");
		printf("-------------------------------------------");}
	
}

void Print_DBS(int n,int m){

	int Count_DBS=0,j=0,i,flag,count=0;
	struct node *pntr=Head;
	printf("-------------------------------------------");
	printf("Degenerate Basic Feasible solutions(BFS) are: \n\n");
	while(pntr!=NULL)
	{
		if(pntr->Is_BFS==0){ 
			pntr = pntr->next; continue;}
		else
		{
			
			count=0;
			for(i=0;i<n;i++){
				if(pntr->data[i]==0)count++;
							}
			if(count > n-m)
			{	
				printf("Soln(%d)= ",Count_DBS);
				for(i=0;i<n;i++)
					printf("x(%d)=%.2f ",i,pntr->data[i]);
				printf("\n\n");
				Count_DBS++;
			}
			
			pntr = pntr->next;
		}

	}
	if(Count_DBS==0)
		printf("There exist no DBS  \n\n");
		printf("-------------------------------------------");
}





void Swap_Row(float** mat, int row1, int row2, int m )
{ int i;
    for ( i=0; i<=m ; i++)
    {
        int temp = mat[row1][i];
        mat[row1][i] = mat[row2][i];
        mat[row2][i] = temp;
    }
}

void insertFirst(float *temp,int n,int flagBFS){
	//Here,n is the number of variables
	
	struct node *newnode=(struct node*)malloc(sizeof(struct node));
	if(newnode==NULL)printf("\nError1\n");

	newnode->data=(float*)malloc(n*sizeof(float));
	if(newnode->data==NULL)printf("\nError2\n");
	int i;
	for(i=0;i<n;i++)newnode->data[i]=temp[i];
	newnode->Is_BFS=flagBFS;
	
	newnode->next=Head;
	Head=newnode;

}


void gaussElimination(float** a,float* b,int m,int* subsetarr,int n){
	
	int j,i,k,d;
	float temp;
	static int solcount=0;

	printf("\nSubset Passed is::");
	for(i=0;i<m;i++)
		printf(" %d",subsetarr[i]);
	printf("\n");
	
	float x[m],sum,er,anew[m][m],*upntr[m];
	int key;
	for (i=0; i<m; i++)
         upntr[i] = (float *)malloc((m+1) * sizeof(float));
	 
	//Code for initialisation of anew	
	for(i=0;i<m;i++){
		
		for(j=0;j<m+1;j++){
			anew[i][j]=a[i][subsetarr[j]];
			if(j==m)
				upntr[i][j]=b[i];
			else upntr[i][j]=anew[i][j];
						  }
						  
	}
	
	int t=0;
	int row;

	//code for uppertraingular matrix
	for(j=0;j<m;j++){
		
		if(upntr[j][j]==0)
		{
			for(row=j+1;row<m;row++)
			{
				if(upntr[row][j]!=0)
				{
					Swap_Row(upntr,j,row,m);
					break;
					
				}
			}


		}

		for(i=j+1;i<m;i++){
			
			temp=upntr[i][j];
			for(k=0;k<m+1;k++){
				upntr[i][k]= upntr[i][k] - (  ((upntr[j][k]) *(temp) )/ upntr[j][j] ) ;

			}
		}

	}

	//Checking whether unique solution exist
	int isConsistnt=1;
	
	if(upntr[m-1][m-1]==0){
		printf(" \n No Unique Solution \n\n");	
	}

	//Code for Variables
	else{
	//Considering rank(A) == rank(A|b) == m
	float sum1;
	x[m-1]=upntr[m-1][m]/upntr[m-1][m-1];
	for(j=m-2;j>=0;j--){
		sum1=0;
		for(k=j+1;k<=m-1;k++)
			sum1=sum1+upntr[j][k]*x[k];
		x[j]=(upntr[j][m]-sum1)/upntr[j][j];	
		}
		solcount++;
	float xfinalSoln[n];
	
	for(i=0,j=0;i<n;i++){

		if(i==subsetarr[j]){
			xfinalSoln[i]=x[j];

			 j++;
		}
		else
			xfinalSoln[i]=0;

	}
	int flagBFS=1;
	for(i=0;i<n;i++)
			{
				if(xfinalSoln[i]<0)
					{flagBFS=0;break;}
			}
	insertFirst(xfinalSoln,n,flagBFS);	

	printf("\nSolution Number(%d)= \n", solcount);

	for(i=0;i<n;i++){
		printf("x(%d)=%.3f ",i,xfinalSoln[i]);
	}
	
	
	printf("\n\n")	;


	}
}

void subset(int* arr,int index,int m,int n,float** a, float* b)
//This will return an array of size n consisiting of 1's and 0's with (n-m) 0's 
{

	int i,j;
	if(count == m){
		int* subsetarr;
		subsetarr=(int*)malloc(m*sizeof(int));
		for(i=0,j=0;i<n;i++){
			if(arr[i]==1)subsetarr[j++]=i;
		}
		gaussElimination(a,b,m,subsetarr,n);

		return;
	}

	for(i=index;i<n;i++){

	 	arr[i]=1;
	 	count++;
	 	subset(arr,i+1,m,n,a,b);
	 	arr[i]=0;
	 	count--;
	}

	return ;	
	
}

int main()
{
	int i,j,n,m;
	printf("Give no of variables=");
	scanf("%d",&n);
	printf("Give no of equations=");
	scanf("%d",&m);
	float *a[m],*b;
	
	for (i=0; i<m; i++)
         a[i] = (float *)malloc(n * sizeof(float));
    b=(float*)malloc(m*sizeof(float)); 

	for(i=0;i<m;i++){
		for(j=0;j<n;j++){
			printf("a[%d][%d]:",i,j);
			scanf("%f",&a[i][j]);
			}
		}

	for(i=0;i<m;i++)
		{printf("b[%d]:",i);
		scanf("%f",&b[i]);}
	int *arr1;
	arr1=(int*)malloc(n*sizeof(int));
	
	subset(arr1,0,m,n,a,b);

	int input;
	int x=1;
	while(x){
	printf("-------------------------------------------");
	printf("\nEnter Choice Number\n\n");
	printf("1. Print all solutions\n");
	printf("2. Print all DBS (The Degenrate Basic solutions)\n");
	printf("3. Print all NDBS (The Non Degenrate Basic Feasible solutions)\n");
	printf("4. Print all BFS (The Basic Feasible solutions)\n");
	printf("5. Exit \n\n");
	scanf("%d",&input);

	switch(input){
		case 1:
			print_it(n);
			break;
		case 2:
			Print_DBS(n,m);
			break;
		case 3:
			Print_NDBS(n,m);
			break;
		case 4:
			printBFS(n);
			break;
		case 5:
			x=0;break;

		default:
			printf("Invalid input\n");
			printf("-------------------------------------------");

	}
	
	}
	
}



