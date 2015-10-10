
/*
 *	project: nebula
 *	file: main.c
 *	
 *	description:
 *	runs the simulator
 */
 
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "gravity.h"
#include "vector.h"

int main(void)
{
	clock_t start;
	double sim_time = 3.154e+7;
	
	/*	defines universe  */
	universe u;
	u.current_time = 0;
	u.time_step = 1;
	u.num_bodies = 2;
	u.body = calloc(u.num_bodies, sizeof(grav_body));
	
	/*	terminates if calloc fails  */
	if (u.body == NULL)
	{
		printf("unable to allocate memory");
		
		/*	waits for the user to hit enter before exiting  */
		fseek(stdin, 0, SEEK_END);
		while(getchar() != '\n');
		return(EXIT_SUCCESS);
	}
	
	u.body[0] = (grav_body) {"Sun", 1.98855e30, null_v, null_v, null_v};
	u.body[1] = (grav_body) {"Comet", 1e3, (vector) {5.9e9, 0, 0}, (vector) {0, 149978.8942, 0}, null_v};
	
	/*	prints the initial state  */
	printf("----INITIAL STATE----\n");
	print_universe(u);
	
	/*	starts the clock  */
	start = clock();
	while (u.current_time < sim_time)
	{
		simulate_grav_full(&u);
	}

	/*	prints the final state  */
	printf("----FINAL STATE----\n");
	print_universe(u);
	
	/*  ends the clock and displays time elapsed  */
	printf("CPU time elapsed: %.2lf s\n", ((double) (clock() - start) / CLOCKS_PER_SEC));
	
	free(u.body);
	
	/*	waits for the user to hit enter before exiting  */
	fseek(stdin, 0, SEEK_END);
	while(getchar() != '\n');
	return(EXIT_SUCCESS);
}