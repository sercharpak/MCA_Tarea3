double calcula_tiempo_total(int n);
double calcula_time_step(int n, double epsilon);
void calcula_Rcm(double *p, int n, double *Rcm);
double calcula_masa(double *p, double r, int n);
void calcula_aceleracion(double *p, double *v, double *a, int n, double epsilon, double *Rcm);
void  kick(double *p, double *v, double *a, int n, double delta_t);
void  drift(double *p, double *v, double *a, int n, double delta_t);
void calcula_energia(double *p, double *v, double *U, double *K, int n);
