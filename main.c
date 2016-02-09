
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

#include "dynamic_array.h"

typedef struct empty
{
		int x;
} empty;

int main(void)
{
	int i;
	dyn_array * int_l = initialize(8);
	
	for (i = 0; i < 8; i++)
	{
		append(int_l, (void*)(&((empty) {100 + i})));
	}
	
	for (i = 0; i < 3; i++)
	{
		printf("%d\n", (*((empty*)get(int_l, i))).x);
	}
	
	return 0;
}

// #include "gravity.h"
// #include "vector.h"
// #include "data.h"

// int main(void)
// {
	// clock_t start;
	// double sim_time = 3.154e+7;
		
	// /*	sets parameters of gravity simulator  */
	// const time_step = 1;
	// current_time = 0;
	// int universe_size = 2;
	
	// /*  creates universe  */
	// body universe[universe_size];
	// universe[0] = (body) {"Sun", 1.98855e30, null_v, null_v, null_v};
	// universe[1] = (body) {"Comet", 1e3, (vector) {5.9e9, 0, 0}, (vector) {0, 149978.8942, 0}, null_v};
	
	// /*	prints the initial state  */
	// printf("----INITIAL STATE----\n");
	// print_universe();
	
	// /*	starts the clock  */
	// start = clock();
	// while (current_time < sim_time)
	// {
		// simulate_grav_full();
	// }

	// /*	prints the final state  */
	// printf("----FINAL STATE----\n");
	// print_universe();
	
	// /*  ends the clock and displays time elapsed  */
	// printf("CPU time elapsed: %.2lf s\n", ((double) (clock() - start) / CLOCKS_PER_SEC));
	
	// /*	waits for the user to hit enter before exiting  */
	// fseek(stdin, 0, SEEK_END);
	// while(getchar() != '\n');
	// return(EXIT_SUCCESS);
// }
