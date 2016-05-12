all : state_final_1000.dat


state_final_1000.dat : main_direct.x
		./main_direct.x 1000 0.1 $(TH)

main_direct.x : main_direct.c t_evol.c inicial.c
		gcc main_direct.c inicial.c t_evol.c -lm -fopenmp -o main_direct.x

clean :
	rm state_*
	rm ./*x
