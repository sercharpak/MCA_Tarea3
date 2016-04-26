all : state_0_100.dat

state_0_100.dat : executor.x
		./executor.x 100 0.1

executor.x : main.c 
		gcc linear_simulacion.c temporal.c inicial.c -lm -o executor.x

clean : 
	rm *.x
	rm state_*
