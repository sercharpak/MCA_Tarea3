#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#define PI 3.141592653589793238462643383
#define G_GRAV 4.49E-3
#define m 1.0

double calcula_tiempo_total(int n){
  double t_dyn;
  double rho;
  double R;
  R = pow(n, 1.0/3.0);
  rho = n / (4.0/3.0) / (PI * pow(R,3));
  t_dyn = 1.0/sqrt(G_GRAV * rho);
  return 5.0 * t_dyn;
}

double calcula_time_step(int n, double epsilon){
  double t_dyn; 
  double rho;
  rho = n / (4.0/3.0) / (PI * pow(epsilon, 3));
  t_dyn = 1.0/sqrt(G_GRAV * rho);
  return t_dyn;
}

void calcula_energia(double *p, double *v, double *U, double *K, int n){
  int i, j, k;
  double delta_total;
  for(i=0;i<n;i++){
    K[i] = 0.0;
    for(k=0;k<3;k++){
      K[i] += 0.5 * pow(v[3*i + k],2.0);
    }
    U[i] = 0.0;
    for(j=0;j<n;j++){
      if(i!=j){
	delta_total = 0.0;
	for(k=0;k<3;k++){
	  delta_total += pow((p[i*3 + k] - p[j*3 + k]),2);
	}      
	U[i] += -G_GRAV/sqrt(delta_total);
      }
    }
  }
}

void calcula_Rcm(double *p, int n, double *Rcm, int th){
  double x=0,y=0,z=0;
  int i=0;
#pragma omp parallel for
  for(i=0;i<n;i++){
    x+=p[i*3 + 0];
    y+=p[i*3 + 1];
    z+=p[i*3 + 2];
  }
  Rcm[0]=x/n;
  Rcm[1]=y/n;
  Rcm[2]=z/n;
}

double calcula_masa(double *p, double r, int n, int th){
  int i, count=0;
  double R;
#pragma omp parallel for private(R)
  for(i=0;i<n;i++){
    R=p[i*3 + 0]*p[i*3 + 0] + p[i*3 + 1]*p[i*3 + 1] + p[i*3 + 2]*p[i*3 + 2];    
    if(R<=r){
      count+=1;
    }
  }

  return count*m;
}

void calcula_aceleracion(double *p, double *v, double *a, int n, double epsilon, int th, double *Rcm){
  int i,k;
  double M=0.0;
  double r=0.0;
  double radio;
  double delta, delta_total;
#pragma omp parallel for private(r, M, radio, k)
  for(i=0;i<n;i++){
    r=p[i*3 + 0]*p[i*3 + 0] + p[i*3 + 1]*p[i*3 + 1] + p[i*3 + 2]*p[i*3 + 2];
    M=calcula_masa(p, r, n, th);
    radio=(p[i*3 + 0]-Rcm[0])*(p[i*3 + 0]-Rcm[0]) + (p[i*3 + 1]-Rcm[1])*(p[i*3 + 1]-Rcm[1]) + (p[i*3 + 2]-Rcm[2])*(p[i*3 + 2]-Rcm[2]);
    for(k=0;k<3;k++){
      a[i*3 + k] = -G_GRAV*(p[i*3 + k]-Rcm[k])*M/pow(radio + epsilon*epsilon,1.5);
    }
  }
}


void  kick(double *p, double *v, double *a, int n, double delta_t, int th){
  int i,k;
#pragma omp parallel for private(k)
  for(i=0;i<n;i++){
    for(k=0;k<3;k++){
      v[i*3 + k] += a[i*3 + k] * delta_t;
    }
  }
}  

void  drift(double *p, double *v, double *a, int n, double delta_t, int th){
  int i,k;
#pragma omp parallel for private(k)
  for(i=0;i<n;i++){
    for(k=0;k<3;k++){
      p[i*3 + k] += v[i*3 + k] * delta_t;
    }
  }
}  

