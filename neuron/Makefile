all : main

main : main.o neuron.o sigmoid.o
		gcc main.o neuron.o sigmoid.o -o XORnn

main.o: main.c sigmoid.h neuron.h
		gcc -Wall -Wextra -Werror -std=c99 -c main.c sigmoid.h neuron.h

neuron.o: neuron.c neuron.h sigmoid.h
		gcc -Wall -Wextra -Werror -std=c99 -c neuron.c neuron.h sigmoid.h

sigmoid.o: sigmoid.c sigmoid.h
		gcc -Wall -Wextra -Werror -std=c99 -c sigmoid.c sigmoid.h

clean:
		rm *.o

