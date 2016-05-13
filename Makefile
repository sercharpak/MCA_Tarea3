all : ./mcmc_plots/corner_plot.png

TH ?= 4
N ?= 1000
EPS ?= 0.1

./mcmc_plots/corner_plot.png : state_final_1000.dat
		python fit.py $(N)

state_final_1000.dat : main_sphere.x
		./main_sphere.x $(N) $(EPS) $(TH)
		python energia.py $(N)

main_sphere.x : main_sphere.c t_evol_sphere.c inicial.c
		gcc main_sphere.c inicial.c t_evol_sphere.c -lm -fopenmp -o main_sphere.x
		@echo 'Se ejecuta con valores default de threads=4, nbodies=1000 y epsilon=0.1'
		@echo 'Si se quiere modificar esto, ejecutar make con TH=threads, N=nbodies, EPS=epsilon'

clean :
	rm state_*
	rm *x
	rm ./mcmc_plots/*.png
