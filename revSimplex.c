#include<stdio.h>
#include<curses.h>
#include<math.h>
#include<stdlib.h>
 
int bMATRIX[10][10];
void DETINV(int mSIZE, double **MATB);
void arg(int *a,int *b,int *n,int x,int y);
int det(int *p,int *n);
double **MATa;
double **MATB;
double *MATb;
double *MATc;
double *MATcBT;
 
int main()
{
  int nSIZE = 1;
  int mSIZE = 1;
  int n1SIZE = 1;
 
  int i, j;
 
      printf("REVERSE SIMPLEX METHOD \n\nEnter size [n] : ");
      scanf("%d", &nSIZE);
      printf("Enter size [m] : ");
      scanf("%d", &mSIZE);
 
      n1SIZE = nSIZE-mSIZE;
      while ( n1SIZE <= 0 )
      {
        printf("\n!!INVALID MATRIX SIZE!!\nPlease reenter size [n] : ");
        scanf("%d", &nSIZE);
        printf("Please reenter size [m] : ");
        scanf("%d", &mSIZE);
        n1SIZE = nSIZE-mSIZE;
      }
 
////////////////////////////////////////////
      MATa = malloc(mSIZE*sizeof*MATa);
 
      for(i=0;i<mSIZE;++i)
      {
          MATa[i]=malloc(nSIZE*sizeof**MATa);
      }
////////////////////////////////////////////
      MATB = malloc(mSIZE*sizeof*MATB);
 
      for(i=0;i<mSIZE;++i)
      {
          MATB[i]=malloc(mSIZE*sizeof**MATB);
      }
 
////////////////////////////////////////////   
      MATc = malloc(nSIZE*sizeof*MATc);
////////////////////////////////////////////   
      MATb = malloc(mSIZE*sizeof*MATb);
////////////////////////////////////////////
 
////////////////////////////////////////////
      printf("Please enter values of\n");
      for(i=0;i<mSIZE;i++)
      {
        for(j=0;j<nSIZE;j++)
          {
            printf("a%d,%d: ", i+1, j+1);
            scanf( "%lf", &MATa[i][j]);
          }
      }
 
      printf("Please enter values of\n");
      for(i=0;i<mSIZE;i++)
      {
        printf("b%d,1: ", i+1);
        scanf( "%lf", &MATb[i]);
      }
      printf("Please enter the coefficients of x in Zequation\n");
      for(i=0;i<nSIZE;i++)
      {
        printf("x%d: ", i+1);
        scanf( "%lf", &MATc[i]);
      }
///////////////////////////////////////
      printf("This is called matrix 'A'=\n");
      for(i=0;i<mSIZE;i++)
        {
            for(j=0;j<nSIZE;j++)
                {
                    printf("%1.0lf  ", MATa[i][j]);
                }
            printf("\n");
        }
      printf("\n");
      printf("This is called matrix 'b'=\n");
      for(i=0;i<mSIZE;i++)
        {
            printf("%1.0lf", MATb[i]);
            printf("\n");
        }
          printf("This is called matrix 'c'=\n");
      for(i=0;i<nSIZE;i++)
        {
            printf("%1.0lf  ", MATc[i]);
             
        }
////////////////////////////////////////
 
////////////////////////////////////////
      printf("\nThis gives matrix 'B':\n");
      for(i=0;i<mSIZE;i++)
      {
        for(j=n1SIZE;j<nSIZE;j++)
        {
            MATB[i][j] = MATa[i][j];
            printf("%1.0lf  ", MATB[i][j]);
        }
        printf("\n");
      }
      printf("\n");
//////////////////////////////////////////   
      printf("\nThis gives matrix 'K':\n");
      for(i=0;i<mSIZE;i++)
      {
        for(j=0;j<n1SIZE;j++)
        {
            printf("%1.0lf  ", MATa[i][j]);
        }
        printf("\n");
      }
      printf("\n");
///////////////////////////////////////
 
///////////////////////////////////////
 
printf("\nNow to caculate matrix 'cB'/L=\n");
      for(i=0;i<n1SIZE;i++)
        {
            printf("%1.0lf  ", MATc[i]);
             
        }
printf("\nTransposing matrix 'cB' gives 'cBT'=\n");
      MATcBT = malloc(n1SIZE*sizeof*MATcBT);
      for(i=0;i<n1SIZE;i++)
        {
            MATcBT[i] = MATc[i];
            printf("%1.0lf\n", MATcBT[i]);
        }
 
printf("\n\n\n!!ALL WORKING TO HERE!!\n\n\n");
DETINV(mSIZE, MATB);//this function call doesnt work :(
 
 
    //  for(i=0;i<mSIZE;++i) free(MATa[i]);
     // free(MATa);
    }
int powi(int a, int b)
{
int i=1,mul=1;
for(i=1;i<=b;i++)
{
mul=mul*a;
}
return mul;
}
    
void DETINV(int mSIZE, double **MATB)
{
int a[10][10],b[10][10],c[10][10];
int n,n1,i,j,m,d,q;
n = mSIZE;
n1= mSIZE;
      for(i=1;i<(mSIZE+1);i++)
      {
        for(j=1;j<(mSIZE+1);j++)
        {
            q = (double)MATB[i][j];
 
        }
        printf("\n");
      }
 
       printf("\nsetting up data for the functions\n");
      for(i=1;i<(mSIZE+1);i++)
      {
        for(j=1;j<(mSIZE+1);j++)
        {
            printf("[%d] [%d] ", i, j);
            printf("%d ", a[i][j]);
            a[i][j] = q;
 
        }
        printf("\n");
      }
 
if(n==2)
{
c[0][0]=a[1][1];
c[1][1]=a[0][0];
c[0][1]=-a[0][1];
c[1][0]=-a[1][0];
d=a[0][0]*a[1][1]-a[0][1]*a[1][0];
printf("Determinant is:%d\n",d);
if(d==0)
{
getch();
exit(d-'0');
}
 
for(i=0;i<n;i++)
{
printf("\n");
for(j=0;j<n;j++)
printf(" %f",c[i][j]/(float)d);
 
}
}
else
{
m=n;
for(i=0;i<m;i++)
{
for(j=0;j<m;j++)
{
n=m;
arg(&a[0][0],&b[0][0],&n,i,j);
c[j][i]=powi(-1,(i+j))*det(&b[0][0],&n);
}
}
n=m;
d=det(&a[0][0],&n);
printf("Determinant is :%d\n",d);
if(d==0)
{
printf("INVERSE DOES NOT EXIST");
getch();
exit(d-'0');
}
printf("Inverting matrix 'B' gives 'B-1'=\n");
for(i=0;i<m;i++)
{
printf("\n");
for(j=0;j<m;j++)
printf(" %f",c[i][j]/(float)d);
}
}    getch();
}
 
void arg(int *a,int *b,int *n,int x,int y)
{
int k,l,i,j;
for(i=0,k=0;i<*n;i++,k++)
{
for(j=0,l=0;j<*n;j++,l++)
{
if(i==x)
i++;
if(j==y)
j++;
*(b+10*k+l)=*(a+10*i+j);
 
}
}
*n=*n-1;
}
 
int det(int *p,int *n)
{
int d[10][10],i,j,m,sum=0;
m=*n;
if(*n==2)
return(*p**(p+11)-*(p+1)**(p+10));
for(i=0,j=0;j<m;j++)
{
*n=m;
arg(p,&d[0][0],n,i,j);
sum=sum+*(p+10*i+j)*powi(-1,(i+j))*det(&d[0][0],n);
}
 
return(sum);
}
