PQueueClient : PQueueClient.o PQueue.o
	gcc -o PQueueClient PQueueClient.o PQueue.o
dijkstra.o : dijkstra.c PQueue.h
	gcc -Wall -Werror -std=c11 -c dijkstra.c
PQueueClient.o : PQueueClient.c PQueue.h
	gcc -Wall -Werror -std=c11 -c PQueueClient.c
PQueue.o : PQueue.c PQueue.h
	gcc -Wall -Werror -std=c11 -c PQueue.c
clean:     
	rm -rf *.o PQueueClient