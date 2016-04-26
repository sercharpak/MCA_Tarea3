all : state_0_100.dat

state_0_100.dat : main.x
		./main.x 100 0.1

main.x : main.c 
		gcc main.c inicial.c -lm -o main.x

clean : 
	rm main.x
	rm state_*
