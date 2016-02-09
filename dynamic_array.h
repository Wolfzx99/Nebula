
/*
 *	project: nebula
 *	file: dynamic_array.h
 *	
 *	description:
 *	header file for dynamic_array.c
 */
 
#ifndef DYNAMIC_ARRAY_H
#define DYNAMIC_ARRAY_H
 
typedef struct dyn_array
{
	int size;
	int capacity;
	void ** data;
} dyn_array;

dyn_array * initialize();

void * get();

static void increase_capacity();

void append();

void set();

void erase();

#endif