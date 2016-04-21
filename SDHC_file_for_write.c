#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>



//Definition of float size constant
#define FLOAT double

void write_state_i(FLOAT*positions, FLOAT* velocities, float state_i, int n_particules);

/*
* Writes the state (positions and velocities) of the i (float) time for n_particules
* float state_i the current state
* int n_particules the number of particles
* FLOAT * positions[n_particles * 3] 
* FLOAT * velocities[n_particles *3]
*/
void write_state_i(FLOAT*positions, FLOAT* velocities, float state_i, int n_particules)
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
