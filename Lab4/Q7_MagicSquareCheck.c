#include<stdio.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<unistd.h>

int size, sum1, sum2, rowsum, columnsum;

void get_input(int size, int arr[][size]);
void displayMagicSquare(int size, int arr[][size]);
int DiagonalSum(int arr[][size]);
int RowSum(int arr[][size]);
int ColumnSum(int arr[][size]);

int main()
{
    int sum = 0, flag1, flag2, status;
    printf("Enter order of Square Matrix: ");
    scanf("%d", &size);
    int arr[size][size];

    printf("Enter the entries for Matrix: ");
    get_input(size, arr);
    printf("\nSquare Matrix is: \n\n");
    displayMagicSquare(size, arr);

    pid_t pid1, pid2, pid3;
    pid1 = vfork();
    if(pid1 == 0)
    {
        sum = RowSum(arr);
        exit(0);
    }
    else
    {
        pid2 = vfork();
        if(pid2 == 0)
        {
            printf("\nSatisfies Column Sum condition: ");
            if(sum == ColumnSum(arr))
            {
                flag1 = 1;
                printf("YES\n");
            }
            else
            {
                flag1 = 0;   
                printf("NO\n");
            }
            exit(0);
        }
        else
        {
            pid3 = vfork();
            if(pid3 == 0)
            {
                printf("Satisfies Diagonal Sum condition: ");
                if(sum == DiagonalSum(arr))
                {
                    flag2 = 1;
                    printf("YES\n");
                }
                else
                {
                    flag2 = 0;   
                    printf("NO\n");
                }
                
                exit(0);
            }
        }  
    }

    waitpid(-1, &status, 0);
    if((flag1 == flag2) == 1)
        printf("\nGiven Matrix is a Magic Square.\n\n");
    else
        printf("\nGiven Matrix is not a Magic Square.\n\n");
    
    return 0;
}

int DiagonalSum(int arr[][size])
{
    // calculate the sum of the prime diagonal 
    int i;
    sum1 = 0, sum2 = 0;  
    for(i=0; i<size; i++) 
        sum1 = sum1 + arr[i][i]; 
    // the secondary diagonal 
    for(i=0; i<size; i++) 
        sum2 = sum2 + arr[i][size-1-i]; 
  
    if(sum1 != sum2)  
        return 0;
    else
        return sum1; 
}

int RowSum(int arr[][size])
{
    // For sums of Rows  
    int tempsum;
    for(int i=0; i<size; i++)
    { 
        rowsum = 0;      
        for(int j=0; j<size; j++) 
        {
            rowsum += arr[i][j]; 
        
        }    // check if every row sum is equal to prime diagonal sum 
        	if(i == 0) 
        	{
        		tempsum = rowsum;
        		continue;
        	}
            if(rowsum != tempsum) 
                return 0;
    }
        
        return rowsum;
}

int ColumnSum(int arr[][size])
{
    // For sums of Columns
    int tempsum;
    for(int i=0; i<size; i++)
    {      
        columnsum = 0;      
        for(int j=0; j<size; j++)
        {
            columnsum += arr[j][i]; 
  
        }  // check if every column sum is equal to prime diagonal sum 
        	if( i==0 )
        	{
        		tempsum = columnsum;
        		continue;
            }
            if(tempsum != columnsum)  
                return 0;
    }
        
        return columnsum;
 
}

void get_input(int size, int arr[][size])
{
    for(int i=0; i<size; i++)
    {
        for(int j=0; j<size; j++)
        {
            scanf("%d", &arr[i][j]);
        }
    }
}

void displayMagicSquare(int size, int arr[][size])
{
    for(int i=0; i<size; i++)
    {
        for(int j=0; j<size; j++)
        {
            printf(" %5d", arr[i][j]);
        }
        printf("\n");
    }
}