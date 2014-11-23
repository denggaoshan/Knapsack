# Genetic algorithm solving 0-1 knapsack problem

This application showes how to apply genetic algorithm to [knapsack problem](https://en.wikipedia.org/wiki/Knapsack_problem).

I use 2-way [determenistic tournament selection](http://en.wikipedia.org/wiki/Tournament_selection) to choose parent from population for recombination.

In crossover phase [one-point-crossover](http://en.wikipedia.org/wiki/Crossover_(genetic_algorith)#One-point_crossover) method is used.

Algorithm terminates if there was no improvement during last 25 generations.
