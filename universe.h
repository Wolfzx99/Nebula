
/*
 *	project: nebula
 *	file: universe.h
 *	
 *	description:
 *	header file for universe.c
 */
 
#include "vector.h"
 
#ifndef GRAVITY_H
#define GRAVITY_H

/*	a number twice as great as pi  */
extern const double TAU;

/*	gravitational constant  */
extern const double G;

/*	a body which experiences gravitational force  */
typedef struct grav_body
{
	char name[32];
	double mass;
	vector position;
	vector velocity;
	vector acceleration;
} grav_body;

void print_grav_body(grav_body a);

/*	a universe defined in terms its state, its precision, and its current time  */
typedef struct universe
{		
	/*	defines an array containing grav_bodies  */
	int num_bodies;
	grav_body * body;
	
	/*	the precision of the simulation (in seconds) */
	double time_step;
	
	/*	time since the simulation began (in seconds)  */
	double current_time;
} universe;

void print_universe(universe u);

/*	gives every body a random mass, position, and velocity  */
void randomize_universe(universe u);

/*	calculates the gravitational accelerations of a single two-body system;
	adds these to their accelerations  */
void simulate_grav_single(grav_body *a, grav_body *b);

/*	makes a call to simulate each system individually exactly once  */
void simulate_grav_full(universe *u);

#endif