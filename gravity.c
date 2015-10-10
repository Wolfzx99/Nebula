
/*
 *	project: nebula
 *	file: gravity.c
 *	
 *	description:
 *	provides basic description of gravitational bodies
 *	provides functionality for simulating gravity
 */
 
#include <stdio.h>
#include <math.h>
#include <time.h>

#include "gravity.h"
#include "vector.h"

/*	a number twice as great as pi  */
const double TAU = 6.28318530717958647692528676655900576839433879875;

/*	gravitational constant  */
const double G = 6.67384e-11;

void print_grav_body(grav_body a)
{
	printf("\t[%s]\n\tmass: %.2e\n\tposition: <%.2e,%.2e,%.2e>\n\tvelocity: <%.2e,%.2e,%.2e>\n", a.name, a.mass, a.position.x, a.position.y, a.position.z, a.velocity.x, a.velocity.y, a.velocity.z);
}

void print_universe(universe u)
{
	int i;
	
	printf("universe time: %.2e\ntime step: %.2e\n\n", u.current_time, u.time_step);
	
	for (i = 0; i < u.num_bodies; i++)
	{
		print_grav_body(u.body[i]);
	}
	
	printf("\n");
}

/*	calculates the gravitational accelerations of a single two-body system;
	adds these to their accelerations  */
void simulate_grav_single(grav_body *a, grav_body *b)
{
	vector dist = subtract(b->position, a->position);
	vector grav_force = scale(normalize(dist), (G * a->mass * b->mass / pow(magnitude(dist), 2)));
	a->acceleration = add(a->acceleration, scale(grav_force, 1 / a->mass));
	b->acceleration = add(b->acceleration, scale(negate(grav_force), 1 / b->mass));
}

/*	makes a call to simulate each system individually exactly once  */
void simulate_grav_full(universe *u)
{
	int i, j;
	
	/*	resets acceleration of each body to zero  */
	for (i = 0; i < u->num_bodies; i++)
	{
		u->body[i].acceleration = null_v;
	}
	
	for (i = 0; i < u->num_bodies; i++)
	{	
		for (j = i + 1; j < u->num_bodies; j++)
		{
			simulate_grav_single(&u->body[i], &u->body[j]);
		}
		
		/*	iterates using the basic kinematics equations over time_step  */
		u->body[i].position = add(u->body[i].position, add(scale(u->body[i].velocity, u->time_step), scale(u->body[i].acceleration, 0.5 * pow(u->time_step, 2))));
		u->body[i].velocity = add(u->body[i].velocity, scale(u->body[i].acceleration, u->time_step));
	}
	
	u->current_time += u->time_step;
}