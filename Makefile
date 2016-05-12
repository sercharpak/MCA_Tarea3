all : state_final_1000.dat


state_final_1000.dat : main_sphere.x
		./main_sphere.x 1000 0.1 $(TH)

main_sphere.x : main_sphere.c t_evol_sphere.c inicial.c
		gcc main_sphere.c inicial.c t_evol_sphere.c -lm -fopenmp -o main_sphere.x

clean :
	rm state_*
	rm ./*x
