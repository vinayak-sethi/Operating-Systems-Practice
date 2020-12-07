#include<stdio.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<unistd.h>

#define MAX 100000

void MagicSquare(int size, int arr[][size]);
void OddOrderMagicSquare(int size, int arr[][size]);
void DoublyEvenMagicSquare(int size, int arr[][size]);
void SinglyEvenMagicSquare(int size, int arr[][size]);
void displayMagicSquare(int size, int arr[][size]);
int MagicSquareCheck(int size, int arr[][size]);

int main()
{
    int size;
    printf("Enter order of square matrix: ");
    scanf("%d", &size);
    int arr[size][size];

    pid_t pid;
    pid = vfork();
    if(pid == 0)
    {
        if(size < 3)
        {
            printf("Error: Order of matrix must be greater than 2\n");
            exit(EXIT_FAILURE);
        }

        MagicSquare(size, arr);
        exit(0);
    }
    else
    {
        wait(NULL);
        displayMagicSquare(size, arr);
        int valid = MagicSquareCheck(size, arr);
        if(valid == 1)
            printf("\nIt is a valid Magic Square\n\n");
        else
            printf("It is not a valid Magic Square\n\n");
    }
    
    return 0;
}

void MagicSquare(int size, int arr[][size])
{
    if(size % 2 == 1)
        OddOrderMagicSquare(size, arr);
    else if(size % 4 == 0)
        DoublyEvenMagicSquare(size, arr);
    else
        SinglyEvenMagicSquare(size, arr);
}

void OddOrderMagicSquare(int size, int arr[][size])
{
    int square = size * size;
    int i=0, j = size/2, k;

    for(k=1; k<= square; ++k)
    {
        arr[i][j] = k;
        i--;
        j++;

        if(k % size == 0)
        {
            i = i+2;
            --j;
        }
        else
        {
            if(j == size)
                j = j - size;
            else if(i<0)
                i = i + size;
        }
    }
}

void DoublyEvenMagicSquare(int size, int arr[][size])
{
    int I[size][size];
    int J[size][size];

    int i, j;

    //prepare I, J
    int index=1;
    for(i=0; i<size; i++)
        for(j=0; j<size; j++)
        {
            I[i][j] = ((i+1)%4)/2;
            J[j][i] = ((i+1)%4)/2;
            arr[i][j] = index;
            index++;
        }

    for(i=0; i<size; i++)
        for(j=0; j<size; j++)
        {
            if(I[i][j]==J[i][j])
                arr[i][j] = size*size+1 - arr[i][j];
        }
}

void SinglyEvenMagicSquare(int size, int arr[][size])
{
    int N = size;
	int halfN = N/2; //size of ABCD boxes
	int k = (N-2)/4; // to get 'noses' of A & D boxes
    
    int temp;
    int new[N];

    int swapCol[N]; // columns which need to swap between C-B & A-D
    int index=0; // index of swapCol
    int miniMagic[halfN][halfN];

  	OddOrderMagicSquare(halfN, miniMagic);	//creating odd magic square for A box
	
	//creating 4 magic boxes
  	for(int i=0; i<halfN; i++)
    	for (int j=0; j<halfN; j++)
        {
	        arr[i][j] = miniMagic[i][j]; 	  		  //A box
      	    arr[i+halfN][j+halfN] = miniMagic[i][j]+halfN*halfN;   //B box
            arr[i][j+halfN] = miniMagic[i][j]+2*halfN*halfN;       //C box
            arr[i+halfN][j] = miniMagic[i][j]+3*halfN*halfN;       //D box
        }

    for (int i=1; i<=k; i++)
        swapCol[index++] = i;

    for (int i=N-k+2; i<=N; i++)
        swapCol[index++] = i;

    //swaping values between C-B & A-D by known columns
    for(int i=1; i<=halfN; i++)
        for(int j=1; j<=index; j++)
        {
            temp = arr[i-1][swapCol[j-1]-1];
            arr[i-1][swapCol[j-1]-1] = arr[i+halfN-1][swapCol[j-1]-1];
            arr[i+halfN-1][swapCol[j-1]-1] = temp;
        }

    //swaping noses
    temp = arr[k][0]; 
    arr[k][0] = arr[k+halfN][0]; 
    arr[k+halfN][0] = temp;

    temp = arr[k+halfN][k]; 
    arr[k+halfN][k] = arr[k][k]; 
    arr[k][k] = temp;
    //end of swaping
}

void displayMagicSquare(int size, int arr[][size])
{
    printf("Sum of each row, column and both diagonals is: %d\n\n", size*(size*size + 1) / 2);
    for(int i=0; i<size; i++)
    {
        for(int j=0; j<size; j++)
        {
            printf(" %5d", arr[i][j]);
        }
        printf("\n");
    }
}

int MagicSquareCheck(int size, int arr[][size])
{
    // calculate the sum of the prime diagonal 
    int i, sum1 = 0, sum2 = 0;  
    for(i=0; i<size; i++) 
        sum1 = sum1 + arr[i][i]; 
    // the secondary diagonal 
    for(i=0; i<size; i++) 
        sum2 = sum2 + arr[i][size-1-i]; 
  
    if(sum1 != sum2)  
        return 0; 
  
    // For sums of Rows  
    for(i=0; i<size; i++)
    { 
        int rowSum = 0;      
        for(int j=0; j<size; j++) 
            rowSum += arr[i][j]; 
          
        // check if every row sum is equal to prime diagonal sum 
        if(rowSum != sum1) 
            return 0; 
    } 
  
    // For sums of Columns 
    for(i=0; i<size; i++)
    {      
        int colSum = 0;      
        for(int j=0; j<size; j++) 
            colSum += arr[j][i]; 
  
        // check if every column sum is equal to prime diagonal sum 
        if(sum1 != colSum)  
        return 0; 
    } 
  
    return 1; 
}