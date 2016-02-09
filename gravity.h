
/*
 *	project: nebula
 *	file: gravity.h
 *	
 *	description:
 *	header file for gravity.c
 */
 
#include "vector.h"
 
#ifndef GRAVITY_H
#define GRAVITY_H

/*	a body which experiences gravitational force  */
typedef struct body
{
	char name[16];
	double mass;
	vector position;
	vector velocity;
	vector acceleration;
} body;

extern body universe[];

/*	a number twice as great as pi  */
extern const double TAU;

/*	gravitational constant  */
extern const double G;

/*	the precision of the simulation (in seconds)  */
extern const double time_step;
	
/*	time since the simulation began (in seconds)  */
extern double current_time;

/*	number of objects in the universe  */
extern int universe_size;

void print_body();

void print_universe();

/*	gives every body a random mass, position, and velocity  */
void randomize_universe();

/*	calculates the gravitational accelerations of a single two-body system;
	adds these to their accelerations  */
void simulate_grav_single();

/*	makes a call to simulate each system individually exactly once  */
void simulate_grav_full();

#endif