
/*
 *	project: nebula
 *	file: data.c
 *	
 *	description:
 *	stores data
 */

typedef struct player player;
typedef struct race race;
typedef struct planet planet;
typedef struct ship ship;

struct player
{
	char name[16];
	int score;
	
	race player_race;
	
	/*	the planet or ship from which the player makes decisions  */
	body *location;
	
	/*	points back to the master list  */
	planet *player_planet[];
	ship *player_ship[];
};

struct planet
{
	char name[16];
	
	/*	points back to master list  */
	grav_body *body;
	
	unsigned long long population;
	
	/*	resources  */
	unsigned long water;
	unsigned long food;
	unsigned long ferrum;
	unsigned long artificium;
	unsigned long caelum;
	
	radiation rad;
}

enum radiation {SAFE, MINOR, MODERATE, SEVERE, DEADLY};