
/*
 *	project: nebula
 *	file: gravity.h
 *	
 *	description:
 *	header file for gravity.c
 */
 
#ifndef GRAVITY_H
#define GRAVITY_H

#include "vector.h"
#include "array.h"

#define G 6.67384e-11

#define NAME_LENGTH 16
#define INIT_CAPACITY 100
#define TIME_STEP 1

/*	an object which experiences gravitational force  */
typedef struct
{
	char name[NAME_LENGTH];
	double mass;
	vect_t pos;
	vect_t vel;
	vect_t acc;
} object_t;

ARRAY_HEADER(object, object_t *)

object_array_t uni;

/*	time since the simulation began (in seconds)  */
double current_time;

void object_init();

void uni_init();

void print_uni();

void simulate_grav();

#endif