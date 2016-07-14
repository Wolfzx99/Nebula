
/*
 *	project: nebula
 *	file: main.c
 *	
 *	description:
 *	runs the simulator
 */
 
#include <stdio.h>
#include <stdlib.h>

typedef struct dyn_array
{
	int size;
	int capacity;
	int type_size;
	void * data;
} dyn_array;

int main()
{
    dyn_array * test = &(dyn_array){0, 8, sizeof(int), calloc(8, sizeof(int))};
    
    ((int*)test->data)[0] = 19;
    
    printf("%d\n", ((int*)test->data)[0]);
    
	/*	waits for the user to hit enter before exiting  */
	fseek(stdin, 0, SEEK_END);
	while(getchar() != '\n');
	return(EXIT_SUCCESS);
}