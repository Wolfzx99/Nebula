
/*
 *	project: nebula
 *	file: data.h
 *	
 *	description:
 *	header file for data.c
 */

#include "array.h"
#include "gravity.h"

#ifndef DATA_H
#define DATA_H

typedef struct race
{
	char name[NAME_LENGTH];
	
	//add characteristics
} race;

typedef enum {arctic, temperate, desert, tropical, ocean} environment_t;

typedef struct planet
{
	char name[NAME_LENGTH];
	
	/*	points back to master list  */
	object_t *obj;
	
	environment_t local_envir;
	
	unsigned long long population;
	
	/*	resources  */
	unsigned long food;
	unsigned long ferrum;
	unsigned long artificium;
	unsigned long caelum;
	
	/*	structures  */
	unsigned int houses;
	unsigned int farms;
	unsigned int mines;
	unsigned int factories;
	unsigned int labs;
	
	/*	fortifications  */
	unsigned long anti_land_guns;
	unsigned long anti_air_guns;
	unsigned long armor;
	
	/*	hazards  */
	unsigned long radiation;
} planet;

typedef struct ship
{
	char name[NAME_LENGTH];
	
	/*	points back to master list  */
	object_t *object;
	
	//add characteristics
} ship;

typedef struct player
{
	char name[NAME_LENGTH];
	int score;
	
	race player_race;
	
	/*	the planet or ship from which the player makes decisions  */
	object_t *current_location;
	
	/*	points back to the master list  */
//	planet *player_planet[];
//	ship *player_ship[];
} player;

#endif