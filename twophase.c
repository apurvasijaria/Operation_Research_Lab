#include<stdio.h>
#include<math.h>
#include<stdlib.h>

void twophasemethod(double** arr,int n,int mnew,int *basicindexarr,int choice,int iter){
	static int count=0;
	int col,row,i;

	if(iter==count){

		printf(" simplex matrix at %dth iteration\n",iter);
		printf("  ");
		for(i=0;i<n;i++)
		printf("x%d     ",i+1);
		printf("\n");
		for(row=0;row<=mnew ;row++){
			for(col=0;col<n+1;col++)printf("%.2f  ",arr[row][col]);
				printf("\n");
			}

		printf("\nBasic Variables \n");
		for(i=0;i<mnew;i++){
			if(basicindexarr[i]>=0){
				printf("x%d ,",basicindexarr[i]+1);
			}
		}

	}

	
	int ispostv=1;
	
	count++;

	double optimalsoln[n];
	for(i=0;i<n;i++)optimalsoln[i]=0;
	
	for(row=0;row<mnew;row++){
		if(arr[row][n]<0){ispostv=0; break;}
	}


	if(ispostv==1){
		printf("Feasible solution obtained, optimal is already met");
		if(arr[mnew][n]<0)
 		{
		printf("\nOptimal Value= %d\n",abs(arr[mnew][n]));
		}
		else{
		printf("\nOptimal Value= %f\n",arr[mnew][n]);
		}
		for(i=0;i<mnew;i++){
			if(basicindexarr[i]>=0){
				optimalsoln[ basicindexarr[i] ]=arr[i][n];
			}
		}

		for(i=0;i<n;i++)printf("x%d = %lf ",i+1,optimalsoln[i]);

		return;
	}
		

	else{

		int pivotr,pivotc;

		double min1=100000000;
		int mincolindex;
		double temp;
		double min2;//min2 is for  finding minimum among all rows of mincolindex
		int minrowindex=0;
		min1=arr[0][n];

		//finds column which has most negative element in last row
		for(row=1;row<mnew;row++){
		if(arr[row][n]<min1)
			{
				//printf("RRRR");
				min1=arr[row][n];
				minrowindex=row;
			}
		}
		int flag=-1;
		
		printf("minrowindex=%d\n",minrowindex);
		min2=10000000;

		//for(i=0;i<n;i++)printf("%lf ", arr[i])
		for(col=0;col<n;col++){

			if(arr[minrowindex][col]<0 )
			{
				//printf("^^$#$#");
				temp=arr[mnew][col]/arr[minrowindex][col];
				if(temp<0)temp=temp*(-1);
				if( temp < min2 ){
					min2=temp;
					mincolindex=col;
				}
				flag=1;
            }
            
		}
		if(flag==-1){
			printf("No Solution exists");
			return;
		} 
		printf("\nPivot elemnt index obtained %d %d\n",minrowindex,mincolindex);
		pivotr=minrowindex;
		pivotc=mincolindex;

		basicindexarr[pivotr]=pivotc;

		double pivotelmnt=arr[pivotr][pivotc];

		printf("N=%d  M=%d\n",n,mnew);
		for(row=0;row<=mnew ;row++){
			for(col=0;col<=n ;col++){
				//if(row==pivotr || col==pivotc){printf("violation");}
				if(row!=pivotr && col!=pivotc){
				//printf("Updating arr[%d][%d] ",row,col);
				arr[row][col]=(arr[row][col]*pivotelmnt-arr[row][pivotc]*arr[pivotr][col])/pivotelmnt;
				}
			}
		}

		for(row=0;row<=mnew;row++)arr[row][pivotc]	/=(-1*pivotelmnt);

		//changing row elmnts
		for(col=0;col<=n;col++)arr[pivotr][col]	/=(pivotelmnt);

		arr[pivotr][pivotc]=1/pivotelmnt;	
		printf("simplex matrix number: %d\n",count);
		for(row=0;row<=mnew;row++)
		{
		for(col=0;col<n+1;col++)printf("%.2f ",arr[row][col]);
			printf("\n");
		}	

	    twophasemethod(arr,n,mnew,basicindexarr,choice,iter);

		return;

	}
	return;
}




int main(){

	int n,m;
	int i,j;
	double* coeffobj;
	int m1,m2,m3;//m1 equality m2 less m3 greatrer

	printf("Enter n[number of variables]: ");
	scanf("%d",&n);//m denotes nmbr of constraint equations
printf("Enter m[number of inequalities]: ");
	scanf("%d",&m);
	coeffobj=(double*)malloc(n*sizeof(double));

	printf("Enter number of equality constraint: ");
	scanf("%d",&m1);

	printf("enter number of less inequality constraint: ");
	scanf("%d",&m2);

	printf("enter nmbr of greater inequality constraint: ");
	scanf("%d",&m3);

	double* constrntcoeff[m];

	for (i=0; i<m; i++)
         constrntcoeff[i] = (double *)malloc(n * sizeof(double));
    double b[m]; 
	//m is no of constraints equations
	printf("Enter coefficient of objective function: ");
	for(i=0;i<n;i++)scanf("%lf",&coeffobj[i]);

	printf("Enter constraints equations: \n");
	for(i=0;i<n;i++)printf("x%d ",i+1);
	printf("  b\n");

	if(m1!=0)
	{	
		printf("\nEnter equality constraints:\n");
		printf("m1=%d\n",m1);
		for(i=0;i<m1;i++)
		{

			for(j=0;j<n;j++)
				{
					scanf("%lf",&constrntcoeff[i][j]);
					//if(j==n)scanf("%lf",&b[i]);
				}
			scanf("%lf",&b[i]);
		}
	}
	if(m2!=0){	
		printf("\nEnter less than and equal to constraints:\n");
		printf("m2=%d\n",m2);
		for(i=0;i<m2;i++)
		{
			//printf("A\n");
			for(j=0;j<n;j++)
				{	//printf("B");

					scanf("%lf",&constrntcoeff[i+m1][j]);
					
				}
				scanf("%lf",&b[i+m1]);
		}
	}
	if(m3!=0)
	{	
		printf("\nEnter greater than and equal to constraints:\n");
		printf("m3=%d\n",m3);
		for(i=0;i<m3;i++)
		{

			for(j=0;j<n;j++)
				{
					scanf("%lf",&constrntcoeff[i+m1+m2][j]);
					//if(j==n)scanf("%lf",&b[i+m1+m2]);
				}
			scanf("%lf",&b[i+m1+m2]);
		}
	}

	int choice=4;
	int iter;
	
	switch(choice){
		case 1: iter=0;
				break;
		case 2: printf("Enter iteration number");
				scanf("%d",&iter);
				break;
		case 3: printf("Enter iteration number");
				scanf("%d",&iter);
				break;
		case 4: break;


	}

	
	
	double* simplxarr[2*m1 + m2 + m3 +1 ];
	int mnew= 2*m1 + m2 + m3;
	//no of rows always equal to number of constraint equation in rows we write only slack and artificial
	for (i=0; i<=mnew; i++)
         simplxarr[i] = (double *)malloc((n+1) * sizeof(double));//numbr of columsn 

    int k,row,col;
    for(i=0,k=i;i<m1;i++){

    	for(j=0;j<n;j++){

    		simplxarr[k][j]=constrntcoeff[i][j];
    		simplxarr[k+1][j]=(-1) * constrntcoeff[i][j];
		}
		simplxarr[k][n]=b[i];
		simplxarr[k+1][n]=(-1)*b[i];
		k=k+2;
    }

    for( ;i< m1+m2;i++){

    	for(j=0;j<n;j++){

    		simplxarr[k][j]=constrntcoeff[i][j];
    	}
    	simplxarr[k][n]=b[i];
    	k++;
    } 
    
    for(;i<m1+m2+m3;i++){
    	
    		for(j=0;j<n;j++){
    			simplxarr[k][j]=(-1)*constrntcoeff[i][j];
		}
		simplxarr[k][n]=(-1)*b[i];
		k++;

    }

    for(col=0;col<n;col++)simplxarr[mnew][col]=(-1)*coeffobj[col];

	simplxarr[mnew][n]=0;
	
	if(choice==1){

	printf("Initial simplex matrix: \n");
	printf("  ");
	for(i=0;i<n;i++)
	printf("x%d     ",i+1);
	printf("\n");
	for(row=0;row<=mnew ;row++){
		for(col=0;col<n+1;col++)printf("%.2f  ",simplxarr[row][col]);
			printf("\n");
		}
	return 0;	

    }

    int* basicindexarr;
    basicindexarr=(int*)malloc(m*sizeof(int));

    for (i=0; i<m; i++)
		basicindexarr[i]=-1;

    twophasemethod(simplxarr,n,mnew,basicindexarr,choice,iter);





 return 0;
    	
}
