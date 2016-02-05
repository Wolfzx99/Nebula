
/*
 *	project: nebula
 *	file: gravity.c
 *	
 *	description:
 *	provides basic description of gravitational bodies
 *	provides functionality for simulating gravity
 *	categorizes bodies into a universe
 */
 
#include <stdio.h>
#include <math.h>
#include <time.h>

#include "gravity.h"
#include "vector.h"



const double TAU = 6.28318530717958647692528676655900576839433879875;
const double G = 6.67384e-11;

void print_body(body a)
{
	printf("\t[%s]\n\tmass: %.2e\n\tposition: <%.2e,%.2e,%.2e>\n\tvelocity: <%.2e,%.2e,%.2e>\n", a.name, a.mass, a.position.x, a.position.y, a.position.z, a.velocity.x, a.velocity.y, a.velocity.z);
}

void print_universe()
{
	int i;
	
	printf("universe time: %.2e\ntime step: %.2e\n\n", current_time, time_step);
	
	for (i = 0; i < universe_size; i++)
	{
		print_body(universe[i]);
	}
	
	printf("\n");
}

/*	calculates the gravitational accelerations of a single two-body system;
	adds these to their accelerations  */
void simulate_grav_single(body *a, body *b)
{
	vector dist = subtract(b->position, a->position);
	vector grav_force = scale(normalize(dist), (G * a->mass * b->mass / pow(magnitude(dist), 2)));
	a->acceleration = add(a->acceleration, scale(grav_force, 1 / a->mass));
	b->acceleration = add(b->acceleration, scale(negate(grav_force), 1 / b->mass));
}

/*	makes a call to simulate each system individually exactly once  */
void simulate_grav_full()
{
	int i, j;
	
	/*	resets acceleration of each body to zero  */
	for (i = 0; i < universe_size; i++)
	{
		universe[i].acceleration = null_v;
	}
	
	for (i = 0; i < universe_size; i++)
	{	
		for (j = i + 1; j < universe_size; j++)
		{
			simulate_grav_single(&universe[i], &universe[j]);
		}
		
		/*	iterates using the basic kinematics equations over time_step  */
		universe[i].position = add(universe[i].position, add(scale(universe[i].velocity, time_step), scale(universe[i].acceleration, 0.5 * pow(time_step, 2))));
		universe[i].velocity = add(universe[i].velocity, scale(universe[i].acceleration, time_step));
	}
	
	current_time += time_step;
}