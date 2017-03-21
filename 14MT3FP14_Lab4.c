#include <stdio.h>
#include <curses.h>
#define INFINITY 999
#define N 3
#define M 6
void calctemp(float *temp,float a[N][M],float c[M],int basic[N])/* Calculates Zj-Cj */
{
  int i,j;
  for(i=0;i<M;i++)
  {
    temp[i]=0;
    for(j=0;j<N;j++)
      temp[i]=temp[i]+c[basic[j]]*a[j][i];
    temp[i]=temp[i]-c[i];
  }
}
void minimum(float *arr,int *arrminpos, int n)
/* Calculates the minimum valued position among the array arr having n elements. */
{
  int i;
  float arrmin;
  arrmin=arr[0];
  *arrminpos=0;
  for(i=0;i<n;i++)
    if(arr[i]<arrmin)
    {
      arrmin=arr[i];
      *arrminpos=i;
    }
    printf("\n%d\n",*arrminpos);
}
void display (float c[N],float b[N],float a[N][M],int basic[N])/* Display the table */
{
  int i,j;
  printf("\t\tc[j]\t");
  printf("%g\t%g\t%g\t%g\t%g\t%g\n",c[0],c[1],c[2],c[3],c[4],c[5]);
  printf("\nc[B]\tB\tb\ta1\ta2\ta3\ta4\ta5\ta6\n");
  for(i=0;i<N;i++)
  {
    printf("\n%.4g\tX%d\t%.4g\t",c[basic[i]],basic[i]+1,b[i]);
    for(j=0;j<M;j++)
      printf("%.4g\t",a[i][j]);
    printf("\n");
  }
}

void main()
{
  float c[M]={5,4,3,0,0,0};
  /* Stores co-efficient of the objective function Max(z) */
  float a[N][M]={
    {2,3,1,1,0,0},
    {4,1,2,0,1,0},
    {3,4,2,0,0,1}
  };
  /* Stores the co-efficent of the constraints */
  float b[N]={5,11,8};
  /* Stores the values on RHS of constraints */
  float temp[M]={0,0,0,0,0,0};
  /* Stores the values of Zj-Cj*/
  int tempminpos;      /* Stores the minimum valued position
              of {Zj-Cj} i.e. coming in variable */
  float minrat[N];   /* Stores the value of the ratio b[i]/a[i][j] */
  int minratminpos;  /* Stores the minimum valued position of
              b[i]/a[i][j] i.e. going out variable */
  float key;          /* Stores the key element */
  int gooutcol;        /* Stores the column number which goes out */
  float z;          /* Stores the value of the objective function */
  float x[M];        /* Stores the value of the variables */
  int i,j;        /* Loop variables */
  int basic[N];        /* Stores the basic variable */
  int nonbasic[N];    /* Stores the non-basic variable */
  int flag=0;      /* Terminating variable */
  //clrscr();
  /*** Initializing basic variables to 3,4,5 i.e. x4,x5,x6 ***/
  for(i=0;i<N;i++)
  {
    basic[i]=(i+N);
    nonbasic[i]=i;
  } 
  printf("\nMax z =");
  for(i=0;i<N;i++)
  {
   printf("c%d",i+1);
   if(i!=N-1)
  {printf("+");}
  }
  printf("\na11x1 + a12x2 + a13x3 <= b1\n");
  printf("\na21x1 + a22x2 + a23x3 <= b2\n");
  printf("\na31x1 + a31x2 + a32x3 <= b3\n");
  printf("\nEnter values of ci's\n");
  /*** Inputing requisite amount of data ***/
  for(i=0;i<N;i++)
  {
    printf("\nEnter c[%d]\t",i+1);
    scanf("%f",&c[i]);
  }
  printf("\nEnter values of ai's\n");
  for(i=0;i<N;i++)
  {
    for(j=0;j<N;j++)
    {
      printf("\nEnter a[%d][%d]\t",i+1,j+1);
      scanf("%f",&a[i][j]);
    }
  }
  printf("\nEnter values of bi's\n");
  for(i=0;i<N;i++)
  {
    printf("\nEnter b[%d]\t",i+1);
    scanf("%f",&b[i]);
  }
  /*** Calculation for actual table ***/
  while(flag==0)
  {
    z=0;
    calctemp(temp,a,c,basic);
    printf("\n");

    /*** Determining the incoming column ***/

    minimum(temp,&tempminpos,M);
    display(c,b,a,basic);
    printf("\nZj-Cj\t\t\t");
    for(i=0;i<M;i++)
      printf("%.4g\t",temp[i]);
    printf("\n\n");
    for(i=0;i<N;i++)
    {
      x[basic[i]]=b[i];
      x[nonbasic[i]]=0;
      printf("x[%d]=%g\n",basic[i]+1,b[i]);
    }
    for(i=0;i<N;i++)
      z=z+c[i]*x[i];
    printf("Max(z) = %g",z);

    /*** Determining the outgoing column ***/

    for(i=0;i<N;i++)
    {
      if(a[i][tempminpos]==0)
      {
        minrat[i]=INFINITY;
        continue;
      }
      if(a[i][tempminpos]<0)
      {
        minrat[i]=INFINITY;
        continue;
      }
      minrat[i]=b[i]/a[i][tempminpos];
    }
    minimum(minrat,&minratminpos,N);
    for(i=0;i<N;i++)
      if(minratminpos==i)
        gooutcol=basic[i];
    printf("\nChanging = X%d\t",tempminpos+1);
    printf("with = X%d\n",gooutcol+1);

    basic[minratminpos]=tempminpos;
    nonbasic[tempminpos]=gooutcol;

    key=a[minratminpos][tempminpos];
    b[minratminpos]=b[minratminpos]/key;
    for(i=0;i<M;i++)
      a[minratminpos][i]=a[minratminpos][i]/key;
    for(i=0;i<N;i++)
    {
      if(minratminpos==i)
        continue;
      key=a[i][tempminpos];
      for(j=0;j<M;j++)
      {
        a[i][j]=a[i][j]-a[minratminpos][j]*key;
      }
      b[i]=b[i]-b[minratminpos]*key;
    }
    getch();

    /*** Terminating condition ***/

    for(i=0;i<M;i++)
    {
      flag=1;
      if(temp[i]<0)
      {
        flag=0;
        break;
      }
    }
  }
  printf("\nPress any key to exit...\n");
  getch();
}
