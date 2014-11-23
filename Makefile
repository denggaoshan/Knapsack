all:
	g++ -std=gnu++11 knapsack.cpp -o knapsack.o -Wall -g

clean:
	rm knapsack.o
