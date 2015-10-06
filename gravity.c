
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>

/*	a number twice as great as pi  */
const double TAU = 6.28318530717958647692528676655900576839433879875;

/*	gravitational constant  */
const double G = 6.67384e-11;

/*	a three-dimensional space vector  */
typedef struct vector
{
	double x;
	double y;
	double z;
} vector;

const vector null_vector = (vector) {0, 0, 0};

/*  scales one vector by a double  */
vector scale(vector a, double k)
{
	double x = a.x * k;
	double y = a.y * k;
	double z = a.z * k;
	return (vector) {x, y, z};
}

/*  calculates the length of one vector  */
double magnitude(vector a)
{
	return sqrt(pow(a.x, 2) + pow(a.y, 2) + pow(a.z, 2));
}

/*	normalizes one vector into its unit vector  */
vector normalize(vector a)
{
	double length = magnitude(a);
	double x = a.x / length;
	double y = a.y / length;
	double z = a.z / length;
	return (vector) {x, y, z};
}

/*	negates the direction of one vector  */
vector negate(vector a)
{
	double x = - a.x;
	double y = - a.y;
	double z = - a.z;
	return (vector) {x, y, z};
}

/*	calculates the sum of two vectors  */
vector add(vector a, vector b)
{
	double x = a.x + b.x;
	double y = a.y + b.y;
	double z = a.z + b.z;
	return (vector) {x, y, z};
}

/*	calculates the difference of two vectors  */
vector subtract(vector a, vector b)
{
	double x = a.x - b.x;
	double y = a.y - b.y;
	double z = a.z - b.z;
	return (vector) {x, y, z};
}

/*	calculates the dot product of two vectors  */
double dot(vector a, vector b)
{
	return (a.x * b.x) + (a.y * b.y) + (a.z * b.z);
}

/*	calculates the cross product of two vectors  */
vector cross(vector a, vector b)
{
	double x = (a.y * b.z) - (a.z * b.y);
	double y = (a.z * b.x) - (a.x * b.z);
	double z = (a.x * b.y) - (a.y * b.x);
	return (vector) {x, y, z};
}

/*	an body which experiences gravitational force  */
typedef struct grav_body
{
	char name[16];
	double mass;
	vector position;
	vector velocity;
	vector acceleration;
} grav_body;

void print_grav_body(grav_body a)
{
	printf("\t[%s]\n\tmass: %.2e\n\tposition: <%.2e,%.2e,%.2e>\n\tvelocity: <%.2e,%.2e,%.2e>\n", a.name, a.mass, a.position.x, a.position.y, a.position.z, a.velocity.x, a.velocity.y, a.velocity.z);
}

/*	a universe defined in terms its state, its precision, and its current time  */
typedef struct universe
{		
	/*	defines an array containing grav_bodies  */
	int num_bodies;
	grav_body * body;
	
	/*	the precision of the simulation (in seconds) */
	double time_step;
	
	/*	time since the simulation began (in seconds)  */
	double current_time;
} universe;

void print_universe(universe u)
{
	int i;
	
	printf("universe time: %.2e\ntime step: %.2e\n\n", u.current_time, u.time_step);
	
	for (i = 0; i < u.num_bodies; i++)
	{
		print_grav_body(u.body[i]);
	}
	
	printf("\n");
}

/*	gives every body a random mass, position, and velocity  */
void randomize_universe(universe u)
{

}

/*	calculates the gravitational accelerations of a single two-body system;
	adds these to their accelerations  */
void simulate_grav_single(grav_body *a, grav_body *b)
{
	vector dist = subtract(b->position, a->position);
	vector grav_force = scale(normalize(dist), (G * a->mass * b->mass / pow(magnitude(dist), 2)));
	a->acceleration = add(a->acceleration, scale(grav_force, 1 / a->mass));
	b->acceleration = add(b->acceleration, scale(negate(grav_force), 1 / b->mass));
}

/*	makes a call to simulate each system individually exactly once  */
void simulate_grav_full(universe *u)
{
	int i, j;
	
	/*	resets acceleration of each body to zero  */
	for (i = 0; i < u->num_bodies; i++)
	{
		u->body[i].acceleration = null_vector;
	}
	
	for (i = 0; i < u->num_bodies; i++)
	{	
		for (j = i + 1; j < u->num_bodies; j++)
		{
			simulate_grav_single(&u->body[i], &u->body[j]);
		}
		
		/*	iterates using the basic kinematics equations over time_step  */
		u->body[i].position = add(u->body[i].position, add(scale(u->body[i].velocity, u->time_step), scale(u->body[i].acceleration, 0.5 * pow(u->time_step, 2))));
		u->body[i].velocity = add(u->body[i].velocity, scale(u->body[i].acceleration, u->time_step));
	}
	
	u->current_time += u->time_step;
}

/*	main function  */
int main(void)
{
	int i, j;
	clock_t start;
	
	/*	so we can compare to Kepler's formulas for debugging purposes  */
	double orbital_period = 247173.4007;
	
	universe u;
	u.num_bodies = 2;
	u.time_step = 100;
	
	u.body = calloc(u.num_bodies, sizeof(grav_body));
	
	/*	terminates if calloc fails  */
	if (u.body == NULL)
	{
		printf("unable to allocate memory");
		
		/*	waits for the user to hit enter before exiting  */
		fseek(stdin, 0, SEEK_END);
		while(getchar() != '\n');
		return(EXIT_SUCCESS);
	}
	
	for (i = 0; i < 5; i++)
	{
		/*	reset the state of the universe  */
		u.current_time = 0;
		u.body[0] = (grav_body) {"Sun", 1.98855e30, (vector) {0, 0, 0}, (vector) {0,0,0}};
		u.body[1] = (grav_body) {"Comet", 1e3, (vector) {5.9e9, 0, 0}, (vector) {0, 149978.8942, 0}};
		
		/*	prints the initial state only once  */
		if (i == 0)
		{
			printf("----INITIAL STATE----\n");
			print_universe(u);
		}
		
		/*	starts the clock  */
		start = clock();

		for (j = 0; u.current_time < orbital_period; j++)
		{
			simulate_grav_full(&u);
		}

		/*  ends the clock and displays time elapsed  */
		printf("CPU time elapsed: %.2lf s\n", ((double) (clock() - start) / CLOCKS_PER_SEC));
		
		printf("Comet distance from start:  %.2e\n", hypot(u.body[1].position.x - 5.9e9, u.body[1].position.y));
		printf("Comet same as percent of R: %.4f%%\n", hypot(u.body[1].position.x - 5.9e9, u.body[1].position.y) / 5.9e9);
		print_universe(u);
		
		u.time_step *= 0.1;
	}
	
	free(u.body);
	
	/*	waits for the user to hit enter before exiting  */
	fseek(stdin, 0, SEEK_END);
	while(getchar() != '\n');
	return(EXIT_SUCCESS);
}