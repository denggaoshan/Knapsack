all:
	g++ -std=gnu++11 knapsack.cpp -o knapsack.o -Wall -O3
	g++ -std=gnu++11 knapsack.cpp -o knapsack_dynamic.o -Wall -O3

clean:
	rm knapsack.o knapsack_dynamic.o
	
