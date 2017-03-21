#include<stdio.h>

 
int main()
{
	int choice=0;
	int i,j,k,n,sum;
			
			printf("Enter the order of matrix: ");
			scanf("%d",&n);
			float a[n+1][n+1],x[n+1];
				for(k=1;k<=n;k++)
				{
					for(j=1;j<=n+1;j++)
					{
						printf("a[%d][%d]:",k,j);
						scanf("%f",&a[k][j]);
					}
				}
			for(k=1;k<=n-1;k++)
				{
					for(i=k+1;i<=n;i++)
					{
						for(j=k+1;j<=n+1;j++)
						{
							a[i][j] = a[i][j] -a[i][k] /a[k][k] * a[k][j];
						}
					}
				}
			x[n] = a[n][n+1]/a[n][n];
			for(k=n-1;k>=1;k--)
				{
				sum=0;
					for(j=k+1;j<=n;j++)
					{
						sum = sum + a[k][j] * x[j];
					}
				 x[k] = 1/a[k][k] * (a[k][n+1]-sum);
				}
			for (j= 1; j<= n; j++)
				{
				    printf("x[%d]: %f\n",j,x[j] );
				    
				}
	while(choice!=4)
	{
		printf(" 1.Degenerate and Non-degenerate Basic Solution\n 2.Basic Feasible Solution\n 3.Extreme Points\n 4.Exit\n");
		printf("Enter a choice:");
		scanf("%d",&choice);
		switch(choice)
		{ 
			case 1:
				
			break;
			case 2: 
			
			break;
			case 3: 
			
			break;
			case 4:
			printf("You chose Exit\n");
			break;
			default :
			printf("invalid option\n");
			break;		
			}
	}

}
