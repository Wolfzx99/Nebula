
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
const vector null_v = (vector) {0, 0, 0};

/*	negates the direction of one vector  */
vector negate(vector a)
{
	double x = - a.x;
	double y = - a.y;
	double z = - a.z;
	return (vector) {x, y, z};
}

/*  scales one vector by a constant  */
vector scale(vector a, double k)
{
	double x = a.x * k;
	double y = a.y * k;
	double z = a.z * k;
	return (vector) {x, y, z};
}

/*  calculates the length of one vector  */
double magnitude(vector a)
{
	return sqrt(pow(a.x, 2) + pow(a.y, 2) + pow(a.z, 2));
}

/*	normalizes one vector into its unit vector  */
vector normalize(vector a)
{
	double length = magnitude(a);
	double x = a.x / length;
	double y = a.y / length;
	double z = a.z / length;
	return (vector) {x, y, z};
}

/*	calculates the sum of two vectors  */
vector add(vector a, vector b)
{
	double x = a.x + b.x;
	double y = a.y + b.y;
	double z = a.z + b.z;
	return (vector) {x, y, z};
}

/*	calculates the difference of two vectors  */
vector subtract(vector a, vector b)
{
	double x = a.x - b.x;
	double y = a.y - b.y;
	double z = a.z - b.z;
	return (vector) {x, y, z};
}

/*	calculates the dot product of two vectors  */
double dot(vector a, vector b)
{
	return (a.x * b.x) + (a.y * b.y) + (a.z * b.z);
}

/*	calculates the cross product of two vectors  */
vector cross(vector a, vector b)
{
	double x = (a.y * b.z) - (a.z * b.y);
	double y = (a.z * b.x) - (a.x * b.z);
	double z = (a.x * b.y) - (a.y * b.x);
	return (vector) {x, y, z};
}