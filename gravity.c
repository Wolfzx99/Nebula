
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>

/* constants */
const double TAU = 6.28318530717958647692528676655900576839433879875;   //tau, a number far superior to pi
const double G = 6.67384e-11;     //gravitational constant
const double M = 1.98855e30;      //combined mass of the objects; set for the mass of the sun

/* simulates gravity; returns the distance between the ending position and the starting position */
double simulate_gravity(double R_X, double R_Y, double V_X, double V_Y, double N, double t)
{
     /* set current conditions to starting conditions */
    double r_x = R_X, r_y = R_Y, v_x = V_X, v_y = V_Y, n = N;
    
    double a_x, a_y;
	unsigned long i, j, m = 0;
	
	/* ensure that j doesn't overflow as long as N < 2^64 by using a nested for loop */
	while (n >= pow(2, 32))
	{
		n = N / pow(2, ++m);
	}
    for (i = 0; i < pow(2, m); i++)
	{
		for (j = 0; j < n; j++)
		{
			/* calculate acceleration for this interval */
			a_x = -G * M * pow(r_x * r_x + r_y * r_y, -1.5) * r_x;
			a_y = -G * M * pow(r_x * r_x + r_y * r_y, -1.5) * r_y;
			
			/* calculate distance for the next interval */
			r_x = r_x + v_x * t + a_x * t * t / 2;
			r_y = r_y + v_y * t + a_y * t * t / 2;
			
			/* calculate velocity for the next interval */
			v_x = v_x + a_x * t;
			v_y = v_y + a_y * t;
		}
	}
    
    /* return the distance between the ending position and the starting position; when the orbit is circular and the time T is set for a multiple of a complete orbital period, this value provides a benchmark for the simulation's accuracy */
    return hypot(R_X - r_x, R_Y - r_y);
}

/* begin main function */
int main(void)
{
    double R_X, R_Y, V_X, V_Y;
	unsigned long period;
    double T;
    double power, N, t;
    clock_t start;
	double distance;
	
    /* starting positions */
    R_X = 0;                    //x component of the distance between the objects; should be 0
    R_Y = 5.9e9;                //y component of the distance between the objects; set for very close to the sun
    V_X = sqrt(G * M / R_Y);    //x component of the combined velocity of the objects; set for a circular orbit
    V_Y = 0;                    //y component of the combined velocity of the objects; should be 0
    
    /* timescale */
	printf("number of orbital periods = ");
    scanf("%lu", &period);
    T = period * TAU * sqrt(R_Y * R_Y / (V_X * V_X));   //total time of simulation; set for the orbital period
    
    /* get precision from user */
    printf("number of calculations = 2^");
    scanf("%lf", &power);
    N = pow(2, power);  //the number of calculations to make in time T
    t = T / N;      //length of time per calculation
    
    /* start measuring CPU time */
    start = clock();
    
    /* simulates gravity and returns the distance from the starting point */
    distance = simulate_gravity(R_X, R_Y, V_X, V_Y, N, t);
    
    /* calculate and print the total CPU time taken */
    printf("calculation time = %.2lf s\n", ((double) (clock() - start) / CLOCKS_PER_SEC));
    
    /* print the distance between the ending position and the starting position */
    printf("distance from starting position = %e m\n", distance);
    
	/* wait for the user to hit enter before exiting */
	fseek(stdin, 0, SEEK_END);
	while(getchar() != '\n');
    return(EXIT_SUCCESS);
}