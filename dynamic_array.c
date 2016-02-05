
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

dyn_array * initialize(int init_capacity, int type_size)
{
	void * data_ptr = calloc(init_capacity, type_size);
	return & (dyn_array) {0, init_capacity, type_size, data_ptr};
}

static void double_capacity(dyn_array * d_a)
{
	d_a->data = realloc(d_a->data, d_a->capacity * d_a->type_size * 2);
	d_a->capacity *= 2;
}

void append(dyn_array * d_a, void * item_ptr)
{
	if (d_a->size >= d_a->capacity)
	{
		double_capacity(d_a);
	}
	
	d_a->data[d_a->size] = item_ptr;
	d_a->size += 1;
}

void set(dyn_array * d_a, int index, void * item_ptr)
{
	/*	if the index is out of bounds, it simply appends the new item  */
	if (index >= d_a->size)
	{
		append(d_a, item_ptr);
	}
	
	else
	{
		d_a->data[index] = item_ptr;
	}
}

void erase(dyn_array * d_a, int index)
{
	d_a->data[index] = d_a->data[d_a->size - 1];
	d_a->size -= 1;
}