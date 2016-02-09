
/*
 *	project: nebula
 *	file: dynamic_array.c
 *	
 *	description:
 *	provides functionality for dynamically-sized arrays
 *	element order is not necessarily maintained
 */
 
#include <stdlib.h>
#include <stdio.h>

#include "dynamic_array.h"

dyn_array * initialize(int init_capacity)
{
	void ** data_ptr = calloc(init_capacity, sizeof(void*));
	return & (dyn_array) {0, init_capacity, data_ptr};
}

void * get(dyn_array * d_a, int i)
{
	return d_a->data[i];
}

static void double_capacity(dyn_array * d_a)
{
	d_a->data = realloc(d_a->data, d_a->capacity * sizeof(void*) * 2);
	d_a->capacity *= 2;
}

void append(dyn_array * d_a, void * item_ptr)
{
	if (d_a->size >= d_a->capacity)
	{
		double_capacity(d_a);
	}
	printf("storing %p at %p\n", item_ptr, d_a->data);
	d_a->data[d_a->size] = item_ptr;
	printf("size: %d, cap: %d, data pointer: %p\n", d_a->size, d_a->capacity, d_a->data);
	d_a->size += 1;
}

void set(dyn_array * d_a, int i, void * item_ptr)
{
	/*	if the i is out of bounds, it simply appends the new item  */
	if (i >= d_a->size)
	{
		append(d_a, item_ptr);
	}
	
	else
	{
		d_a->data[i] = item_ptr;
	}
}

void erase(dyn_array * d_a, int i)
{
	d_a->data[i] = d_a->data[d_a->size - 1];
	d_a->size -= 1;
}