#include <iostream>
#include <random>
#include <algorithm>
#include <fstream>

int main(){
	std::random_device rd;
	std::mt19937 gen(rd());

	std::bernoulli_distribution distrib(0.5);

	std::ofstream out;
	out.open("rand_walk.txt");

	std::ofstream out1;
	out1.open("huge_step.txt");


	int N = 10000; //amount of various walkers;
	int amount_step = 10000;

	std::vector<int> point (N, 0);

	for (int i = 0; i < amount_step; i++){

		std::vector<int> step;
		std::transform(std::begin(point), std::end(point), std::back_inserter(step), 
			[&distrib, &gen](int a){return distrib(gen) ? (a + 1) : (a - 1);});
		
		double average_displacement = (double)std::accumulate(step.begin(), step.end(), 0) / N;
		double average_abs_displacement = (double)std::accumulate(step.begin(), step.end(), 0, [](int a, int b){return a + abs(b);}) / N;
		double average_square_displacement = (double)std::accumulate(step.begin(), step.end(), 0, [](int a, int b){return a + b*b;}) / N;

		point = step;

		out << i << " " << average_displacement << " " << average_abs_displacement << " " << average_square_displacement << "\n";
	}

	for (int i: point){
		out1 << i << "\n"; 
	}

	out.close();

	return 0;
}