#include <iostream>

using namespace std;

int max(int a, int b){
	return (a > b)? a : b;
}

uint dp(uint capacity, uint *weights, uint *values, size_t n_of_items){

	uint **table = new uint*[n_of_items + 1];
	for(uint i = 0 ; i <= n_of_items; i++){
		table[i] = new uint[capacity + 1];
	}
	for (uint i = 0; i <= n_of_items; i++){
		for (uint w = 0; w <= capacity; w++){
			if (i==0 || w==0)
				table[i][w] = 0;
			else if (weights[i-1] <= w)
				table[i][w] = max(values[i-1] + table[i-1][w-weights[i-1]],  table[i-1][w]);
			else
				table[i][w] = table[i-1][w];
		}
	}
	uint result = table[n_of_items][capacity];
	for(uint i = 0; i <= n_of_items; i++){
		delete[] table[i];
	}
	delete[] table;
	return result;
}

uint* init_weights(size_t n_of_items){
	uint *weights = new uint[n_of_items];
	for(size_t i = 0; i < n_of_items; i++)
		weights[i] = (97 * (i+1)) % 11;
	return weights;
}

uint* init_values(size_t n_of_items){
	uint *values = new uint[n_of_items];
	for(size_t i = 0; i < n_of_items; i++)
		values[i] = (83 * (i+1)) % 41;
	return values;
}

int main(){
	size_t n_of_items = 300;
	uint *values = init_values(n_of_items);
	uint *weights = init_weights(n_of_items);
	uint capacity = 800;
	cout << dp(capacity, weights, values, n_of_items) << endl;
	delete[] values;
	delete[] weights;
	return 0;
}