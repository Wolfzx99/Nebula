
/*
 *	project: nebula
 *	file: gravity.c
 *	
 *	description:
 *	provides basic description of gravitational bodies
 *	provides functionality for simulating gravity
 *	categorizes bodies into a universe
 */
 
#include <stdio.h>
#include <math.h>
#include <time.h>

#include "gravity.h"

ARRAY_SOURCE(object, object_t)

void object_init(object_t *obj, char name[NAME_LENGTH], double mass, vect_t pos, vect_t vel, vect_t acc)
{
	size_t i;
	
	for (i = 0; i < NAME_LENGTH; i++) { obj->name[i] = name[i]; }
	obj->mass = mass;
	obj->pos = pos;
	obj->vel = vel;
	obj->acc = acc;
}

void uni_init()
{
	/*	sets up the universe  */
	uni = malloc(sizeof(object_array_t));
	object_array_init(uni, INIT_CAPACITY);
	
	current_time = 0;
} 

void print_uni()
{
	size_t i;
	
	printf("universe time: %d\ntime step: %d\n\n", current_time, TIME_STEP);
	
	for (i = 0; i < uni->size; i++)
	{
		printf("%d out of %d", i, uni->size);
		printf("works");
		object_t *obj;
		printf("works");
		printf("%d", object_array_get(uni, i, obj));
		printf("works");
		printf("\t[%s]\n\tmass: %.2e\n\tpos: <%.2e,%.2e,%.2e>\n\tvel: <%.2e,%.2e,%.2e>\n", obj->name, obj->mass, obj->pos.x, obj->pos.y, obj->pos.z, obj->vel.x, obj->vel.y, obj->vel.z);
	}
	
	printf("\n");
}

/*	simulates gravity for a time equal to TIME_STEP  */
void simulate_grav()
{
	size_t i, j;
	object_t *obj_i, *obj_j;
	
	for (i = 0; i < uni->size; i++)
	{
		object_array_get(uni, i, obj_i);
		
		/*  calculates net gravitational acceleration on i for all j  */
		for (j = i + 1; j < uni->size; j++)
		{
			object_array_get(uni, j, obj_j);
			
			vect_t dist = subtract(obj_j->pos, obj_i->pos);
			vect_t grav_force = scale(normalize(dist), (G * obj_i->mass * obj_j->mass / pow(magnitude(dist), 2)));
			obj_i->acc = add(obj_i->acc, scale(grav_force, 1 / obj_i->mass));
			obj_j->acc = add(obj_j->acc, scale(negate(grav_force), 1 / obj_j->mass));
			
			MUST OBJEECT_ARRAY_SET()
		}
		
		/*	alters position and velocity of all objects  */
		obj_i->pos = add(obj_i->pos, add(scale(obj_i->vel, TIME_STEP), scale(obj_i->acc, 0.5 * pow(TIME_STEP, 2))));
		obj_i->vel = add(obj_i->vel, scale(obj_i->acc, TIME_STEP));
		
		/*	sets acceleration equal to 0  */
		obj_i->acc = null_v;
	}
	
	current_time += TIME_STEP;
}