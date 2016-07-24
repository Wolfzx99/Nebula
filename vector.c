
/*
 *	project: nebula
 *	file: vector.c
 *	
 *	description:
 *	provides three-dimensional vector functionality
 */

#include <math.h>

#include "vector.h"

/*	defines the null vector of magnitude zero and direction undefined  */
const vect_t null_v = (vect_t) {0, 0, 0};

/*	negates the direction of one vector  */
vect_t negate(vect_t a)
{
	double x = -a.x;
	double y = -a.y;
	double z = -a.z;
	return (vect_t) {x, y, z};
}

/*  scales one vector by a constant  */
vect_t scale(vect_t a, double k)
{
	double x = a.x * k;
	double y = a.y * k;
	double z = a.z * k;
	return (vect_t) {x, y, z};
}

/*  calculates the length of one vector  */
double magnitude(vect_t a)
{
	return sqrt(pow(a.x, 2) + pow(a.y, 2) + pow(a.z, 2));
}

/*	normalizes one vector into its unit vector  */
vect_t normalize(vect_t a)
{
	double length = magnitude(a);
	double x = a.x / length;
	double y = a.y / length;
	double z = a.z / length;
	return (vect_t) {x, y, z};
}

/*	calculates the sum of two vectors  */
vect_t add(vect_t a, vect_t b)
{
	double x = a.x + b.x;
	double y = a.y + b.y;
	double z = a.z + b.z;
	return (vect_t) {x, y, z};
}

/*	calculates the difference of two vectors  */
vect_t subtract(vect_t a, vect_t b)
{
	double x = a.x - b.x;
	double y = a.y - b.y;
	double z = a.z - b.z;
	return (vect_t) {x, y, z};
}

/*	calculates the dot product of two vectors  */
double dot(vect_t a, vect_t b)
{
	return (a.x * b.x) + (a.y * b.y) + (a.z * b.z);
}

/*	calculates the cross product of two vectors  */
vect_t cross(vect_t a, vect_t b)
{
	double x = (a.y * b.z) - (a.z * b.y);
	double y = (a.z * b.x) - (a.x * b.z);
	double z = (a.x * b.y) - (a.y * b.x);
	return (vect_t) {x, y, z};
}