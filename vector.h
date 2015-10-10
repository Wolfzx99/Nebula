
/*
 *	project: nebula
 *	file: vector.h
 *	
 *	description:
 *	header file for vector.c
 */

#ifndef VECTOR_H
#define VECTOR_H

/*	a three-dimensional euclidean vector  */
typedef struct vector
{
	double x;
	double y;
	double z;
} vector;

extern const vector null_v;

/*	negates the direction of one vector  */
vector negate(vector a);

/*  scales one vector by a constant  */
vector scale(vector a, double k);

/*  calculates the length of one vector  */
double magnitude(vector a);

/*	normalizes one vector into its unit vector  */
vector normalize(vector a);

/*	calculates the sum of two vectors  */
vector add(vector a, vector b);

/*	calculates the difference of two vectors  */
vector subtract(vector a, vector b);

/*	calculates the dot product of two vectors  */
double dot(vector a, vector b);

/*	calculates the cross product of two vectors  */
vector cross(vector a, vector b);

#endif