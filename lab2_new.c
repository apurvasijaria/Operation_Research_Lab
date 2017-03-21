#include<stdio.h>
#include<conio.h>

//function make to make possible combinations of variables to set certain variables
 zero to generate possible solutions
while applying gauss elimination//
int make(int i,int n, int m, int count, int k, int p[],int l,int a[][n],int w[][n],int c)
{
  //i= for main index, n= total number of variables, m=total number of equations,
    count=to keep track of number of recursions
    k=to track the step of next index element for a particular index 
    i.e. for x0x1 k=1 and for x0x2 k=2, p[]=to store the index
    l=for index tracking in index array, a[][n]=original martix of coeffivcients,
    w[][n]=to store all solutions, c= to track w[][n] //
    int j,h;
    int v[m][m]; //to store the new array on which gauss elimination will be applied//
    for(j=i;j<n;j++)
    {
        if(count<n-m)
        {
            count++;
            p[l]=j;
            l++;
            for(h=0;h<m;h++)
            {
              v[h][j]=a[h][j]; //restoring the variables again in v matrix to pass to gauss elimination//
            }
            if(count<n-m)
            {
                make(j+k,n,m,count,k,l,a,c);//calling the function again to append an element in the index//
                k++;
            }

        }
        else
        {
            gausselim(v,w,c); /*passing the matrix v as argument once a new index is made up*/
            c++;
            break; /*breaking out from loop*/
        }
    }
}

int guasselim(int a[][m],int w[][n],int c) /*function for gauss elimination*/
{
    int choice=0;
	int i,j,k,sum;
			for(k=0;k<m-1;k++)
				{
					for(i=k;i<=m;i++)
					{
						for(j=k+1;j<=m+1;j++)
						{
							a[i][j] = a[i][j] -a[i][k] /a[k][k] * a[k][j];
						}
					}
				}
			x[m] = a[m][m+1]/a[m][m];
			for(k=m;k>1;k--)
				{
				sum=0;
					for(j=k;j<m;j++)
					{
						sum = sum + a[k][j] * x[j];
					}
				 x[k] = 1/a[k][k] * (a[k][m+1]-sum);
				}
			for (j= 0; j< m; j++)
				{
				    printf("x[%d]: %f\n",j,x[j] );
                    w[c][j]=x[j]; /*storing the solutoins of different matrix here*/
				}
}

int main()
{
    int p,i,n,m,c,count,k;
    i=0;
    k=1;
    c=1;
    count=0;
    printf("Enter the order of matrix: ");
	scanf("%d",&n);
    printf("Enter the number of equations: ");
	scanf("%d",&m);
	float a[n][n],x[n];
	int w[n][n];
		for(k=0;k<n;k++)
			{
			for(j=0;j<n+1;j++)
				{
					printf("a[%d][%d]:",k,j);
					scanf("%f",&a[k][j]);
				}
			}
   for(p=0;p<n-1;p++)
    {
     make(i,n,m,count,k,a,w,c);
     i++;
     count=0; //redifning count//
     k=1;//redifing k for new index generation with 1 as initial step//
    }
	while(choice!=4)
	{
		printf(" 1.Degenerate and Non-degenerate Basic Solution\n 2.Basic Feasible Solution\n 3.Extreme Points\n 4.Exit\n");
		printf("Enter a choice:");
		scanf("%d",&choice);
		switch(choice)
		{
			case 1:
            printf("\nDegenerate and Non-degenerate Basic Solution\n");
            for(j=0;j<n;j++)
				{
				    for(c=0;c<n;c++)
					{
					    printf("%d",w[j][c]);
					}

				}
			}
			break;
			case 2:
            printf("\nDegenerate and Non-degenerate Basic Feasible Solution\n");
            for(j=0;j<n;j++)
				{
				    for(c=0;c<n;c++)
					{
					    if(w[j][c]>0);
					    {
					        print[j]=1;
					    }
					    else
                        {
                            print[j]=0; //if any element is negetive this will get 0 as a value//
                        }
					}

				}
           for(j=0;j<n;j++)
				{
				    if(print[j]==1)
                    {
                        for(c=0;c<n;c++)
                        {
                            printf("%d",w[j][c]); //for printing only corsfficients with positive element//
                        }
                    }
				}

			break;
			case 3:
            		printf("\nExtreme points\n") //for choosing option 3 //

			break;
			case 4:
			printf("You chose Exit\n"); //choosing exit//
			break;
			default :
			printf("invalid option\n"); //default case//
			break;
			}
	}

}
