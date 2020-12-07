#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>

#define MAX_THREAD 4 //maximum number of threads

int max;
double circle_points = 0, square_points = 0;

struct limit
{
	int low;
	int high;
};

void *MonteCarlo_PI(void *arg);

int main(int argc, char *argv[])
{
    //Validate the correct usage of command line arguments
	if(argc != 2)
	{
		printf("\nSyntax: %s <Limit>\n\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	if(atoi(argv[1]) < 0)
	{
		printf("\nlimit value should be greater than zero...\n\n");
		exit(EXIT_FAILURE);
	}

	max = atoi(argv[1]);
    struct limit *l[4];

	for(int i=0; i<4; i++)
		l[i] = (struct limit *)malloc(sizeof(struct limit)); 

	//creating the limits for different threads
	l[0]->low = 0, l[0]->high = max/4;
	l[1]->low = l[0]->high+1, l[1]->high = l[0]->high*2;
	l[2]->low = l[1]->high+1, l[2]->high = l[0]->high*3;
	l[3]->low = l[2]->high+1, l[3]->high = max;

    pthread_t *tid = (pthread_t *)malloc(MAX_THREAD*sizeof(pthread_t)); //returns the thread id of thread created
    pthread_attr_t attr; //to define thread attributes
	pthread_attr_init(&attr); //initializes the thread attribute


	for(int i=0; i<MAX_THREAD; i++)
    {
        pthread_create(&tid[i], &attr, MonteCarlo_PI, (void *)l[i]); //creates a new thread
    }

	for(int i=0; i<MAX_THREAD; i++)
    {
		pthread_join(tid[i], NULL); //wait for termination of the thread
    }

    double pi = (double)(4 * circle_points) / square_points; //estimating PI value
    printf("\n\nEstimated value of PI using Monte Carlo Simulation Technique: %lf\n\n", pi);

    return 0;
}

void *MonteCarlo_PI(void *arg)
{
    struct limit *l = (struct limit *)arg;
    int interval, i; 
    double rand_x, rand_y, origin_dist; 
  
    // Initializing rand() 
    srand(time(NULL)); 
  
    // Total Random numbers generated = possible x values * possible y values 
    for (i = l->low; i<(l->high * l->high); i++)
    { 
        // Randomly generated x and y values 
        rand_x = (double)(rand() % (l->high + 1)) / l->high;
        rand_y = (double)(rand() % (l->high + 1)) / l->high; 
  
        // Distance between (x, y) from the origin 
        origin_dist = rand_x * rand_x + rand_y * rand_y; 
  
        // Checking if (x, y) lies inside the define 
        // circle with R=1 
        if (origin_dist <= 1)
            circle_points++; 
  
        // Total number of points generated 
        square_points++;  
    }
    
    printf("\nCircle Points -> %.2f | Square Points -> %.2f", circle_points, square_points);

    pthread_exit(0); //to exit a thread
}