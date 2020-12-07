#include<stdio.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<unistd.h>

int nr1, nr2, nc1, nc2;

void get_input(int row, int column, int arr[][column]);
void displayMatrix(int row, int column, int arr[][column]);
int MatMul(int i, int j, int a[][nc1], int b[][nc2]);

int main()
{
    int status;
    printf("Enter the size of Matrix 1: ");
    scanf("%d %d",&nr1, &nc1);
    printf("Enter the size of Matrix 2: ");
    scanf("%d %d",&nr2, &nc2);

    int a[nr1][nc1];
    int b[nr2][nc2];

    if(nr2 != nc1)
    {
        printf("\nMatrix Multiplication cannot be performed\nDue to mismatch in Column No. of Matrix 1 and Row No. of Matrix 2...\n\n");
        exit(EXIT_FAILURE);
    }

    printf("Enter the entries for Matrix 1: ");
    get_input(nr1, nc1, a);
    printf("Enter the entries for Matrix 2: ");
    get_input(nr2, nc2, b);

    printf("\nFirst Matrix: \n");
    displayMatrix(nr1, nc1, a);
    printf("\nSecond Matrix: \n");
    displayMatrix(nr2, nc2, b);

    int c[nr1][nc2];
    printf("\nMatrix Multiplication of Matrix 1 and Matrix 2 is: \n");
    pid_t pid[nr1 * nc2];
    int index = 0;
    int sum1, sum2;

    for(int i=0; i<nr1; i++)
    {   
        for(int j=0; j<nc2; j += 2)
        {
            pid[index] = vfork(); //use of vfork()
            if(pid[index++] == 0)
            {
                sum1 = MatMul(i, j, a, b);
                c[i][j] = sum1;
                exit(0);
            }
            else
            {
                if(j+1 < nc2)
                {
                    sum2 = MatMul(i, j + 1, a, b);
                    c[i][j + 1] = sum2;                  
                }
            }
        }
    }

    waitpid(-1, & status, 0);
    displayMatrix(nr1, nc2, c);
    printf("\n");
    return 0;
}

void get_input(int row, int column, int arr[][column])
{
    for(int i=0; i<row; i++)
    {
        for(int j=0; j<column; j++)
        {
            scanf("%d", &arr[i][j]);
        }
    }
}

void displayMatrix(int row, int column, int arr[][column])
{
    for(int i=0; i<row; i++)
    {
        for(int j=0; j<column; j++)
        {
            printf(" %5d", arr[i][j]);
        }
        printf("\n");
    }
}

int MatMul(int a, int b, int arr1[][nc1], int arr2[][nc2])
{
    int sum = 0;
    for(int i=0; i<nr2; i++)
    {
        sum += arr1[a][i] * arr2[i][b];
    }
    return sum;
}