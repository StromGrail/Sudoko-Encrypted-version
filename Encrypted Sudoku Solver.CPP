//********** Header Files**********//

#include<conio.h>
#include<dos.h>
#include<graphics.h>
#include<iostream.h>
#include<math.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

//********** Value initialization of sudoku size **********//

#define N 9

//********** Declaration of common variables **********//

long int p,q,n,t,flag,e[100],d[100],temp[100],j,m[100],en[100],i,check;
char msg[100];

//********** Function Declaration **********//

void Initialise_Sudoku(int grid[N][N]);
int Find_Empty(int grid[N][N],int &i,int &j);
int Row_Ok(int grid[N][N],int row,int num);
int Column_Ok(int grid[N][N],int col,int num);
int Block_Ok(int grid[N][N],int b_row,int b_col,int num);
int Value_Ok(int grid[N][N],int row,int col,int num);
int Solve_Sudoku(int grid[N][N]);
void Print_Sudoku(int a[N][N]);
int check_prime(long int num);
long int value_of_d(long int x);
void value_of_e();
void encrypt();
void encrypt_sudoku();
void decrypt();
void decrypt_sudoku();
void graph();
void graphics();

//********** Function to enter the values of the unsolved sudoku **********//

void Initialise_Sudoku(int grid[N][N])
{
    for(int i=0;i<N;i++)
    {
        for(int j=0;j<N;j++)
            scanf("%d",&grid[i][j]);
    }
}

//********** Function to find whether the sudoku grid is full or empty **********//
//********** Returns 1 if sudoku has an empty cell or else 0 **********//
//********** Reference variables i and j are the corresponding values of the row and column of the empty cell **********//

int Find_Empty(int grid[N][N],int &i,int &j)
{
    for(i=0;i<N;i++)
    {
        for(j=0;j<N;j++)
            if(grid[i][j]==0)
                return 1;
    }
    return 0;
}

//********** Function to find whether the value "num" if present in a row or not **********//
//********** Returns 0 if the row has the "num" or else 1 *********//

int Row_Ok(int grid[N][N],int row,int num)
{
    for(int j=0;j<N;j++)
        if(grid[row][j]==num)
            return 0;
    return 1;
}

//********** Function to find whether the value "num" if present in a column or not **********//
//********** Returns 0 if the column has the "num" or else 1 **********//

int Column_Ok(int grid[N][N],int col,int num)
{
    for(int i=0;i<N;i++)
        if(grid[i][col]==num)
            return 0;
    return 1;
}

//********** Function to find whether the value "num" if present in a 3*3 block or not **********//
//********** Returns 0 if the block has the "num" or else 1 **********//

int Block_Ok(int grid[N][N],int b_row,int b_col,int num)
{
    for(int i=0;i<3;i++)
    {
        for(int j=0;j<3;j++)
            if(grid[b_row+i][b_col+j]==num)
                return 0;
    }
    return 1;
}

//********** Function to find whether the value "num" can be assigned to an empty cell or not **********//
//********** Returns 0 if row the value can be assigned to the empty cell or else 1**********//

int Value_Ok(int grid[N][N],int row,int col,int num)
{
    if(Row_Ok(grid,row,num)&&Column_Ok(grid,col,num)&&Block_Ok(grid,(row-row%3),(col-col%3),num))
        return 1;
    else return 0;
}

//********** Function to solve the sudoku **********//
//********** Returns 0 if the sudoku is solvable or else 0 **********//
//********** Checks for an empty cell - returns 1 if no empty cell is present(sudoku solved) or else 0**********//
//********** Checks if a value can be assigned to the empty cell**********//
//********** Recursively calls itself for every assigned value to an empty cell **********//
//********** Backtracks and assigns a different value to the empty cell if sudoku cannot be filled anymore **********//

int Solve_Sudoku(int grid[N][N])
{
    int row,col;
    if(!Find_Empty(grid,row,col))
        return 1;
    for(int num=1;num<=9;num++)
    {
        if(Value_Ok(grid,row,col,num))
        {
            grid[row][col]=num;
            if(Solve_Sudoku(grid))
                return 1;
            grid[row][col]=0;
        }
    }
    return 0;
}

//********** Function to print the sudoku grid **********//

void Print_Sudoku(int a[N][N])
{
    for(int i=0;i<N;i++)
    {
        for(int j=0;j<N;j++)
            printf("%d ",a[i][j]);
        printf("\n");
    }
}

int check_prime(long int num)
{
    long int k;
    j=sqrt(num);
    for(k=2;k<=j;k++)
    {
    if(num%k==0)
        return 0;
    }
    return 1;
}

long int value_of_d(long int x)
{
    long int k=1;
    while(1)
    {
        k=k+t;
        if(k%x==0)
            return (k/x);
    }
}

void value_of_e()
{
    int k;
    k=0;
    for(i=2;i<t;i++)
    {
        if(t%i==0)
            continue;
        check=check_prime(i);
        if(check==1&&i!=p&&i!=q)
        {
            e[k]=i;
            check=value_of_d(e[k]);
            if(check>0)
            {
                d[k]=check;
                k++;
            }
            if(k==99)
                break;
        }
    }
}

void encrypt()
{
    long int pt,ct,key=e[0],k,len;
    i=0;
    len=strlen(msg);
    while(i!=len)
    {
        pt=m[i];
        pt=pt-96;
        k=1;
        for(j=0;j<key;j++)
        {
            k=k*pt;
            k=k%n;
        }
        temp[i]=k;
        ct=k+96;
        en[i]=ct;
        i++;
    }
    en[i]=-1;
    printf("\n\nTHE ENCRYPTED MESSAGE IS : ");
    for(i=0;en[i]!=-1;i++)
        printf("%c",en[i]);
}

void encrypt_sudoku()
{
    long int pt,ct,key=e[0],k,len;
    i=0;
    len=81;
    while(i!=len)
    {
        pt=m[i];
        k=1;
        for(j=0;j<key;j++)
        {
            k=k*pt;
            k=k%n;
        }
        temp[i]=k;
        ct=k;
        en[i]=ct;
        i++;
    }
    en[i]=-1;
    printf("\n\nTHE ENCRYPTED SUDOKU IS : \n");
    len=0;
    for(i=0;i<N;i++)
    {
        for(j=0;j<N;j++)
        {
            printf("%d ",en[len]);
            len++;
        }
	printf("\n");
    }
}

void decrypt()
{
    long int pt,ct,key=d[0],k;
    i=0;
    while(en[i]!=-1)
    {
        ct=temp[i];
        k=1;
        for(j=0;j<key;j++)
        {
            k=k*ct;
            k=k%n;
        }
        pt=k+96;
        m[i]=pt;
        i++;
    }
    m[i]=-1;
    printf("\n\nTHE DECRYPTED MESSAGE IS : ");
    for(i=0;m[i]!=-1;i++)
	printf("%c",m[i]);
}

void decrypt_sudoku()
{
    long int pt,ct,key=d[0],k;
    i=0;
    while(en[i]!=-1)
    {
        ct=temp[i];
        k=1;
        for(j=0;j<key;j++)
        {
            k=k*ct;
            k=k%n;
        }
        pt=k;
        m[i]=pt;
        i++;
    }
    m[i]=-1;
    printf("\n\nTHE DECRYPTED SUDOKU IS : \n");
    int len=0;
    for(i=0;i<N;i++)
    {
        for(j=0;j<N;j++)
        {
            printf("%d ",m[len]);
            len++;
        }
        printf("\n");
    }
}

void graph()
{
    clrscr();
    int gd=DETECT,gm,x,y;
    initgraph(&gd,&gm,"c:\\turboc3\\bgi");
    setbkcolor(BLUE);
}

void graphics()
{
    clrscr();
    int gd=DETECT,gm,x,y;
    initgraph(&gd,&gm,"c:\\turboc3\\bgi");
    setbkcolor(BLUE);
    for(x=0;x<640;x=x+10)
    {
        setlinestyle(1,1,3);
        for(y=45;y<50;y++)
        {
            line(0,y,x,y);
            line(0,y+400,x,y+405);
        }
        for(y=78;y<83;y++)
            line(y-30,0,y-30,x);
        for(y=550;y<556;y++)
            line(y+35,0,y+35,x);
        delay(30);
    }
    settextstyle(8,0,2);
    outtextxy(50,100,"Encrypted Sudoku Solver");
    outtextxy(100,200,"Enter The Choice");
    outtextxy(100,250,"1. View sudoku");
    outtextxy(100,300,"2. View message");
    outtextxy(100,350,"3. Exit");
}

int main()
{

    int temp,ch;
    clrscr();
    do
    {
        graphics();
        cin>>ch;
	if(ch==1)
	{
	    graph();
		printf("\nEnter the numbers of sudoku\n");
		//int Sudoku[N][N];
		int Sudoku[9][9]={{3,0,6,5,0,8,4,0,0},
				    {5,2,0,0,0,0,0,0,0},
				    {0,8,7,0,0,0,0,3,1},
				    {0,0,3,0,1,0,0,8,0},
				    {9,0,0,8,6,3,0,0,5},
				    {0,5,0,0,9,0,6,0,0},
				    {1,3,0,0,0,0,2,5,0},
				    {0,0,0,0,0,0,0,7,4},
				    {0,0,5,2,0,6,3,0,0}};
		//Initialise_Sudoku(Sudoku);
		printf("\n");
		if(Solve_Sudoku(Sudoku))
		{
		    int k=0;
		    for(i=0;i<N;i++)
		    {
			for(j=0;j<N;j++)
			{
			    m[k]=Sudoku[i][j];
			    k++;
			}
		    }
		}
		else
		    printf("\nSudoku is not solvable\n");
		p=5;
		q=7;
		n=p*q;
		t=(p-1)*(q-1);
		value_of_e();
		encrypt_sudoku();
		printf("\nEnter the decryption key for the correct solution\n");
                while(1)
                {
                    scanf("%d",&temp);
                    if(temp==11)
                    {
                        decrypt_sudoku();
                        break;
                    }
                    else printf("\nWrong key try again\n");
                }
                delay(10000);
                graph();
                cout<<"\n Do you want to continue?(1-Yes,2-No) \t";
                cin>>temp;
                if(temp==1)
                    ch=1;
                else ch=3;
        }
        if(ch==2)
        {
            graph();
            printf("\nENTER FIRST PRIME NUMBER\n");
            scanf("%d",&p);
            flag=check_prime(p);
            if(flag==0)
            {
                printf("\nWRONG INPUT\n");
                exit(1);
            }
            printf("\nENTER ANOTHER PRIME NUMBER\n");
            scanf("%d",&q);
            flag=check_prime(q);
            if(flag==0||p==q)
            {
                printf("\nWRONG INPUT\n");
                exit(1);
            }
            printf("\nENTER MESSAGE\n");
            fflush(stdin);
            gets(msg);
            int l=strlen(msg);
            for(i=0;i<l;i++)
                m[i]=msg[i];
            n=p*q;
            t=(p-1)*(q-1);
            value_of_e();
            printf("\nPOSSIBLE VALUES OF e AND d ARE\n");
            for(i=0;i<j-1;i++)
                printf("\n%ld\t%ld",e[i],d[i]);
            encrypt();
            decrypt();
            delay(10000);
            graph();
            cout<<"\n Do you want to continue?(1-Yes,2-No) \t";
            cin>>temp;
            if(temp==1)
                ch=1;
            else ch=3;
        }
        if (ch==3)
            exit(0);
    }
    while(ch==1);
    getch();
}
