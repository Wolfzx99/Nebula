
/*
 *	project: nebula
 *	file: data.h
 *	
 *	description:
 *	header file for data.c
 */
 
#ifndef DATA_H
#define DATA_H

typedef struct race
{
	char name[16];
	
	//add characteristics
} race;

typedef enum environment {arctic, temperate, desert, tropical, ocean} environment;

typedef struct planet
{
	char name[16];
	
	/*	points back to master list  */
	body *body;
	
	environment local_environment;
	
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
	char name[16];
	
	/*	points back to master list  */
	body *body;
	
	//add characteristics
} ship;

typedef struct player
{
	char name[16];
	int score;
	
	race player_race;
	
	/*	the planet or ship from which the player makes decisions  */
	body *current_location;
	
	/*	points back to the master list  */
	planet *player_planet[];
	ship *player_ship[];
} player;

#endif