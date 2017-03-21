#include <stdio.h>
int main()
{

    int n,i,j,key;
    printf("enter the order of matrix: ");
    scanf("%d%d",&n,&m);
    float a[n][n],b[n],er,x0[n],x[n];
    printf("Enter stopping criteria:");
    scanf("%f",&er);
    for(i=0;i<m;i++)
    {
        for (j= 0; j< n; j++)
        {
            printf("a[%d][%d]:",i,j );
            scanf("%f",&a[i][j]);
        }
    }
    
    for(i=0;i<n;i++)
    {
        printf("b[%d]:", i);
        scanf("%f",&b[i]);
    }
    for(i=0;i<n;i++)
    {
        x0[i]=0;
    }

	
    do
    {   float sum=0;
        key=0;
        for(i=0;i<n;i++)
        {
            sum=b[i];
            for(j=0;j<n;j++)
            {
                if(j!=i)
                {
                    sum=sum-a[i][j]*x0[j];
                }
            }
            x[i]=sum/a[i][i];
            if(((x[i]-x0[i]) / x[i] )>er)
            {
                key=1;
                x0[i]=x[i];
            }
        }
        

    }while(key==1);
for (j= 0; j< n; j++)
        {
            printf("x[%d]: %f",j,x[j] );
            
        }
}
