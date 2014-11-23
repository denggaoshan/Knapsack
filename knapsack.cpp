#include <iostream>
#include <vector>
#include <bitset>
#include <tuple>

#define N_OF_ITEMS 50

using namespace std;

static int    crossover_prob = 70;
static size_t population_size = 500;

class Chromosome{

public:
	bitset<N_OF_ITEMS> data;

	static uint *weights;
	static uint *values;
	static int   mutation_prob;
	static uint  capacity;
	Chromosome(){
		for(size_t i = 0; i < N_OF_ITEMS; i++)
			data[i] = rand() % 2;
	}

	Chromosome(bitset<N_OF_ITEMS> data){
		this->data = data;
	}

	int fitness() const{
		int  result  = 0;
		uint weight = 0;
		for(size_t i = 0 ; i < N_OF_ITEMS; i++){
			result += values[i] * data[i];
			weight += weights[i] * data[i];
			if(weight > capacity){
				result = -1;
				break;
			}
		}
		return result;
	}

	void mutate(){
		for(uint i = 0 ; i < N_OF_ITEMS; i++){
			if(rand() % 100 < mutation_prob)
				data.flip(i);
		}
	}

	void print() const{
		for(size_t i = 0 ; i < N_OF_ITEMS; i++)
			cout << data[i];
		cout << " " << fitness() << endl;
	}
};

bool operator>(const Chromosome& lhs, const Chromosome& rhs){
    return lhs.fitness() > rhs.fitness();
}

Chromosome select_parent(vector <Chromosome> &population){
	Chromosome candidate1 = population[rand() % population_size];
	Chromosome candidate2 = population[rand() % population_size];

	return (candidate1 > candidate2) ? candidate1 : candidate2;
}


tuple <Chromosome, Chromosome>
crossover(vector <Chromosome> &population)
{
	Chromosome parent1 = select_parent(population);
	Chromosome parent2 = select_parent(population);

	if(rand() % 100 < crossover_prob){
		bitset<N_OF_ITEMS> buf1;
		bitset<N_OF_ITEMS> buf2;
		uint point = rand() % N_OF_ITEMS;
		for(uint i = 0 ; i < N_OF_ITEMS; i++){
			buf1[i] = (i <= point) ? parent1.data[i] : parent2.data[i];
			buf2[i] = (i <= point) ? parent2.data[i] : parent1.data[i];
		}
		Chromosome child1(buf1), child2(buf2);
		return tuple <Chromosome, Chromosome> (child1, child2);
	}
	else
		return tuple <Chromosome, Chromosome>(parent1, parent2);
}

static uint* init_weights(){
	uint *weights = new uint[N_OF_ITEMS];
	for(size_t i = 0; i < N_OF_ITEMS; i++)
		weights[i] = 2 * i + 1;
	return weights;
}

static uint* init_values(){
	uint *values = new uint[N_OF_ITEMS];
	for(size_t i = 0; i < N_OF_ITEMS; i++)
		values[i] = i;
	return values;
}


void next_generation(vector <Chromosome> &population){
	vector <Chromosome> new_population;

	while(new_population.size() < population.size()){
		auto children = crossover(population);
		new_population.push_back(get<0>(children));
		new_population.push_back(get<1>(children));
	}
	population = new_population;
	population.resize(population_size);
}

Chromosome find_best(vector <Chromosome> &population){
	Chromosome best = population.front();
	for(auto itr = population.begin() + 1; itr!=population.end(); itr++){
		if(*itr > best)
			best = *itr;
	}
	return best;
}

int   Chromosome::mutation_prob = 2;
uint  Chromosome::capacity = 2000;
uint *Chromosome::weights  = init_weights();
uint *Chromosome::values   = init_values();


int main(){
	srand(time(NULL));
	vector <Chromosome> population(population_size);

	Chromosome best = find_best(population);
	uint timer;
	uint n_of_best_gen = 0;
	uint improved_generations_ago = 0;
	for(timer = 0; improved_generations_ago < 25 ;timer++){
		next_generation(population);
		for(uint i = 0; i < population_size; i++)
			population[i].mutate();

		Chromosome next_generation_best = find_best(population);
		if(next_generation_best > best){
			best = next_generation_best;
			improved_generations_ago = 0;
			n_of_best_gen = timer;
		}
		else
			improved_generations_ago++;
	}

	
	for(size_t i = 0; i < population_size; i++)
		population[i].print();

	cout << n_of_best_gen << endl;
	best.print();

	delete[] Chromosome::weights;
	delete[] Chromosome::values;
	return 0;
}
