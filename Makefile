all : state_0_100.dat


state_0_100.dat : main.x
		./main.x 100 0.1 $(TH)

main.x : main.c
		gcc main.c inicial.c t_evol.c -lm -fopenmp -o main.x

main_sphere.x : main_sphere.c t_evol_sphere.c
		gcc main_sphere.c inicial.c t_evol_sphere.c -lm -fopenmp -o main_sphere.x

clean :
	rm *.x
	rm state_*
