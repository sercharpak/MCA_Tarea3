#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define PI 3.14159265358979323846264338327950288419716939937511
#define FLOAT FLOAT

/* 
Un programa sencillo para seguir la evolucion dinamica de un conjunto de N masas puntuales.
*/

void recibe_input(int argc, char **argv, int N, FLOAT epsilon);
FLOAT *crea_vector(int N);
void posiciones_iniciales(FLOAT *p, int N);
void escribe_estado(FLOAT* positions, FLOAT* velocities, FLOAT state_i, int n_particules);
FLOAT calcula_tiempo_total(int N);
FLOAT calcula_time_step(int N);
void calcula_aceleracion(FLOAT *p, FLOAT *v, FLOAT *a, int N, FLOAT epsilon);
void actualiza_timestep(FLOAT *p, FLOAT *v, FLOAT *a, int N);

int main(int argc, char **argv){

	int i=0, N=0;
	FLOAT *p=NULL;
	FLOAT *v=NULL;
	FLOAT *a=NULL;
	FLOAT time_step=0, total_time=0, epsilon=0;
	int n_steps=0;
#define FLOAT FLOAT
	/*inicializacion*/
	recibe_input(argc, argv, &N, &epsilon);
	p = crea_vector(N);
	v = crea_vector(N);
	a = crea_vector(N);
	posiciones_iniciales(p, N);
	escribe_estado(p,v,i);

	/*tiempos caracteristicos*/
	total_time = calcula_tiempo_total(N);
	time_step = calcula_time_step(N);
	n_steps = (int)(total_time/time_step);

	/*evolucion temporal*/
	for(i=0;i<n_steps;i++){
		calcula_aceleracion(p, v, a, N, epsilon);
		actualiza_timestep(p, v, a, N);
	}
	escribe_estado(p,v,i)
	return 0;
}

FLOAT *crea_vector(int N){
	
}

void recibe_input(int argc, char **argv, int N, FLOAT epsilon){

	if (argc != 3){
		printf("Hay un número erroneo de parametros, debe ser: main.x N epsilon\n");
		return -1; 
	}
	
	N = atoi(argv[1]);	
	epsilon = atof(argv[2]);
}

void posiciones_iniciales(FLOAT *p, int N){ 

	int i, j; 
	FLOAT lambda, costheta, phi; 
	FLOAT R;

	R = pow(N,1.0/3.0);

	for(i=0;i<N; i++){ 

		lambda=R*drand48(); 
		costheta=2*drand48()-1; 
		phi=drand48()*2*PI; 

		for(j=0;j<2;j++){ 
			p[i,j]=pow(lambda,1.0/3.0)*cos(phi)*sqrt(1-costheta*costheta); 
			p[i,j]=pow(lambda,1.0/3.0)*sin(phi)*sqrt(1-costheta*costheta); 
			p[i,j]=pow(lambda,1.0/3.0)*costheta; 
		}
	}
}

/*
* Writes the state (positions and velocities) of the i (float) time for n_particules
* float state_i the current state
* int n_particules the number of particles
* FLOAT * positions[n_particles * 3] 
* FLOAT * velocities[n_particles *3]
*/
void escribe_estado(FLOAT* positions, FLOAT* velocities, FLOAT state_i, int n_particules)
{
	//We write the current state of particles in a text file
	//Each row will have the state for a particle r
	//The format is: pos_x \t pos_y \t pos_z \t vel_x \t vel_y \t vel_z
	//The name of the file contains: -state_i (the time for which the name is written - n_particles (the number of particles)

	FILE* archivo;

	char bufX[20];
	char bufY[20];
	char n1[50], n3[50], n2[50];
	int i; 

	//Prepare the name of the file
	sprintf(buf_I, "%f", state_i);
	sprintf(buf_I, "%d", n_particules);
	strcpy(n1,  "state_");
	strcpy(n2, "_");
	strcpy(n3, ".dat");
	strcat(n1, bufX);
	strcat(n1, n2);
	strcat(n1, bufY);
	strcat(n1, n3);

	//Opens the file
	archivo = fopen(n1, "w");

	//Writes in the file
	for(i=0;i<particules;i++){
		fprintf(archivo, "%f \t %f \t %f \t %f \t %f \t %f \n", positions[i], positions[i+1], positions[i+2], velocities[i], velocities[i+1], velocities[i+2]);
	}

	//Closes the file
	fclose(archivo);
}
