#ifndef ARRAY_H
#define ARRAY_H

#include <stdio.h>
#include <stdlib.h>

/* Defines dynamic array types */
#define DEFINE_ARRAY_TYPE(name, type) \
	typedef struct {                  \
		size_t size;                  \
		size_t capacity;              \
		type * data;                  \
	} name##_array_t;

/* Declares dynamic array functions */
#define DECLARE_ARRAY_FUNCS(name)                              		\
	int name##_array_init();          								\
	void name##_array_free();                     					\
	int name##_array_get();                               			\
	int name##_array_set();                         				\
	int name##_array_append(); 										\
	int name##_array_remove();		 

/* Defines dynamic array functions */
#define DEFINE_ARRAY_FUNCS(name, type)                              \
	int name##_array_init(name##_array_t * arr, size_t cap)         \
	{                                                               \
		arr->size = 0;                                              \
		arr->capacity = cap;                                        \
		arr->data = calloc(cap, sizeof(type));	                    \
		if(arr->data == NULL) { return -1; }                        \
		else { return 0; }                                          \
	}                                                               \
	void name##_array_free(name##_array_t * arr)                    \
	{                                                               \
		free(arr->data);                                            \
		arr->data = NULL;                                           \
		arr->size = arr->capacity = 0;                              \
	}                                                               \
	int name##_array_get(name##_array_t * arr, size_t idx,    		\
	                     type * out)                               	\
	{                                                               \
		if(idx < arr->size) { *out = arr->data[idx]; return 0; }    \
		else { return -1; }                                         \
	}                                                               \
	int name##_array_set(name##_array_t * arr, size_t idx,     		\
	                     type * item)                         		\
	{                                                               \
		if(idx < arr->size) { arr->data[idx] = *item; return 0; }   \
		else { return -1; }                                         \
	}                                                               \
	int name##_array_append(name##_array_t * arr, type * item)		\
	{                                                               \
		if(arr->size >= arr->capacity)                              \
		{                                                           \
			size_t new_size = sizeof(type) * arr->capacity * 2;     \
			type * new_data = realloc(arr->data, new_size);         \
			if(new_data == NULL) { return -1; }                     \
			else { arr->capacity *= 2; arr->data = new_data; }      \
		}                                                           \
		arr->data[arr->size++] = *item;                             \
		return 0;													\
	}																\
	int name##_array_remove(name##_array_t * arr, size_t idx)		\
	{																\
		if(idx < arr->size) {										\
		arr->data[idx] = arr->data[arr->size - 1];					\
		arr->size -= 1;												\
		return 0;													\
		} else { return -1; }										\
	}                                                               

/* Dynamic array creation, for headers and sources */
#define ARRAY_HEADER(name, type)    \
	DEFINE_ARRAY_TYPE(name, type)   \
	DECLARE_ARRAY_FUNCS(name)
#define ARRAY_SOURCE(name, type)    \
	DEFINE_ARRAY_FUNCS(name, type)

/* Create numeric arrays */
ARRAY_HEADER(int, int)
ARRAY_HEADER(uint, unsigned int)
ARRAY_HEADER(long, long)
ARRAY_HEADER(ulong, unsigned long)
ARRAY_HEADER(float, float)
ARRAY_HEADER(double, double)

#endif /* ARRAY_H */
