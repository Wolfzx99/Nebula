
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
typedef struct vect_t
{
	double x;
	double y;
	double z;
} vect_t;

extern const vect_t null_v;

/*	negates the direction of one vector  */
vect_t negate(vect_t a);

/*  scales one vector by a constant  */
vect_t scale(vect_t a, double k);

/*  calculates the length of one vector  */
double magnitude(vect_t a);

/*	normalizes one vector into its unit vector  */
vect_t normalize(vect_t a);

/*	calculates the sum of two vectors  */
vect_t add(vect_t a, vect_t b);

/*	calculates the difference of two vectors  */
vect_t subtract(vect_t a, vect_t b);

/*	calculates the dot product of two vectors  */
double dot(vect_t a, vect_t b);

/*	calculates the cross product of two vectors  */
vect_t cross(vect_t a, vect_t b);

#endif