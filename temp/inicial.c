#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>	

#define PI 3.141592653589793238462643383279502884197
#define FLOAT double


void recibe_input(int argc, char **argv, int *n, FLOAT *e, int *th){
	//This function makes sure the amount of parameters is correct
	//The number of particles and epsilon are stored in pointers
	if(argc!=4){
		fprintf(stderr, "Hay un número erroneo de parametros. USAGE: main.x N epsilon threads\n");
		exit(1);
	}
	*n = atoi(argv[1]);
	*e = atof(argv[2]);
	*th = atoi(argv[3]);
}

FLOAT *crea_vector(int n){
	//We generate the vector for the position, velocity and acceleration of size 3*n
	//The memory for this vector is allocated and its initialized in zeros
	FLOAT *v;
	int i;
	if(!(v = malloc(n * sizeof(FLOAT)))){
		fprintf(stderr, "Problem with memory allocation\n");
		exit(1);
	}

	for(i=0;i < n;i++){ 
		v[i] = 0.0; 
	}
	return v;
}

void posiciones_iniciales(FLOAT *p, int n){
	//We generate n points randomly distributed in an sphere
	//The function writes the particle's position an velocity (in x, y, and z)
	
	FLOAT phi, theta, r, costheta;
	FLOAT R;
	int i;
	R = pow(n, 1.0/3.0);
	for(i=0 ; i<n ; i++){
		phi = 2.0 * PI * drand48();
		costheta = 2.0*(drand48() - 0.5);
		theta  = acos(costheta);
		r = R * pow(drand48(), 1.0/3.0);

		p[i*3 + 0] = r * cos(phi) * sin(theta);
		p[i*3 + 1] = r * sin(phi) * sin(theta);
		p[i*3 + 2] = r * cos(theta);
	}
}


/*
* Writes the state (positions and velocities) of the i (int) time step for n particles
* FLOAT id the current state
* int n the number of particles
* FLOAT * x[n_particles * 3] (Position)
* FLOAT * y[n_particles *3] (Velocities)
*/

void escribe_estado(FLOAT *x, FLOAT *y, FLOAT *U, FLOAT *K, int n, int id){
	//We write the current state of particles in a text file
	//Each row will have the state for a particle r
	//The format is: pos_x \t pos_y \t pos_z \t vel_x \t vel_y \t vel_z
	//The name of the file contains: -state_i (the time for which the name is written - n_particles (the number of particles)

	FILE* archivo;

	char bufX[20];
	char bufY[20];
	char n1[50], n2[50], n3[50];
	int i; 

	//Prepare the name of the file
	sprintf(bufX, "%d", id);
	sprintf(bufY, "%d", n);
	strcpy(n1,  "state_");
	strcpy(n2, "_");
	strcpy(n3, ".dat");
	strcat(n1, bufX);
	strcat(n1, n2);
	strcat(n1, bufY);
	strcat(n1, n3);

	//Opens the file
	archivo = fopen(n1, "w");


	if(!(archivo=fopen(n1, "w"))){
		fprintf(stderr, "Problem opening file %s\n", n1);
		exit(0);
	}


	//Writes in the file
	for(i=0;i<n;i++){
		fprintf(archivo, "%f \t %f \t %f \t %f \t %f \t %f \t %f \t %f \n", x[3*i +0], x[3*i +1], x[3*i +2], y[3*i +0], y[3*i +1], y[3*i +2], U[i], K[i]);
	}

	//Closes the file
	fclose(archivo);

}

