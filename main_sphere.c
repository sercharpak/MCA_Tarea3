#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include "inicial.h"
#include "t_evol_sphere.h"

/*
  Tarea 3 Metodos Computacionales Avanzados
  Un programa sencillo para seguir la evolucion
  dinamica de un conjunto de N masas puntuales.
  Con aproximación esferica
*/

int main(int argc, char **argv){
	int i=0, N=0, threads=1;
	double *p=NULL;
	double *v=NULL;
	double *a=NULL;
	double *U;
	double *K;
	double *Rcm;
	double time_step=0, total_time=0, epsilon=0;
	int n_steps=0;

	/*inicial*/
	recibe_input(argc, argv, &N, &epsilon, &threads);
	
	omp_set_num_threads(threads);

 	p = crea_vector(3*N);
	v = crea_vector(3*N);
	a = crea_vector(3*N);
	U = crea_vector(N);
	K = crea_vector(N);
	Rcm = crea_vector(3);
	posiciones_iniciales(p, N);
	calcula_energia(p, v, U, K, N);
	escribe_estado(p, v, U, K, N, i);
	calcula_Rcm(p, N, Rcm);
  
	// tiempos caracteristicos 
	total_time = calcula_tiempo_total(N);
	time_step = calcula_time_step(N, epsilon);
	n_steps = (int)(total_time/time_step);
	fprintf(stderr, "tiempo total: %f time_step: %f n_steps %d\n",total_time, time_step, n_steps);

	//evolucion temporal

	calcula_aceleracion(p, v, a, N, epsilon, Rcm);
	kick(p, v, a, N, time_step/2.0);  
	for(i=0;i<n_steps;i++){
		drift(p, v, a, N, time_step);  
		calcula_aceleracion(p, v, a, N, epsilon, Rcm);
		kick(p, v, a, N, time_step);  
	}
	calcula_energia(p, v, U, K, N);
	escribe_estado(p, v, U, K, N, i);

	
	return 0;
}

