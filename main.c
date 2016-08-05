
#include <time.h>

#include "gravity.h"
#include "vector.h"
#include "data.h"

int main(void)
{
	
	/*  test  */
	{
		#define SIM_TIME (100*3.154e+7)
		
		clock_t start;
		
		uni_init();
		
		object_t *a = malloc(sizeof(object_t));
		object_t *b = malloc(sizeof(object_t));		
		if (NULL == a) { return(EXIT_FAILURE); }
		if (NULL == b) { return(EXIT_FAILURE); }
		
		object_init(a, "Sol", 1.98855e30, null_v, null_v, null_v);
		object_init(b, "Comet", 1e3, (vect_t) {5.9e9, 0, 0}, (vect_t) {0, 149978.8942, 0}, null_v);
		
		if (-1 == object_array_append(&uni, &a)) { return(EXIT_FAILURE); }
		if (-1 == object_array_append(&uni, &b)) { return(EXIT_FAILURE); }
		
		/*	prints the initial state  */
		printf("----INITIAL STATE----\n");
		print_uni();
		
		/*	starts the clock  */
		start = clock();
		while (current_time < SIM_TIME)
		{
			simulate_grav();
		}
	
		/*	prints the final state  */
		printf("----FINAL STATE----\n");
		print_uni();
		
		/*  ends the clock and displays time elapsed  */
		printf("CPU time elapsed: %.2lf s\n", ((double) (clock() - start) / CLOCKS_PER_SEC));
	}

	/*	waits for the user to hit enter before exiting  */
	fseek(stdin, 0, SEEK_END);
	while(getchar() != '\n');
	return(EXIT_SUCCESS);
}
